#pragma once
#include <SDL.h>

#include <string>
#include <vector>
#include <iostream>
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
	virtual void update(float dt) {};
	virtual void render(MainRenderer* r) {};

	size_t get_window_width();
	size_t get_window_height();

protected:
	MainRenderer renderer;

private:
	SDL_Window * window{ nullptr };
};