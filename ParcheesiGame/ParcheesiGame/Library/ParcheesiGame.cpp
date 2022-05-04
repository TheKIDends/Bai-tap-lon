#include "ParcheesiGame.h"

bool ParcheesiGame::checkIdInStartPosition(int idPosition) {
    for (int i = 0; i < 4; ++i)
        if (idPosition == idStartPosition[i]) return true;
    return false;
}

int ParcheesiGame::idMoveForward(int idPosition) {
    int nextIdPosition = idPosition + 1;
    if (nextIdPosition > 71) nextIdPosition -= 56;
    if (checkIdInStartPosition(nextIdPosition)) { ++nextIdPosition; }
    if (nextIdPosition > 71) nextIdPosition -= 56;
    return nextIdPosition;
}

void ParcheesiGame::buildMap() {
    idStartPosition[0] = 16;
    idStartPosition[1] = 30;
    idStartPosition[2] = 44;
    idStartPosition[3] = 58;

    // Start green
    mapChessBoard[0] = { 433, 478 };
    mapChessBoard[1] = { 630, 478 };
    mapChessBoard[2] = { 532, 421 };
    mapChessBoard[3] = { 532, 534 };

    // Start yellow
    mapChessBoard[4] = { 895, 210 };
    mapChessBoard[5] = { 895, 323 };
    mapChessBoard[6] = { 796, 265 };
    mapChessBoard[7] = { 993, 265 };

    // Start red
    mapChessBoard[8]  = { 436,   56 };
    mapChessBoard[9]  = { 633,   56 };
    mapChessBoard[10] = { 535,  113 };
    mapChessBoard[11] = { 535,   -1 };

    // Start blue 
    mapChessBoard[12] = {  74, 264 };
    mapChessBoard[13] = { 271, 264 };
    mapChessBoard[14] = { 173, 209 };
    mapChessBoard[15] = { 173, 322 };

    int dx =  33, dy = 19;
    int  x = 334,  y = 420;

    for (int i = 16; i <= 22; ++i) {
        mapChessBoard[i] = { x, y };
        x += dx; y -= dy;
    }

    x -= dx; y += dy;
    for (int i = 23; i <= 28; ++i) {
        x += dx; y += dy;
        mapChessBoard[i] = { x, y };
    }

    x += dx; y -= dy;
    mapChessBoard[29] = { x, y - 6 }; //  yellow

    x += dx; y -= dy;
    mapChessBoard[30] = { x, y };

    for (int i = 31; i <= 36; ++i) {
        x -= dx; y -= dy;
        mapChessBoard[i] = { x, y };
    }

    for (int i = 37; i <= 42; ++i) {
        x += dx; y -= dy;
        mapChessBoard[i] = { x, y };
    }

    x -= dx; y -= dy + 3;
    mapChessBoard[43] = { x, y - 8 }; // red

    x -= dx; y -= dy + 3;
    mapChessBoard[44] = { x, y };

    for (int i = 45; i <= 50; ++i) {
        x -= dx; y += dy;
        mapChessBoard[i] = { x, y };
    }

    for (int i = 51; i <= 56; ++i) {
        x -= dx; y -= dy;
        mapChessBoard[i] = { x, y };
    }

    x -= dx; y += dy + 3;
    mapChessBoard[57] = { x + 4, y - 7 }; // blue

    x -= dx; y += dy;
    mapChessBoard[58] = { x, y };

    for (int i = 59; i <= 64; ++i) {
        x += dx; y += dy;
        mapChessBoard[i] = { x, y };
    }

    for (int i = 65; i <= 70; ++i) {
        x -= dx; y += dy;
        mapChessBoard[i] = { x, y };
    }

    x += dx; y += dy;
    mapChessBoard[71] = { x, y - 3 }; // green
}

void ParcheesiGame::setGameObject() {
    playerTurn = 0;

    mouse = new MouseEvents;
    dice = new Dice;

    buildMap();

    for (int i = 0; i < 4; ++i) player[i] = new Player;
    player[0]->setAvatarPlayer({  18, 551, 110, 115 }, 128, 138, "Image/green_avatar.png");
    player[1]->setAvatarPlayer({ 972, 551, 110, 115 }, 128, 138, "Image/yellow_avatar.png");
    player[2]->setAvatarPlayer({ 972,  18, 110, 115 }, 128, 138, "Image/red_avatar.png");
    player[3]->setAvatarPlayer({  18,  18, 110, 115 }, 128, 138, "Image/blue_avatar.png");

    // Set chess image
    int clipPosition_y = 0;
    for (int i = 0; i < 4; ++i) {
        player[i]->setAllChessPlayer(35, 64, { 0, clipPosition_y, 54, 99 }, "Image/chess.png");
        clipPosition_y += 99;
    }

    // Set chess start position
    int idPositionChess = 0;
    for (int i = 0; i < 4; ++i) {
        for (int chess = 0; chess < 4; ++chess) player[i]->setIdPositionChess(chess, idPositionChess++);
    }

    // Set button
    playButton.setButton({ int(SCREEN_WIDTH / 2.7), int(SCREEN_HEIGHT / 2.5) , 1326 / 5, 515 / 5 }, 1326, 515, "Image/play_button.png");
    
    exitButton.setButton({ int(SCREEN_WIDTH / 2.55) , int(SCREEN_HEIGHT / 1.55), 1326 / 6, 515 / 6 }, 1326, 515, "Image/exit_button.png");

    _2playersButton.setButton({ int(SCREEN_WIDTH / 2.9), int(SCREEN_HEIGHT / 4), 1560 / 5, 513 / 5 }, 1560, 513, "Image/2_players_button.png");

    _3playersButton.setButton({ int(SCREEN_WIDTH / 2.9), int(SCREEN_HEIGHT / 2.17), 1560 / 5, 513 / 5 }, 1560, 513, "Image/3_players_button.png");

    _4playersButton.setButton({ int(SCREEN_WIDTH / 2.9), int(SCREEN_HEIGHT / 1.5), 1560 / 5, 513 / 5 }, 1560, 513, "Image/4_players_button.png");

    backButton.setButton({ int(SCREEN_WIDTH / 1.1), int(SCREEN_HEIGHT / 1.18), 448 / 6, 497 / 6 }, 448, 497, "Image/back_button.png");

    rollButton.setButton({ 150, 10, 448 / 6, 497 / 6 }, 448, 497, "Image/back_button.png");
}

bool ParcheesiGame::idChessInLayer(int idPositionChess, int layer) {
    switch (layer) {
        case 1:
            if (16 <= idPositionChess && idPositionChess <= 28) return true;
            break;
        case 2:
            if (idPositionChess == 29 || idPositionChess == 71) return true;
            break;
        case 3:
            if (30 <= idPositionChess && idPositionChess <= 36) return true;
            if (64 <= idPositionChess && idPositionChess <= 70) return true;
            break;
        case 4:
            if (37 <= idPositionChess && idPositionChess <= 42) return true;
            if (58 <= idPositionChess && idPositionChess <= 63) return true;
            break;
        case 5:
            if (43 == idPositionChess || idPositionChess == 57) return true;
            break;
        case 6:
            if (44 <= idPositionChess && idPositionChess <= 56) return true;
            break;
        case 7:
            if (0 <= idPositionChess && idPositionChess <= 15) return true;
            break;
    }
    return false;
}

void ParcheesiGame::displayMenu() {
    // Back ground display menu
    //windowRenderer->loadBackGround("Image/background.png");

    // Load button 
    windowRenderer->loadButton(playButton);
    windowRenderer->loadButton(exitButton);   
}

void ParcheesiGame::displayPlayerNumberSelection() {
    // Back ground display player number selection
    //windowRenderer->loadBackGround("Image/background.png");

    //// Load button 
    windowRenderer->loadButton(backButton);
    windowRenderer->loadButton(_2playersButton);
    windowRenderer->loadButton(_3playersButton);
    windowRenderer->loadButton(_4playersButton);
}

void ParcheesiGame::animationMoveChess() {
    int idPositionChess = chessAnimation.getIdPosition();
    int chess = chessAnimation.getChess();
    int state = chessAnimation.getState();
    int position_x = mapChessBoard[idPositionChess].first;
    int position_y = mapChessBoard[idPositionChess].second;

    int nextIdPositionChess = idMoveForward(idPositionChess);

    int nextPosition_x = mapChessBoard[nextIdPositionChess].first;
    int nextPosition_y = mapChessBoard[nextIdPositionChess].second;

    switch (state) {
        case 0:
            windowRenderer->loadChess(position_x, position_y, player[playerTurn]->getChess(chess), state);
            break;

        case 1:
            windowRenderer->loadChess(position_x, position_y, player[playerTurn]->getChess(chess), state);
            break;

        case 2:
            windowRenderer->loadChess((position_x + nextPosition_x) / 2, (position_y + nextPosition_y) / 2, player[playerTurn]->getChess(chess), state);
            break;

        //case 3:
        //    windowRenderer->loadChess(nextPosition_x, nextPosition_y, player[playerTurn]->getChess(chess), 1);
        //    break;
    }

    if (state == chessAnimation.getMaxState() - 1) {
        player[playerTurn]->setIdPositionChess(chess, nextIdPositionChess);

        if (nextIdPositionChess == chessAnimation.getEndIdPosition()) { chessAnimation.finishAnimations(); return; }
        chessAnimation.setIdPosition(nextIdPositionChess);
        
    }
    
    chessAnimation.nextState();
}

void ParcheesiGame::displayGame() {
    // Back ground display game
    //windowRenderer->loadBackGround("Image/background.png");

    // Set chess
    for (int i = 0; i < 4; ++i) {
        for (int chess = 0; chess < 4; ++chess) {
            int idPositionChess = player[i]->getChess(chess).getIdPositionChess();

            if (idPositionChess <= 15) continue;

            int nextIdPositionChess = idMoveForward(idPositionChess);

            if (mapChessBoard[idPositionChess].first < mapChessBoard[nextIdPositionChess].first) {
                player[i]->setPathImgChess(chess, "Image/chess.png");
            }
            else player[i]->setPathImgChess(chess, "Image/chess_rev.png");
        }
    }

    // Load avatar players
    for (int i = 0; i < numberPlayers; ++i) windowRenderer->loadAvatar(player[i]);

    // Load button 
    windowRenderer->loadButton(rollButton);

    // Load layers board
    int numLayers = 7;
    for (int layerBoard = numLayers; layerBoard >= 1; --layerBoard) {
        string pathChessBoard = string("Image/chess_board/img") + char(layerBoard + '0') + string(".png");
        windowRenderer->loadImgFullWindow(pathChessBoard);

        for (int i = 0; i < numberPlayers; ++i) {
            for (int chess = 0; chess < 4; ++chess) {
                int idPositionChess = player[i]->getChess(chess).getIdPositionChess();

                // Animation move chess
                if (chessAnimation.getAnimations() && i == playerTurn && chess == chessAnimation.getChess()) {
                    if (idChessInLayer(chessAnimation.getIdPosition(), layerBoard)) animationMoveChess();
                    continue;
                }
                
                if (idChessInLayer(idPositionChess, layerBoard)) {

                    // Load arrow
                    if (player[i]->getChess(chess).getCanMoveChess()) {
                        switch (arrowAnimations.getState()) {
                            case 0:
                                windowRenderer->loadArrow(mapChessBoard[idPositionChess].first + 11, mapChessBoard[idPositionChess].second + 5);
                                break;
                            case 1:
                                windowRenderer->loadArrow(mapChessBoard[idPositionChess].first + 11, mapChessBoard[idPositionChess].second + 8);
                                break;
                        }
                    }

                    // Load chess
                    windowRenderer->loadChess(mapChessBoard[idPositionChess].first, mapChessBoard[idPositionChess].second, player[i]->getChess(chess), 0);
                }
            }
        }
    }   

    arrowAnimations.nextState();
}

int ParcheesiGame::chessNextStep(int idPosition) {
    if (idPosition <= 15) {
        for (int chess = 0; chess < 4; ++chess) {
            int idPositionChess = player[playerTurn]->getChess(chess).getIdPositionChess();
            if (idStartPosition[playerTurn] == idPositionChess) return -1;
        }
        if (dice->getDice() == 6) return idStartPosition[playerTurn];
        return -1;
    }

    int nextIdPosition = idPosition;
    int step = dice->getDice();
    while (step--) {
        nextIdPosition = idMoveForward(nextIdPosition);

        for (int i = 0; i < numberPlayers; ++i) {
            if (!step && i != playerTurn) continue;

            for (int chess = 0; chess < 4; ++chess) {
                int idPositionChess = player[i]->getChess(chess).getIdPositionChess();
                if (nextIdPosition == idPositionChess) return -1;
            }
        }
    }

    return nextIdPosition;
}

bool ParcheesiGame::canMove() {
    for (int chess = 0; chess < 4; ++chess) {
        int idPositionChess = player[playerTurn]->getChess(chess).getIdPositionChess();
        if (chessNextStep(idPositionChess) != -1) return true;
    }
    return false;
}

void ParcheesiGame::eventsMenu() {
    playButton.setTypeButton(mouse->CheckMouseInButton(playButton));
    exitButton.setTypeButton(mouse->CheckMouseInButton(exitButton));

    if (events->type == SDL_MOUSEBUTTONDOWN) {
        if (playButton.getTypeButton()) display = PLAYER_NUMBER_SELECTION;
        if (exitButton.getTypeButton()) { SDL_Quit(); exit(1); }
    }
}

void ParcheesiGame::eventsPlayerNumberSelection() {
    backButton.setTypeButton(mouse->CheckMouseInButton(backButton));
    _2playersButton.setTypeButton(mouse->CheckMouseInButton(_2playersButton));
    _3playersButton.setTypeButton(mouse->CheckMouseInButton(_3playersButton));
    _4playersButton.setTypeButton(mouse->CheckMouseInButton(_4playersButton));

    if (events->type == SDL_MOUSEBUTTONDOWN) {
        if (backButton.getTypeButton()) { display = MENU; return; }
        if (_2playersButton.getTypeButton()) { display = GAME; numberPlayers = 2; return; }
        if (_3playersButton.getTypeButton()) { display = GAME; numberPlayers = 3; return; }
        if (_4playersButton.getTypeButton()) { display = GAME; numberPlayers = 4; return; }
    }
}

void ParcheesiGame::eventsGame() {
    if (chessAnimation.getAnimations()) return;

    rollButton.setTypeButton(mouse->CheckMouseInButton(rollButton));

    //cout << playerTurn << '\n';
    switch (statePlayer) {
        case ROLLDICE:
            if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
                if (mouse->CheckMouseInButton(rollButton)) {
                    dice->rollDice();
                    //
                    cout << dice->getDice()  << " dice" << '\n';
                    //
                    statePlayer = CHOOSECHESS;
                }
            }
            break;

        case CHOOSECHESS:
            if (!canMove()) {
                cout << "CAN NOT MOVE!!!\n";
                statePlayer = (dice->getDice() == 6) ? ROLLDICE : ENDTURN;
                break;
            }

            // Chess can move
            for (int chess = 0; chess < 4; ++chess) {
                if (player[playerTurn]->getCanMoveChess(chess)) continue;

                int idPositionChess = player[playerTurn]->getChess(chess).getIdPositionChess();
                if (chessNextStep(idPositionChess) != -1) player[playerTurn]->setCanMoveChess(chess, true);
            }

            if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
                for (int chess = 0; chess < 4; ++chess) {
                    if (!player[playerTurn]->getCanMoveChess(chess)) continue;

                    int idPositionChess = player[playerTurn]->getChess(chess).getIdPositionChess();
                    if (mouse->CheckMouseInChess(mapChessBoard[idPositionChess].first, mapChessBoard[idPositionChess].second, player[playerTurn]->getChess(chess))) {

                        // move chess                        
                        int nextStep = chessNextStep(idPositionChess);
                        if (nextStep != -1) {

                            if (idPositionChess > 15) {
                                chessAnimation.setIdPosition(idPositionChess);
                                chessAnimation.setChessAnimations(true, chess, nextStep);
                            }
                            else player[playerTurn]->setIdPositionChess(chess, nextStep);

                           
                            for (int chess1 = 0; chess1 < 4; ++chess1) {
                                player[playerTurn]->setCanMoveChess(chess1, false);
                            }

                            statePlayer = (dice->getDice() == 6) ? ROLLDICE : ENDTURN;
                            break;

                        }
                        
                    }
                }
            }

            break;

        case ENDTURN:
            //
            cout << "ENDTURN" << '\n';
            //
            playerTurn = (playerTurn + 1) % numberPlayers;
            statePlayer = ROLLDICE;
            break;
    }
}

void ParcheesiGame::startGame() {
    windowRenderer = new WindowRenderer;
    windowRenderer->createWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    setGameObject();

    FPS fpsTimer;

    display = GAME;

    bool quit = false;
    while (!quit) {
        cout << '*' << '\n';
        fpsTimer.start();

        // Load background
        windowRenderer->loadImgFullWindow(string("Image/background1/background-") + char(backgroundAnimations.getState() + '0') + string(".png"));
        backgroundAnimations.nextState();

        // Handle Events
        while (SDL_PollEvent(events)) {

            //User requests quit
            if (events->type == SDL_QUIT) {
                quit = true;
                break;
            }

            mouse->mouseHandleEvent();

            switch (display) {
                case MENU:
                    eventsMenu();
                    break;
                case PLAYER_NUMBER_SELECTION:
                    eventsPlayerNumberSelection();
                    break;
                case GAME:
                    eventsGame();
                    break;
            }
        }

        // Update game state, draw the current frame
        switch (display) {
            case MENU:
                displayMenu();
                break;
            case PLAYER_NUMBER_SELECTION:
                displayPlayerNumberSelection();
                break;
            case GAME:
                displayGame();
                break;
        }

        windowRenderer->displayImage();

        // FPS
        int real_time = fpsTimer.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND; // ms
        if (real_time < time_one_frame) {
            int delay_time = time_one_frame - real_time;
            if (delay_time >= 0) SDL_Delay(delay_time);
        }
    }

    windowRenderer->deleteWindow();
    SDL_Quit();
}