#pragma once
#include <SDL.h>
#include <string>


namespace Presets {
	constexpr float FPS_CAP = 60.0F;
	constexpr float FPS_CAP_INTERV_MS = 1000.0f/FPS_CAP;

	constexpr size_t WINDOW_WIDTH = 600;
	constexpr size_t WINDOW_HEIGHT = 400;

	const std::string WINDOW_NAME{"FractalViewer"};

	struct Sim {
		static constexpr size_t ITERATIONS{50};
	};
}

