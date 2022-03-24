#include "ParcheesiGame.h"

void ParcheesiGame::startGame() {
    WindowRenderer* windowRenderer = new WindowRenderer;
    windowRenderer->createWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    windowRenderer->loadImage();

    SDL_Event events;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&events)) {
            //User requests quit
            if (events.type == SDL_QUIT) {
                quit = true;
                break;
            }


        }
    }

    windowRenderer->deleteWindow();
}