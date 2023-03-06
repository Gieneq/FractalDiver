#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL.h>
#include <stdlib.h>

#include "Settings.h"
#include "FractalViewer.h"


int main(int argc, char* argv[]) {

    srand(time(NULL));
    FractalViewer engine;
    (void)argc;
    (void)argv;

    if (!engine.setup(Presets::WINDOW_WIDTH, Presets::WINDOW_HEIGHT))
        return EXIT_FAILURE;

    engine.loop();

    return EXIT_SUCCESS;
}


