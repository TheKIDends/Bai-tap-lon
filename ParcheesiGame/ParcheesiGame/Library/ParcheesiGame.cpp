#include "ParcheesiGame.h"

void ParcheesiGame::displayMenu () {
    MouseEvents* mouse = new MouseEvents;
    mouse->mouseHandleEvent();

    // Back ground display menu
    windowRenderer->loadBackGround("Image/back_ground.png");

    // Create play button 
    Button* playButton = new Button;
    playButton->setButton({ int(SCREEN_WIDTH / 2.7), int (SCREEN_HEIGHT / 2.5) , 1326 / 5, 515 / 5 } , 1326, 515, "Image/play_button.png");
    bool typePlayButton = bool(mouse->CheckMouseInButton(playButton));
    windowRenderer->loadButton(typePlayButton, playButton);

    // Create exit button 
    Button* exitButton = new Button;
    exitButton->setButton( { int (SCREEN_WIDTH / 2.55) , int (SCREEN_HEIGHT / 1.55), 1326 / 6, 515 / 6 } , 1326, 515, "Image/exit_button.png");
    bool typeExitButton = bool(mouse->CheckMouseInButton(exitButton));
    windowRenderer->loadButton(typeExitButton, exitButton);

    if (events->type == SDL_MOUSEBUTTONDOWN) {
        if (typeExitButton) { SDL_Quit(); exit(1); }
    }

    if (events->type == SDL_MOUSEBUTTONDOWN) {
        if (typePlayButton) display = 1;
    }
}

void ParcheesiGame::displayPlayerNumberSelection() {
    MouseEvents* mouse = new MouseEvents;
    mouse->mouseHandleEvent();
     
    // Back ground display player number selection
    windowRenderer->loadBackGround("Image/back_ground.png");

    //// Create 2 players button 
    Button* _2playersButton = new Button;
    _2playersButton->setButton( { int (SCREEN_WIDTH / 2.9), int (SCREEN_HEIGHT / 4), 1560 / 5, 513 / 5 } , 1560, 513, "Image/2_players_button.png");
    bool type2PlayersButton = bool(mouse->CheckMouseInButton(_2playersButton));
    windowRenderer->loadButton(type2PlayersButton, _2playersButton);

    //// Create 3 players button 
    Button* _3playersButton = new Button;
    _3playersButton->setButton({ int(SCREEN_WIDTH / 2.9), int(SCREEN_HEIGHT / 2.17), 1560 / 5, 513 / 5 } , 1560, 513, "Image/3_players_button.png");
    bool type3PlayersButton = bool(mouse->CheckMouseInButton(_3playersButton));
    windowRenderer->loadButton(type3PlayersButton, _3playersButton);

    //// Create 4 players button 
    Button* _4playersButton = new Button;
    _4playersButton->setButton({ int (SCREEN_WIDTH / 2.9), int (SCREEN_HEIGHT / 1.5), 1560 / 5, 513 / 5 } , 1560, 513, "Image/4_players_button.png");
    bool type4PlayersButton = bool(mouse->CheckMouseInButton(_4playersButton));
    windowRenderer->loadButton(type4PlayersButton, _4playersButton);

    // Create back button 
    Button* backButton = new Button;
    backButton->setButton({ int(SCREEN_WIDTH / 1.1), int(SCREEN_HEIGHT / 1.18), 448 / 6, 497 / 6 } , 448, 497, "Image/back_button.png");
    bool typeBackButton = bool(mouse->CheckMouseInButton(backButton));
    windowRenderer->loadButton(typeBackButton, backButton);

    if (events->type == SDL_MOUSEBUTTONDOWN) {
        if (typeBackButton)     { display = 0; return; }
        if (type2PlayersButton) { numberOfPlayers = 2; display = 2; return; }
        if (type3PlayersButton) { numberOfPlayers = 3; display = 2; return; }
        if (type4PlayersButton) { numberOfPlayers = 4; display = 2; return; }
    }
}

void ParcheesiGame::displayGame() {
    // Back ground display game
    windowRenderer->loadBackGround("Image/back_ground.png");

    // Create chess board
    windowRenderer->loadChessBoard();
}

void ParcheesiGame::startGame() {
    windowRenderer = new WindowRenderer;
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
                    displayMenu();
                    break;

                case 1:
                    displayPlayerNumberSelection();
                    break;

                case 2:
                    displayGame();
                    break;
            }

            windowRenderer->displayImage();
        }
    }

    windowRenderer->deleteWindow();
    SDL_Quit();
}