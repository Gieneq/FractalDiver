#include "FractalViewer.h"


bool FractalViewer::setup(size_t window_width, size_t window_height) {
	auto result = Engine::setup(window_width, window_height);

	return result;
}



bool FractalViewer::input(SDL_Event& ev) {

	return false;
}

void FractalViewer::update(float dt) {

}


void FractalViewer::render(MainRenderer* renderer) {

}