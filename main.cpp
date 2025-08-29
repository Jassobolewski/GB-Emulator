#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// --- Emulator State and Constants ---
const int GB_SCREEN_WIDTH = 160;
const int GB_SCREEN_HEIGHT = 144;

struct EmuState {
    uint8_t framebuffer[GB_SCREEN_HEIGHT][GB_SCREEN_WIDTH][4]{}; // RGBA format
    SDL_Texture* screenTexture = nullptr;
    // You would also add your CPU state, memory, etc., here
    // GameBoyCPU cpu;
    // GameBoyMemory memory;
};

// --- SDL Globals ---
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

// A placeholder for your actual PPU rendering logic
void render_ppu_frame(EmuState* state);


/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    // Create and initialize our emulator state
    auto *state = new EmuState();
    *appstate = state; // Pass our state back to the SDL app framework

    SDL_SetAppMetadata("GB Emulator", "0.1", "com.example.gb-emulator");

    if (SDL_Init(SDL_INIT_VIDEO)) {

        // Create the window scaled up from the GB resolution
        if (!SDL_CreateWindowAndRenderer("GB Emulator", GB_SCREEN_WIDTH * 4, GB_SCREEN_HEIGHT * 4, 0, &window,
                                        &renderer)) {
            SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        // --- Create the texture for the Game Boy screen ---
        state->screenTexture = SDL_CreateTexture(renderer,
                                                 SDL_PIXELFORMAT_RGBA32,
                                                 SDL_TEXTUREACCESS_STREAMING,
                                                 GB_SCREEN_WIDTH,
                                                 GB_SCREEN_HEIGHT);

        if (state->screenTexture == nullptr) {
            SDL_Log("Couldn't create screen texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        SDL_SetTextureScaleMode(state->screenTexture, SDL_SCALEMODE_NEAREST);

        return SDL_APP_CONTINUE;
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
}

/* This function runs when a new event occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (event->key.which == SDLK_ESCAPE) {
            return SDL_APP_SUCCESS;
        }
        // TODO: Handle Game Boy joypad input here
    }
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    auto *state = (EmuState*)appstate; // Get our emulator state

    // 1. RUN EMULATOR FOR ONE FRAME
    // This is where you'd call your CPU::Execute() in a loop until the PPU
    // signals that a full frame has been rendered (VBlank).
    // For this example, we'll just call a placeholder PPU function.
    render_ppu_frame(state);

    // 2. UPDATE THE SDL TEXTURE
    // Copy the pixel data from our framebuffer to the GPU texture.
    int pitch = GB_SCREEN_WIDTH * 4; // 160 pixels * 4 bytes per pixel (RGBA)
    SDL_UpdateTexture(state->screenTexture, nullptr, state->framebuffer, pitch);

    // 3. RENDER THE TEXTURE TO THE SCREEN
    SDL_RenderClear(renderer); // Clear the window (good practice)
    SDL_RenderTexture(renderer, state->screenTexture, nullptr, nullptr); // Draw texture, scaled to fit window
    SDL_RenderPresent(renderer); // Show the result

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    auto *state = (EmuState*)appstate;
    if (state) {
        // We MUST destroy the texture we created.
        SDL_DestroyTexture(state->screenTexture);
        // And free the memory for our state struct.
        delete state;
    }
    // SDL will automatically handle the window and renderer.
}


// --- YOUR PPU LOGIC GOES HERE ---
// This is a placeholder that demonstrates how to fill the framebuffer.
// Replace this with your actual PPU rendering logic.
void render_ppu_frame(EmuState* state)
{
    // The classic Game Boy green-ish color palette (RGBA)
    uint8_t colors[4][4] = {
            { 0x9B, 0xBC, 0x0F, 0xFF }, // Lightest Green
            { 0x8A, 0xAC, 0x0F, 0xFF }, // Light Green
            { 0x30, 0x62, 0x30, 0xFF }, // Dark Green
            { 0x0F, 0x38, 0x0F, 0xFF }  // Darkest Green
    };


    // Example: Fill the screen with a pattern
    for (int y = 0; y < GB_SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < GB_SCREEN_WIDTH; ++x) {
            // Your PPU logic would determine which of the 4 colors a pixel is.
            // For example: uint8_t color_index = ppu_get_pixel_color(x, y);
            uint8_t color_index = (x / 40 + y / 40) % 4; // Simple pattern

            // Copy the RGBA values for that color into the framebuffer
            state->framebuffer[y][x][0] = colors[color_index][0]; // R
            state->framebuffer[y][x][1] = colors[color_index][1]; // G
            state->framebuffer[y][x][2] = colors[color_index][2]; // B
            state->framebuffer[y][x][3] = colors[color_index][3]; // A
        }
    }
}