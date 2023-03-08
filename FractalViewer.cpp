#include "FractalViewer.h"


bool FractalViewer::setup(size_t window_width, size_t window_height) {
	auto result = Engine::setup(window_width, window_height);
    
    for(size_t i{0}; i<Presets::Sim::BUFFER_SIZE; ++i) {
        buffer[i] = 0.0F;
    }
	return result;
}



bool FractalViewer::input(SDL_Event& ev) {

    /* Navigation */
    if (ev.type == SDL_KEYDOWN) {
		auto sym = ev.key.keysym.sym;

        if(sym == SDLK_w)
			translation_dir.y = -1.0;
        if(sym == SDLK_a)
			translation_dir.x = -1.0;
        if(sym == SDLK_s)
			translation_dir.y = 1.0;
        if(sym == SDLK_d)
			translation_dir.x = 1.0;

        if(translation_dir.x != 0.0 || translation_dir.y != 0.0)
            translation_dir.normalize();
            
        if(sym == SDLK_SPACE)
			scale_mod = 1;
        else if(sym == SDLK_LSHIFT)
			scale_mod = -1;

	} else if (ev.type == SDL_KEYUP) {
		auto sym = ev.key.keysym.sym;
        if(sym == SDLK_w)
			translation_dir.y = 0.0;
        if(sym == SDLK_a)
			translation_dir.x = 0.0;
        if(sym == SDLK_s)
			translation_dir.y = 0.0;
        if(sym == SDLK_d)
			translation_dir.x = 0.0;

        if(sym == SDLK_SPACE || sym == SDLK_LSHIFT)
			scale_mod = 0;
    }

    /* Utils */
    if (ev.type == SDL_KEYUP) {
        if(ev.key.keysym.sym == SDLK_p)
            animate = !animate;

        if(ev.key.keysym.sym == SDLK_i) {
            std::cout << "Informations" << std::endl;
            std::cout << "FPS:   " << true_fps << std::endl;
            std::cout << "Const: " << constant << std::endl;
            std::cout << "Rect:  " << sim_area << std::endl;
            std::cout << "Cam:   " << cam_center << std::endl;
            std::cout << "Scale: " << scale << std::endl;
            std::cout << "Time:  " << sim_time << std::endl;
        }
    }

	return false;
}


void draw_images_line(float* line, size_t elements_x, size_t elements_y, const Point& c, double zx_min, double zw, double zy_min, double zh) {
    double elementsx_d = static_cast<double>(elements_x);
    double elementsy_d = static_cast<double>(elements_y);
    for(size_t iy{0U}; iy < elements_y; ++iy) {
        double zy = zy_min + zh * double(iy) / elementsy_d;
        for(size_t ix{0U}; ix < elements_x; ++ix) {
            double zx = zx_min + zw * double(ix) / elementsx_d;
            Point z0{zx, zy};
            line[iy * elements_x + ix] = computer_iterations(z0, c, Presets::Sim::ITERATIONS);
        }
    }
}

void donothing() {
    
}

void FractalViewer::update(double dt) {
    scale *= 1.0 + scale_mod * Presets::Sim::ZOOM_SPEED * dt;
    cam_center.x += translation_dir.x*(1.0/scale)* dt;
    cam_center.y += translation_dir.y*(1.0/scale)* dt;
    
    sim_area.x = cam_center.x - 1.0/scale;
    sim_area.y = cam_center.y - 1.0/scale;
    sim_area.w = 2.0/scale;
    sim_area.h = 2.0/scale;

    if (animate) {
        constant.x =  Presets::Sim::CONSTANT_MAG * cos(Presets::Sim::CONSTANT_FI_ROTSPEED * sim_time * 2.0*M_PI);
        constant.y =  Presets::Sim::CONSTANT_MAG * sin(Presets::Sim::CONSTANT_FI_ROTSPEED * sim_time * 2.0*M_PI);
    }

    double zh = sim_area.h / static_cast<double>(Presets::Sim::THREADS_COUNT);

    for(size_t i_thread{0}; i_thread < Presets::Sim::THREADS_COUNT; ++i_thread) {
        size_t iy = i_thread * Presets::Sim::LINES_PER_THREAD;
        float* start_buffer = buffer + iy * Presets::WINDOW_WIDTH;
        double zy = sim_area.y + sim_area.h * static_cast<double>(i_thread) / static_cast<double>(Presets::Sim::THREADS_COUNT);
        threads.push_back(std::thread(draw_images_line, start_buffer, Presets::WINDOW_WIDTH, Presets::Sim::LINES_PER_THREAD, constant, sim_area.x, sim_area.w, zy, zh));
    }

    for (size_t i = 0; i < Presets::Sim::THREADS_COUNT; i++) {
        threads[i].join();
    }
    threads.clear();
    // for(size_t iy{0}; iy<Presets::WINDOW_HEIGHT; iy += Presets::Sim::THREADS_COUNT) {
    //     for(size_t iyt{0}; iyt < Presets::Sim::THREADS_COUNT; ++iyt) {
    //         auto i = iy + iyt;
    //         double fy = static_cast<double>(i) / static_cast<double>(Presets::WINDOW_HEIGHT);
    //         double zy = fy * sim_area.h + sim_area.y;
    //         threads.push_back(std::thread(draw_images_line, buffer + i * Presets::WINDOW_WIDTH , Presets::WINDOW_WIDTH, constant, zy, sim_area.x, sim_area.w));
    //         // threads.push_back(std::thread(donothing));
    //     }
    //     // draw_images_line(buffer[iy], constant, zy, sim_area.x, sim_area.w);
    //     for (size_t i = 0; i < Presets::Sim::THREADS_COUNT; i++) {
    //         threads[i].join();
    //     }
    //     threads.clear();
    // }




    if(animate) {
        sim_time += dt;
    }
}


void FractalViewer::render(MainRenderer* renderer) {
     renderer->render_buffer(buffer);
}