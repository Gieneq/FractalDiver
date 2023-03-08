#pragma once
#include <SDL.h>

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <memory>

#include "Settings.h"
#include "Maths.h"
#include "MainRenderer.h"




class Engine {
public:
	Engine() = default;
	virtual ~Engine();

	bool setup(size_t window_width, size_t window_height);
	void loop();
	virtual bool input(SDL_Event& ev) { return false; };
	virtual void update(double dt) {};
	virtual void render(MainRenderer* r) {};

	size_t get_window_width();
	size_t get_window_height();
	double true_fps{Presets::FPS_CAP};


protected:
	MainRenderer renderer;

private:
	SDL_Window * window{ nullptr };

	double fps_eval_accumulator{0};
	size_t fps_eval_iterations{0};
};