#pragma once
#include <SDL.h>

#include <memory>
#include <iostream>
#include <array>
#include <cstdlib>

#include "Settings.h"

class MainRenderer {
public:
	MainRenderer();
	~MainRenderer();

	bool setup(SDL_Window* window);

    void prepare(double dt);
    void render();
    void present();

    void render_buffer(float* buffer);
    uint8_t get_gradient(size_t v);
    

private:
    SDL_Renderer* renderer{ nullptr };
    SDL_Window* window{ nullptr };
    SDL_Surface* surface{nullptr};
    SDL_Texture* texture{nullptr};
    SDL_Rect destr{0,0,Presets::WINDOW_WIDTH, Presets::WINDOW_HEIGHT};
    std::array<SDL_Color, Presets::Rendering::PALETTE_COLORS_COUNT> colors_palett;
    void build_colors_palett();
    double time_accumulator{0.0};
};

