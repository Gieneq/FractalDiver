#include "Engine.h"


Engine::~Engine() {
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

bool Engine::setup(size_t window_width, size_t window_height) {
    using std::cerr;
    using std::endl;
    std::cout << "Setting up game base" << std::endl;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow(Presets::WINDOW_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return false;
    }

    if (!renderer.setup(this->window)) {
        cerr << "SDL_CreateRenderer Error" << SDL_GetError() << endl;
        if (window != nullptr) {
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
        return false;
    }
    return true;
}

size_t Engine::get_window_width() {
    int win_width;
    SDL_GetWindowSize(window, &win_width, NULL);
    return win_width;
}

size_t Engine::get_window_height() {
    int win_height;
    SDL_GetWindowSize(window, &win_height, NULL);
    return win_height;
}

static inline bool check_if_quitting_window(SDL_Event &ev) {
    return (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE);
}

void Engine::loop() {
    auto last_tick_count = SDL_GetPerformanceCounter();
    auto current_tick_count = SDL_GetPerformanceCounter();
    float dt{ 0 };
    while (true) {
        /*
         * INPUT
         */
        SDL_Event ev;
        if (SDL_PollEvent(&ev)) {
            if (check_if_quitting_window(ev))
                break;
            // if (!gui.input(ev)) {
            //     if (!world.input(ev)) {
            //         this->input(ev);
            //     }
            // }
        }

        /*
         * UPDATE
         */
        current_tick_count = SDL_GetPerformanceCounter();
        dt = (current_tick_count - last_tick_count) / (float)SDL_GetPerformanceFrequency() * 1000.0F;
        // gui.update(dt);
        // world.update(dt);
        this->update(dt);
        SDL_Delay(static_cast<unsigned int>(std::floor(std::max(0.0F, Presets::FPS_CAP_INTERV_MS - dt))));
        last_tick_count = current_tick_count;

        /*
         * RENDER
         */
        renderer.prepare();
        // gui.render(&renderer);
        // world.render(&renderer);
        this->render(&renderer);
        renderer.render(); //feeded with render methods from I/U/R
        renderer.present();
    }
}
