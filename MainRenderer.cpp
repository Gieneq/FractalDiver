#include "MainRenderer.h"
#include <utility>
#include <iostream>
#include "rgb_hsv.h"

MainRenderer::MainRenderer() {

}

MainRenderer::~MainRenderer() {
    if (this->renderer != nullptr) {
        SDL_DestroyRenderer(this->renderer);
    }
}

bool MainRenderer::setup(SDL_Window * window) {
    using std::cerr;
    using std::endl;
    renderer = SDL_CreateRenderer(window, -1, 0); //SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        return false;
    }
    this->window = window;

    surface = SDL_CreateRGBSurface(0, Presets::WINDOW_WIDTH, Presets::WINDOW_HEIGHT, Presets::WINDOW_DEPTH, 0, 0, 0, 0);

    build_colors_palett();
    return true;
}

void MainRenderer::build_colors_palett() {
    for(size_t i{0U}; i < Presets::Rendering::PALETTE_COLORS_COUNT; ++i) {
        float r,g,b;

        size_t hue_i = (i + Presets::Rendering::PALETTE_SHIFT_DEGREES) % Presets::Rendering::PALETTE_COLORS_COUNT;
        float h = 360.0F * static_cast<float>(hue_i) / static_cast<float>(Presets::Rendering::PALETTE_COLORS_COUNT);
        float s = 1;
        float v = i < Presets::Rendering::PALETTE_COLORS_COUNT - Presets::Rendering::PALETTE_COLORS_THR ? 1.0F : 0.0F;
        HSVtoRGB(r,g,b,h,s,v);
        uint8_t px_r = static_cast<uint8_t>(255*r);
        uint8_t px_g = static_cast<uint8_t>(255*g);
        uint8_t px_b = static_cast<uint8_t>(255*b);
        colors_palett[i] = {px_r, px_g, px_b, 255};
    }
}

void MainRenderer::prepare(double dt) {
    time_accumulator += dt;
    SDL_RenderClear(renderer);
}

void MainRenderer::render() {

}

void MainRenderer::present() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);

}

uint8_t MainRenderer::get_gradient(size_t v) {
    constexpr auto f_iterations = static_cast<float>(Presets::Sim::ITERATIONS);
    constexpr auto fmax_color = 255.0F;
    float fv = static_cast<float>(v);
    fv = fmax_color * fv / f_iterations;
    auto color = static_cast<int>(fv);
    color = color > 255 ? 255 : color;
    color = color < 0 ? 0 : color;
    return (uint8_t)(color);
}

void MainRenderer::render_buffer(float* buffer) {
    auto value_max = static_cast<float>(Presets::Rendering::PALETTE_COLORS_COUNT);
    auto threshold = static_cast<float>(Presets::Rendering::PALETTE_COLORS_COUNT - Presets::Rendering::PALETTE_COLORS_THR);

    SDL_LockSurface(surface);

    for(size_t iy{0}; iy<Presets::WINDOW_HEIGHT; ++iy) {
        for(size_t ix{0}; ix<Presets::WINDOW_WIDTH; ++ix) {
            auto value = buffer[iy * Presets::WINDOW_WIDTH + ix];
            uint8_t pxr, pxg, pxb;
            if(Presets::Rendering::USE_CACHED_PALLET) {
                auto color = colors_palett[static_cast<size_t>(value)];
                pxr = color.r;
                pxg = color.g;
                pxb = color.b;
            } else {
                float h = 360.0F * value / value_max;
                float s = 1.0F;
                float v =  value < threshold ? 1.0F : 0.0F;
                float r,g,b;
                HSVtoRGB(r,g,b,h,s,v);
                pxr = static_cast<uint8_t>(255.0F*r);
                pxg = static_cast<uint8_t>(255.0F*g);
                pxb = static_cast<uint8_t>(255.0F*b);
            }

            Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) surface->pixels
                                             + iy * surface->pitch
                                             + ix * surface->format->BytesPerPixel);

            
            *target_pixel = SDL_MapRGB(surface->format, pxr, pxg, pxb);
        }
    }
    
    SDL_UnlockSurface(surface);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &destr);
    SDL_DestroyTexture(texture);
}


