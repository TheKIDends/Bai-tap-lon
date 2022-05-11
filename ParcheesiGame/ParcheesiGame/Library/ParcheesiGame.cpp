#include "ParcheesiGame.h"

bool ParcheesiGame::checkIdInStartPosition(int idPosition) {
    for (int idPlayer = 0; idPlayer < 4; ++idPlayer)
        if (idPosition == idStartPosition[idPlayer]) return true;
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
    mapChessboard[0] = { 433, 478 };
    mapChessboard[1] = { 630, 478 };
    mapChessboard[2] = { 532, 421 };
    mapChessboard[3] = { 532, 534 };

    // Start yellow
    mapChessboard[4] = { 895, 210 };
    mapChessboard[5] = { 895, 323 };
    mapChessboard[6] = { 796, 265 };
    mapChessboard[7] = { 993, 265 };

    // Start red
    mapChessboard[8] = { 436,   56 };
    mapChessboard[9] = { 633,   56 };
    mapChessboard[10] = { 535,  113 };
    mapChessboard[11] = { 535,   -1 };

    // Start blue 
    mapChessboard[12] = { 74, 264 };
    mapChessboard[13] = { 271, 264 };
    mapChessboard[14] = { 173, 209 };
    mapChessboard[15] = { 173, 322 };

    int dx = 33, dy = 19;
    int  x = 334, y = 420;

    for (int i = 16; i <= 22; ++i) {
        mapChessboard[i] = { x, y };
        x += dx; y -= dy;
    }

    x -= dx; y += dy;
    for (int i = 23; i <= 28; ++i) {
        x += dx; y += dy;
        mapChessboard[i] = { x, y };
    }

    x += dx; y -= dy;
    mapChessboard[29] = { x, y - 6 }; //  yellow

    x += dx; y -= dy;
    mapChessboard[30] = { x, y };

    for (int i = 31; i <= 36; ++i) {
        x -= dx; y -= dy;
        mapChessboard[i] = { x, y };
    }

    for (int i = 37; i <= 42; ++i) {
        x += dx; y -= dy;
        mapChessboard[i] = { x, y };
    }

    x -= dx; y -= dy + 3;
    mapChessboard[43] = { x, y - 8 }; // red

    x -= dx; y -= dy + 3;
    mapChessboard[44] = { x, y };

    for (int i = 45; i <= 50; ++i) {
        x -= dx; y += dy;
        mapChessboard[i] = { x, y };
    }

    for (int i = 51; i <= 56; ++i) {
        x -= dx; y -= dy;
        mapChessboard[i] = { x, y };
    }

    x -= dx; y += dy + 3;
    mapChessboard[57] = { x + 4, y - 7 }; // blue

    x -= dx; y += dy;
    mapChessboard[58] = { x, y };

    for (int i = 59; i <= 64; ++i) {
        x += dx; y += dy;
        mapChessboard[i] = { x, y };
    }

    for (int i = 65; i <= 70; ++i) {
        x -= dx; y += dy;
        mapChessboard[i] = { x, y };
    }

    x += dx; y += dy;
    mapChessboard[71] = { x, y - 3 }; // green
}

void ParcheesiGame::setGameComponents() {
    playerTurn = 0;

    mouse = new MouseEvents;

    buildMap();

    // Set background
    background.setObject({ 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT }, { 0, 0, 1494, 840 }, "Image/background.png");
    windowRenderer->rendererTexture(&background);

    // Set avatar
    player[0].setAvatarPlayer({  18, 551, 110, 115 }, { 0, 0, 128, 138 }, "Image/green_avatar.png");
    player[1].setAvatarPlayer({ 972, 551, 110, 115 }, { 0, 0, 128, 138 }, "Image/yellow_avatar.png");
    player[2].setAvatarPlayer({ 972,  18, 110, 115 }, { 0, 0, 128, 138 }, "Image/red_avatar.png");
    player[3].setAvatarPlayer({  18,  18, 110, 115 }, { 0, 0, 128, 138 }, "Image/blue_avatar.png");
    for (int idPlayer = 0; idPlayer < 4; ++idPlayer) windowRenderer->rendererTexture(&player[idPlayer]);

    // Set chess image
    int clipPosition_y = 0;
    for (int idPlayer = 0; idPlayer < 4; ++idPlayer) {
        player[idPlayer].setAllChessPlayer({ 0, 0, 35, 64 }, { 0, clipPosition_y, 54, 99 }, "Image/chess.png");
        
        for (int idChess = 0; idChess < 4; ++idChess)
            windowRenderer->rendererTexture(player[idPlayer].getChessIterator(idChess));

        clipPosition_y += 99;
    }

    // Set chess start position
    int idPosition = 0;
    for (int idPlayer = 0; idPlayer < 4; ++idPlayer) {
        for (int idChess = 0; idChess < 4; ++idChess) {
            player[idPlayer].setStartIdChess(idChess, idPosition++);
        }
    }               

    // Set chessboard
    chessboard.setObject({0, 0, SCREEN_WIDTH , SCREEN_HEIGHT }, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, "Image/chessboard.png");
    windowRenderer->rendererTexture(&chessboard);

    // Set dice back
    backDice.setObject({ 150, 540, 160 , 132 }, { 0, 0, 160, 132 }, "Image/dice/dice_back.png");
    //backDice.setObject({ 792, 540, 160 , 132 }, { 0, 0, 160, 132 }, "Image/dice/dice_back.png");
    //backDice.setObject({ 792, 5, 160 , 132 }, { 0, 0, 160, 132 }, "Image/dice/dice_back.png");
    //backDice.setObject({ 150, 5, 160 , 132 }, { 0, 0, 160, 132 }, "Image/dice/dice_back.png");
    windowRenderer->rendererTexture(&backDice);

    // Set Dice
    dice.setObject({ 0, 0, 0 , 0 }, { 0, 150, 150, 150 }, "Image/dice/dice.png");
    windowRenderer->rendererTexture(&dice);

    // Set button
    playButton.setObject({ int(SCREEN_WIDTH /  2.7), int(SCREEN_HEIGHT /  2.5) , 1326 / 5, 515 / 5 }, { 0, 0, 1326, 515 }, "Image/play_button.png");
    exitButton.setObject({ int(SCREEN_WIDTH / 2.55) , int(SCREEN_HEIGHT / 1.55), 1326 / 6, 515 / 6 }, { 0, 0, 1326, 515 }, "Image/exit_button.png");
    _2playersButton.setObject({ int(SCREEN_WIDTH / 2.9), int(SCREEN_HEIGHT / 4), 1560 / 5, 513 / 5 }, { 0, 0, 1560, 513 }, "Image/2_players_button.png");
    _3playersButton.setObject({ int(SCREEN_WIDTH / 2.9), int(SCREEN_HEIGHT / 2.17), 1560 / 5, 513 / 5 }, { 0, 0, 1560, 513 }, "Image/3_players_button.png");
    _4playersButton.setObject({ int(SCREEN_WIDTH / 2.9), int(SCREEN_HEIGHT /  1.5), 1560 / 5, 513 / 5 }, { 0, 0, 1560, 513 }, "Image/4_players_button.png");
    backButton.setObject({ int(SCREEN_WIDTH / 1.1), int(SCREEN_HEIGHT / 1.18), 448 / 6, 497 / 6 }, { 0, 0, 448, 497 }, "Image/back_button.png");
    
    windowRenderer->rendererTexture(&playButton);
    windowRenderer->rendererTexture(&exitButton);
    windowRenderer->rendererTexture(&_2playersButton);
    windowRenderer->rendererTexture(&_3playersButton);
    windowRenderer->rendererTexture(&_4playersButton);
    windowRenderer->rendererTexture(&backButton);
}

bool ParcheesiGame::checkIdChessInLayer(int idPositionChess, int layer) {
    switch (layer) {
        case 0:
            if (16 <= idPositionChess && idPositionChess <= 28) return true;
            break;
        case 1:
            if (idPositionChess == 29 || idPositionChess == 71) return true;
            break;
        case 2:
            if (30 <= idPositionChess && idPositionChess <= 36) return true;
            if (64 <= idPositionChess && idPositionChess <= 70) return true;
            break;
        case 3:
            if (37 <= idPositionChess && idPositionChess <= 42) return true;
            if (58 <= idPositionChess && idPositionChess <= 63) return true;
            break;
        case 4:
            if (43 == idPositionChess || idPositionChess == 57) return true;
            break;
        case 5:
            if (44 <= idPositionChess && idPositionChess <= 56) return true;
            break;
        case 6:
            if (0 <= idPositionChess && idPositionChess <= 15) return true;
            break;
        }
    return false;
}

void ParcheesiGame::animationMoveChess() {
    int idPositionChess = chessAnimations.getIdPosition();
    int idChess = chessAnimations.getChess();
    int status  = chessAnimations.getStatus();
    int position_x = mapChessboard[idPositionChess].first;
    int position_y = mapChessboard[idPositionChess].second;

    int nextIdPositionChess = idMoveForward(idPositionChess);

    int nextPosition_x = mapChessboard[nextIdPositionChess].first;
    int nextPosition_y = mapChessboard[nextIdPositionChess].second;

    switch (status) {
        case 0:
            windowRenderer->loadChess(position_x, position_y, player[playerTurn].getChess(idChess), status);
            break;

        case 1:
            windowRenderer->loadChess(position_x, position_y, player[playerTurn].getChess(idChess), status);
            break;

        case 2:
            windowRenderer->loadChess((position_x + nextPosition_x) / 2, (position_y + nextPosition_y) / 2, player[playerTurn].getChess(idChess), status);
            break;
    }

    if (status == chessAnimations.getMaxStatus() - 1) {
        player[playerTurn].setIdPositionChess(idChess, nextIdPositionChess);

        if (nextIdPositionChess == chessAnimations.getEndIdPosition()) { 
            
            // Kick chess
            for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
                if (idPlayer == playerTurn) continue;

                for (int idChess = 0; idChess < 4; ++idChess) {
                    if (player[idPlayer].getIdPositionChess(idChess) == nextIdPositionChess) {
                        player[idPlayer].setIdPositionChess(idChess, player[idPlayer].getStartIdChess(idChess));
                        break;
                    }
                }
            }

            chessAnimations.finishAnimations(); 
            return; 
        }
        
        chessAnimations.setIdPosition(nextIdPositionChess);
    }

    chessAnimations.nextStatus();
}

void ParcheesiGame::animationRollDice() {
    windowRenderer->loadDiceAnimations(dice, diceAnimations.getStatus());

    if (diceAnimations.getStatus() == diceAnimations.getMaxStatus() - 1) {
        diceAnimations.finishAnimations();
        return;
    }

    diceAnimations.nextStatus();
}

// Display

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

void ParcheesiGame::displayGame() {
    // Set direction chess
    for (int idPlayer = 0; idPlayer < 4; ++idPlayer) {
        for (int idChess = 0; idChess < 4; ++idChess) {
            int idPositionChess = player[idPlayer].getIdPositionChess(idChess);

            if (idPositionChess <= 15) continue;

            int nextIdPositionChess = idMoveForward(idPositionChess);

            if (mapChessboard[idPositionChess].first < mapChessboard[nextIdPositionChess].first) {
                player[idPlayer].setDirectionChess(idChess, RIGHT);
            }
            else player[idPlayer].setDirectionChess(idChess, LEFT);
        }
    }

    // Load avatar players
    for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer)
        windowRenderer->loadAvatar(player[idPlayer]);

    // Load layers board
    for (int layerBoard = chessboard.getNumLayers() - 1; layerBoard >= 0; --layerBoard) {
        chessboard.setLayer(layerBoard);
        windowRenderer->loadChessboard(chessboard);

        for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
            for (int idChess = 0; idChess < 4; ++idChess) {
                int idPositionChess = player[idPlayer].getChess(idChess).getIdPosition();

                // Animation move chess
                if (chessAnimations.getAnimations() && idPlayer == playerTurn && idChess == chessAnimations.getChess()) {
                    if (checkIdChessInLayer(chessAnimations.getIdPosition(), layerBoard)) animationMoveChess();
                    continue;
                }

                if (checkIdChessInLayer(idPositionChess, layerBoard)) {

                    // Load arrow
                    if (player[idPlayer].getChess(idChess).getCanMoveChess()) {
                        switch (arrowAnimations.getStatus()) {
                            case 0:
                                windowRenderer->loadArrow(mapChessboard[idPositionChess].first + 11, mapChessboard[idPositionChess].second + 5);
                                break;
                            case 1:
                                windowRenderer->loadArrow(mapChessboard[idPositionChess].first + 11, mapChessboard[idPositionChess].second + 8);
                                break;
                        }
                    }

                    // Load chess
                    windowRenderer->loadChess(mapChessboard[idPositionChess].first, mapChessboard[idPositionChess].second, player[idPlayer].getChess(idChess), 0);
                }
            }
        }
    }

    arrowAnimations.nextStatus();

    // Set Dice
    if (playerTurn == 0) dice.setRect({ 189, 550, 110 , 110 }); else
    if (playerTurn == 1) dice.setRect({ 800, 550, 110 , 110 }); else
    if (playerTurn == 2) dice.setRect({ 800,  13, 110 , 110 }); else
    if (playerTurn == 3) dice.setRect({ 189,  13, 110 , 110 });

    // Dice
    windowRenderer->loadBackDice(backDice, playerTurn);

    if (diceAnimations.getAnimations()) animationRollDice();
    else windowRenderer->loadDice(dice);
}

int ParcheesiGame::chessNextStep(int idPosition) {
    if (idPosition <= 15) {
        for (int idChess = 0; idChess < 4; ++idChess) {
            int idPositionChess = player[playerTurn].getIdPositionChess(idChess);
            if (idStartPosition[playerTurn] == idPositionChess) return -1;
        }
        if (dice.getNumDice() == 6) return idStartPosition[playerTurn];
        return -1;
    }

    int nextIdPosition = idPosition;
    int step = dice.getNumDice();
    while (step--) {
        nextIdPosition = idMoveForward(nextIdPosition);

        for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
            if (!step && idPlayer != playerTurn) continue;

            for (int idChess = 0; idChess < 4; ++idChess) {
                int idPositionChess = player[idPlayer].getIdPositionChess(idChess);
                if (nextIdPosition == idPositionChess) return -1;
            }
        }
    }

    return nextIdPosition;
}

bool ParcheesiGame::canMove() {
    for (int chess = 0; chess < 4; ++chess) {
        int idPositionChess = player[playerTurn].getIdPositionChess(chess);
        if (chessNextStep(idPositionChess) != -1) return true;
    }
    return false;
}

void ParcheesiGame::eventsMenu() {
    playButton.setStatus(mouse->CheckMouseInButton(playButton));
    exitButton.setStatus(mouse->CheckMouseInButton(exitButton));

    if (events->type == SDL_MOUSEBUTTONDOWN) {
        if (playButton.getStatus() == ON_CLICK) display = PLAYER_NUMBER_SELECTION;
        if (exitButton.getStatus() == ON_CLICK) { SDL_Quit(); exit(1); }
    }
}

void ParcheesiGame::eventsPlayerNumberSelection() {
    backButton.setStatus(mouse->CheckMouseInButton(backButton));
    _2playersButton.setStatus(mouse->CheckMouseInButton(_2playersButton));
    _3playersButton.setStatus(mouse->CheckMouseInButton(_3playersButton));
    _4playersButton.setStatus(mouse->CheckMouseInButton(_4playersButton));

    if (events->type == SDL_MOUSEBUTTONDOWN) {
        if (backButton.getStatus() == ON_CLICK) { display = MENU; return; }
        if (_2playersButton.getStatus() == ON_CLICK) { display = GAME; numberPlayers = 2; return; }
        if (_3playersButton.getStatus() == ON_CLICK) { display = GAME; numberPlayers = 3; return; }
        if (_4playersButton.getStatus() == ON_CLICK) { display = GAME; numberPlayers = 4; return; }
    }
}

void ParcheesiGame::eventsGame() {
    if (chessAnimations.getAnimations()) return;
    if (diceAnimations.getAnimations()) return;

    //cout << playerTurn << '\n';
    switch (statusPlayer) {
        case ROLLDICE:
            if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
                if (mouse->CheckMouseInDice(dice) == ON_CLICK) {
                    //int x;
                    //cin >> x;
                    //dice.setDice(x);
                    dice.rollDice();
                    diceAnimations.setDiceAnimations(true);
                    //
                    cout << dice.getNumDice() << " dice" << '\n';
                    //
                    statusPlayer = CHOOSECHESS;
                }
            }
            break;

        case CHOOSECHESS:
            if (!canMove()) {
                cout << "CAN NOT MOVE!!!\n";
                statusPlayer = (dice.getNumDice() == 6) ? ROLLDICE : ENDTURN;
                break;
            }

            // Chess can move
            for (int idChess = 0; idChess < 4; ++idChess) {
                if (player[playerTurn].getCanMoveChess(idChess)) continue;

                int idPositionChess = player[playerTurn].getIdPositionChess(idChess);
                if (chessNextStep(idPositionChess) != -1) player[playerTurn].setCanMoveChess(idChess, true);
            }

            if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
                for (int idChess = 0; idChess < 4; ++idChess) {
                    if (!player[playerTurn].getCanMoveChess(idChess)) continue;

                    int idPositionChess = player[playerTurn].getIdPositionChess(idChess);
                    if (mouse->CheckMouseInChess(mapChessboard[idPositionChess].first, mapChessboard[idPositionChess].second, player[playerTurn].getChessIterator(idChess))) {

                        // move chess               
                        int nextStep = chessNextStep(idPositionChess);
                        if (nextStep != -1) {

                            if (idPositionChess > 15) {
                                chessAnimations.setIdPosition(idPositionChess);
                                chessAnimations.setChessAnimations(true, idChess, nextStep);
                            }
                            else player[playerTurn].setIdPositionChess(idChess, nextStep);


                            for (int chess1 = 0; chess1 < 4; ++chess1) {
                                player[playerTurn].setCanMoveChess(chess1, false);
                            }

                            statusPlayer = (dice.getNumDice() == 6) ? ROLLDICE : ENDTURN;
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
            dice.setNumDice(0);
            statusPlayer = ROLLDICE;
            break;
    }
}

void ParcheesiGame::startGame() {
    windowRenderer = new WindowRenderer;
    windowRenderer->createWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    setGameComponents();

    FPS fpsTimer;

    display =  GAME;

    bool quit = false;
    while (!quit) {
        cout << '*' << '\n';
        fpsTimer.start();

        // Load background
        windowRenderer->loadBackground(background);
        background.nextLayer();

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

        // Update game status, draw the current frame
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