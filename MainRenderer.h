#pragma once
#include <SDL.h>

#include <vector>
#include <memory>
#include <iostream>
#include <cstdlib>

#include "Settings.h"

class MainRenderer {
public:
	MainRenderer();
	~MainRenderer();

	bool setup(SDL_Window* window);

    void prepare();
    void render();
    void present();

    // void add_sprite(const Sprite* sprite);

private:
    SDL_Renderer* renderer{ nullptr };
    SDL_Window* window{ nullptr };
    // std::vector<const Sprite*> batch;
};






/*
SDL_Surface* bmp = SDL_LoadBMP("../img/grumpy-cat.bmp");
if (bmp == nullptr) {
    cerr << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
    if (ren != nullptr) {
        SDL_DestroyRenderer(ren);
    }
    if (win != nullptr) {
        SDL_DestroyWindow(win);
    }
    SDL_Quit();
    return EXIT_FAILURE;
}

SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
if (tex == nullptr) {
    cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
    if (bmp != nullptr) {
        SDL_FreeSurface(bmp);
    }
    if (ren != nullptr) {
        SDL_DestroyRenderer(ren);
    }
    if (win != nullptr) {
        SDL_DestroyWindow(win);
    }
    SDL_Quit();
    return EXIT_FAILURE;
}
SDL_FreeSurface(bmp);

for (int i = 0; i < 20; i++) {
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, nullptr, nullptr);
    SDL_RenderPresent(ren);
    SDL_Delay(100);
}

SDL_DestroyTexture(tex);
SDL_DestroyRenderer(ren);
SDL_DestroyWindow(win);

return EXIT_SUCCESS;

*/