#include "ParcheesiGame.h"

void ParcheesiGame::displayMenu (WindowRenderer* windowRenderer) {
    MouseEvents* mouse = new MouseEvents;
    mouse->mouseHandleEvent();

    // Back ground menu
    windowRenderer->loadBackGround("Image/back_ground_menu");

    // Create play button 
    Button* playButton = new Button;
    playButton->setButton(1747.0 * 0.63 / 2.7, 1086.0 * 0.63 / 2.5, 1326 / 5, 505 / 5, "Image/play_button");
    bool typePlayButton = bool(mouse->CheckMouseInButton(playButton));
    windowRenderer->loadButton(typePlayButton, playButton);

    // Create exit button 
    Button* exitButton = new Button;
    exitButton->setButton(1747.0 * 0.63 / 2.55, 1086.0 * 0.63 / 1.6, 1326 / 6, 505 / 6, "Image/exit_button");
    bool typeExitButton = bool(mouse->CheckMouseInButton(exitButton));
    windowRenderer->loadButton(typeExitButton, exitButton);

    if (events->type == SDL_MOUSEBUTTONDOWN) {
        if (typeExitButton) {
            SDL_Quit();
            exit(1);
        }
    }

    if (events->type == SDL_MOUSEBUTTONDOWN) {
        if (typePlayButton) display = 1;
    }
}

void ParcheesiGame::displayGame(WindowRenderer* windowRenderer) {
    // Back ground menu
    windowRenderer->loadBackGround("Image/back_ground_menu");

    // Create chess board
    windowRenderer->loadChessBoard();
}

void ParcheesiGame::startGame() {
    WindowRenderer* windowRenderer = new WindowRenderer;
    windowRenderer->createWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    display = 0;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(events)) {
            //User requests quit
            if (events->type == SDL_QUIT) {
                quit = true;
                break;
            }

            switch (display) {
                case 0:
                    displayMenu(windowRenderer);
                    break;

                case 1:
                    displayGame(windowRenderer);
                    break;
            }

            windowRenderer->displayImage();
        }
    }

    windowRenderer->deleteWindow();
    SDL_Quit();
}