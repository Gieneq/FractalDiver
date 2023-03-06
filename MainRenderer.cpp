#include "MainRenderer.h"

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
    return true;
}

void MainRenderer::prepare() {
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