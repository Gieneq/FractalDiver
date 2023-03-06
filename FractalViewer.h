#pragma once
#include "Engine.h"

class FractalViewer: public Engine {
public:
	FractalViewer() : Engine() {};
	bool setup(size_t window_width, size_t window_height);
	virtual bool input(SDL_Event &ev) override;
	virtual void update(float dt) override;
	virtual void render(MainRenderer* renderer) override;
};
