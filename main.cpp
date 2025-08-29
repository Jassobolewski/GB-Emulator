#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>
#include "PPU.h"

// --- Emulator State and Constants ---
const int GB_SCREEN_WIDTH = 160;
const int GB_SCREEN_HEIGHT = 144;

struct EmuState {
    Uint32 framebuffer[GB_SCREEN_HEIGHT][GB_SCREEN_WIDTH]{};
    SDL_Texture* screenTexture = nullptr;
    const SDL_PixelFormatDetails* screenFormatDetails = nullptr; // Let's rename for clarity
};

// --- SDL Globals ---
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

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
                                                 SDL_PIXELFORMAT_UNKNOWN,
                                                 SDL_TEXTUREACCESS_STREAMING,
                                                 GB_SCREEN_WIDTH,
                                                 GB_SCREEN_HEIGHT);

        if (state->screenTexture == nullptr) {
            SDL_Log("Couldn't create screen texture: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        SDL_PropertiesID props = SDL_GetTextureProperties(state->screenTexture);

        // 2. Get the pixel format from the properties. It's stored as a number.
        auto format = (SDL_PixelFormat)SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_FORMAT_NUMBER, SDL_PIXELFORMAT_UNKNOWN);


        state->screenFormatDetails = SDL_GetPixelFormatDetails(format);
        if (state->screenFormatDetails == nullptr) {
            SDL_Log("Couldn't get pixel format details for format %s: %s", SDL_GetPixelFormatName(format), SDL_GetError());
            return SDL_APP_FAILURE;
        }

        SDL_Log("Texture created with format: %s", SDL_GetPixelFormatName(format));


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
        if (event->key.key == SDLK_ESCAPE) {
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
        SDL_DestroyTexture(state->screenTexture);
        delete state;
    }
    // SDL will automatically handle the window and renderer.
}

const std::vector<uint8_t> SMILEY_TILE1 = {
        0x7C, 0x7C, 0x00, 0xC6, 0xC6, 0x00, 0x00, 0xFE, 0xC6, 0xC6, 0x00, 0xC6, 0xC6, 0x00,  0x00,  0x00
};

const std::vector<uint8_t> SMILEY_TILE = {
        0x3C, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
        0x7E, 0x5E, 0x7E, 0x0A, 0x7E, 0x42, 0x7E, 0x3C
};

const std::vector<uint8_t> KNOWN_GOOD_SMILEY = {
        0x3C, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x7E, 0x3C,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


void render_ppu_frame(EmuState* state)
{
    PPU ppu;
    std::array<uint8_t, 64> smiley_pixels = ppu.tileDecoder(SMILEY_TILE1);

    uint8_t colors[4][4] = {
            {0x9D, 0xD8, 0xD9, 0xFF}, // Lightest
            {0x69, 0x98, 0xA5, 0xFF},
            {0x3F, 0x63, 0x71, 0xFF},
            {0x21, 0x30, 0x3B, 0xFF}  // Darkest
    };

    // Pre-calculate the packed Uint32 colors once using the format details
    Uint32 mapped_colors[4];
    for(int i = 0; i < 4;i++) {
        mapped_colors[i] = SDL_MapRGBA(state->screenFormatDetails, nullptr,
                                       colors[i][0], colors[i][1], colors[i][2], colors[i][3]);
    }

    const int TILE_WIDTH = 8;
    const int TILE_HEIGHT = 8;

    for (int y = 0; y < TILE_HEIGHT; ++y) {
        for(int x = 0; x < TILE_WIDTH; ++x) {
            // The correct formula to get the pixel from the 1D array
            int index = y * TILE_WIDTH + x;

            // Make sure we don't read past the end of the array
            if (index < smiley_pixels.size()) {
                uint8_t color_id = smiley_pixels[index];
                state->framebuffer[y][x] = mapped_colors[color_id];
            }
        }
    }

    for (int y = 0; y < TILE_HEIGHT; ++y) {
        for(int x = 0; x < TILE_WIDTH; ++x) {
            // The correct formula to get the pixel from the 1D array
            int index = y * TILE_WIDTH + x;

            // Make sure we don't read past the end of the array
            if (index < smiley_pixels.size()) {
                uint8_t color_id = smiley_pixels[index];
                state->framebuffer[y + 64][x + 64] = mapped_colors[color_id];
            }
        }
    }

}