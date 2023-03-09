#pragma once
#include <SDL.h>
#include <string>
#include "Maths.h"


namespace Presets {
	constexpr auto FPS_CAP = 200.0;
	constexpr auto FPS_CAP_INTERVAL = 1.0/FPS_CAP;

	constexpr size_t WINDOW_WIDTH = 600;
	constexpr size_t WINDOW_HEIGHT = 400;
	constexpr size_t WINDOW_DEPTH = 32;
	constexpr double ASPECT_RATIO = static_cast<double>(WINDOW_WIDTH) / static_cast<double>(WINDOW_HEIGHT);

	const std::string WINDOW_NAME{"FractalViewer"};

	struct Sim {
		static constexpr size_t ITERATIONS{150};
		static constexpr size_t BUFFER_SIZE = WINDOW_WIDTH * WINDOW_HEIGHT;
		static constexpr size_t THREADS_COUNT{10};
		static constexpr size_t LINES_PER_THREAD{WINDOW_HEIGHT / THREADS_COUNT};
		static constexpr bool ROTATE_CONSTANT{false};
		
		static constexpr double CONSTANT_R{-0.544531};
		static constexpr double CONSTANT_I{0.56911};
		// static constexpr double CONSTANT_R{-0.547831};
		// static constexpr double CONSTANT_I{0.56711};

		static constexpr double CAM_X{0};
		static constexpr double CAM_Y{0};
		
		static constexpr double CONSTANT_MAG{0.7885};
		static constexpr double CONSTANT_FI_ROTSPEED{0.1};
		static constexpr double ZOOM_SPEED{0.6};
		static constexpr double INITIAL_SIM_TIME{0};
		
	};

	struct Rendering {
		static constexpr size_t PALETTE_COLORS_COUNT{Sim::ITERATIONS};
		static constexpr size_t PALETTE_COLORS_THR{32};
		static constexpr size_t PALETTE_SHIFT_DEGREES{150};
		static constexpr bool USE_CACHED_PALLET{true};

	};

	struct Utils {
		static constexpr double FPS_PRINT_INTERVAL{5.0};
	};
}

