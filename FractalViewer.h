#pragma once
#include "Engine.h"
#include "Maths.h"
#include <vector>
#include <thread>

class FractalViewer: public Engine {
public:
	FractalViewer() : Engine() {
        buffer = new float[Presets::Sim::BUFFER_SIZE];
    };
    ~FractalViewer() {
        delete []buffer;
    }
	bool setup(size_t window_width, size_t window_height);
	virtual bool input(SDL_Event &ev) override;
	virtual void update(double dt) override;
	virtual void render(MainRenderer* renderer) override;

    Rect sim_area{{-1, -1}, {1, 1}};
    Point cam_center{Presets::Sim::CAM_X, Presets::Sim::CAM_Y};

    float* buffer {nullptr};
    double scale{1};
    int scale_mod = 0;
    Point translation_dir{0,0};
    double sim_time{Presets::Sim::INITIAL_SIM_TIME};
    bool animate {Presets::Sim::ROTATE_CONSTANT};
    Point constant {Presets::Sim::CONSTANT_R, Presets::Sim::CONSTANT_I};
    std::vector<std::thread> threads;
    static void draw_images_linee(std::vector<float>& line, Point& c, double zy, double zx_min, double zw);
};
