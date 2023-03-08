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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
        //float v = static_cast<float>(Presets::Sim::ITERATIONS - i - 1) / static_cast<float>(Presets::Sim::ITERATIONS);
        // v = powf(v, 0.8F);
        // v = v > 0.5F ? 1.0F : v;
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
    // const auto debug_color = Presets::Colors::DEBUG;
    // SDL_Rect draw_rect;
    // for (auto* element : batch) {
    //     SDL_SetRenderDrawColor(renderer, 
    //         element->color.r,
    //         element->color.g, 
    //         element->color.b, 
    //         element->color.a
    //     );
    //     draw_rect.x = static_cast<int>(element->x) + Presets::CENTERING_OFFSET_X;
    //     draw_rect.y = static_cast<int>(element->y) + Presets::CENTERING_OFFSET_Y;
    //     draw_rect.w = static_cast<int>(element->w);
    //     draw_rect.h = static_cast<int>(element->h);
    //     SDL_RenderFillRect(renderer, &draw_rect);
    
    //     //SDL_SetRenderDrawColor(renderer, debug_color.r, debug_color.g, debug_color.b, debug_color.a);
    //     //SDL_RenderDrawRect(renderer, &draw_rect);
    // }
}

void MainRenderer::present() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
    // batch.clear();
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
            // value /= (double)(Presets::Rendering::PALETTE_COLORS_COUNT);
            // value = pow(value, .9);
            // value *= (double)(Presets::Rendering::PALETTE_COLORS_COUNT);
            // auto svalue = static_cast<size_t>(value);
            // auto color = colors_palett[svalue];

            float h = 360.0F * value / value_max;
            float s = 1.0F;
            float v =  value < threshold ? 1.0F : 0.0F;
            float r,g,b;

            HSVtoRGB(r,g,b,h,s,v);

            uint8_t pxr = static_cast<uint8_t>(255.0F*r);
            uint8_t pxg = static_cast<uint8_t>(255.0F*g);
            uint8_t pxb = static_cast<uint8_t>(255.0F*b);


            //SDL_Color color{static_cast<uint8_t>(value*255.0/(double)(Presets::Rendering::PALETTE_COLORS_COUNT)), 0,0,255};
            // SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            // SDL_SetRenderDrawColor(renderer, pxr, pxg, pxb, 255);
            // SDL_RenderDrawPoint(renderer, ix, iy);
            
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

// void MainRenderer::add_sprite(const Sprite* sprite) {
//     batch.push_back(sprite);
// }








    // using std::cerr;
    // using std::endl;
    // std::cout << "Hello, world!\n";

    // if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    //     cerr << "SDL_Init Error: " << SDL_GetError() << endl;
    //     return EXIT_FAILURE;
    // }


    // SDL_Event event;
    // SDL_Renderer *renderer;
    // SDL_Window *window;
    // int i;

    // SDL_Init(SDL_INIT_VIDEO);
    // SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    // SDL_RenderClear(renderer);
    // SDL_SetRenderDrawColor(renderer, 255, 22, 0, 255);
    // for (i = 0; i < WINDOW_WIDTH; ++i)
    //     SDL_RenderDrawPoint(renderer, i, i);
    // SDL_RenderPresent(renderer);
    // while (1) {
    //     if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
    //         break;
    // }
    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // SDL_Quit();
    // return EXIT_SUCCESS;