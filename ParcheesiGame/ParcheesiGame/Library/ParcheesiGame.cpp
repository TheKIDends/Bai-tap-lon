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

int ParcheesiGame::chessNextStep(int idPosition) {
    if (idPosition <= 15) {
        for (int idChess = 0; idChess < 4; ++idChess) {
            int idPositionChess = player[playerTurn].getChess_It(idChess)->getIdPosition();
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
                int idPositionChess = player[idPlayer].getChess_It(idChess)->getIdPosition();
                if (nextIdPosition == idPositionChess) return -1;
            }
        }
    }

    return nextIdPosition;
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

bool ParcheesiGame::canMove() {
    for (int idChess = 0; idChess < 4; ++idChess) {
        int idPosition = player[playerTurn].getChess_It(idChess)->getIdPosition();
        if (chessNextStep(idPosition) != -1) return true;
    }
    return false;
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

void ParcheesiGame::restartGame() {
    playerTurn = 0;
    statusPlayer = ROLL_DICE;
    
    // Reset chess start position
    int idPosition = 0;
    for (int idPlayer = 0; idPlayer < 4; ++idPlayer) {
        player[idPlayer].setWinner(false);
        for (int idChess = 0; idChess < 4; ++idChess) {
            player[idPlayer].getChess_It(idChess)->setStartId(idPosition++);
        }
    }

    // Resrt animations
    for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
        for (int idChess = 0; idChess < 4; ++idChess) {
            player[idPlayer].getChess_It(idChess)->finishAnimations();
        }
    }
    dice.setNumDice(0);
    dice.finishAnimations();
}

void ParcheesiGame::saveGame() {
    string filepath = "Save/save1.txt";
    ofstream ofs(filepath.c_str());

    ofs << playerTurn << '\n';

    for (int idPlayer = 0; idPlayer < 4; ++idPlayer) {
        ofs << player[idPlayer].getWinner() << '\n';
        for (int idChess = 0; idChess < 4; ++idChess) {
            ofs << player[idPlayer].getChess_It(idChess)->getIdPosition() << '\n';
        }
    }

    ofs.close();
}

void ParcheesiGame::setGameComponents() {
    restartGame();

    mouse = new Mouse;
    // Set mouse
    mouse->setObject({ 0, 0, 0, 0 }, { 0, 0, 512, 512 }, "Image/mouse.png");
    windowRenderer->loadTexture(mouse);

    buildMap();

    // Set background
    background.getFpsTime()->start();
    background.setObject({ 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT }, { 0, 0, 1494, 840 }, "Image/background.png");
    windowRenderer->loadTexture(&background);

    // Set arrow
    arrow.getFpsTime()->start();
    arrow.setArrow(3, DOWN, { 0, 0, 10, 10 }, {0, 0, 122, 98}, "Image/arrow.png");
    windowRenderer->loadTexture(&arrow);

    clickToRoll.getFpsTime()->start();
    clickToRoll.setArrow(7, LEFT, { 0, 0, 60, 60 }, { 0, 98, 98, 98 }, "Image/arrow.png");
    windowRenderer->loadTexture(&clickToRoll);

    // Set avatar
    player[0].setAvatarPlayer({  18, 551, 110, 115 }, { 0, 0, 128, 138 }, "Image/green_avatar.png");
    player[1].setAvatarPlayer({ 972, 551, 110, 115 }, { 0, 0, 128, 138 }, "Image/yellow_avatar.png");
    player[2].setAvatarPlayer({ 972,  18, 110, 115 }, { 0, 0, 128, 138 }, "Image/red_avatar.png");
    player[3].setAvatarPlayer({  18,  18, 110, 115 }, { 0, 0, 128, 138 }, "Image/blue_avatar.png");
    for (int idPlayer = 0; idPlayer < 4; ++idPlayer) windowRenderer->loadTexture(&player[idPlayer]);
    
    // Set chess image
    int clipPosition_y = 0;
    for (int idPlayer = 0; idPlayer < 4; ++idPlayer) {
        player[idPlayer].setAllChessPlayer({ 0, 0, 35, 64 }, { 0, clipPosition_y, 54, 99 }, "Image/chess.png");
        for (int idChess = 0; idChess < 4; ++idChess)
            windowRenderer->loadTexture(player[idPlayer].getChess_It(idChess));

        clipPosition_y += 99;
    }          

    // Start FPS Chess
    for (int idPlayer = 0; idPlayer < 4; ++idPlayer) {
        for (int idChess = 0; idChess < 4; ++idChess) {
            player[idPlayer].getChess_It(idChess)->getFpsTime()->start();
        }
    }

    // Set chessboard
    chessboard.setObject({0, 0, SCREEN_WIDTH , SCREEN_HEIGHT }, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, "Image/chessboard.png");
    windowRenderer->loadTexture(&chessboard);

    // Set dice back
    backDice.setObject({ 0, 0, 0 , 0 }, { 0, 0, 160, 132 }, "Image/dice/dice_back.png");
    windowRenderer->loadTexture(&backDice);

    // Set Dice
    dice.setObject({ 0, 0, 0 , 0 }, { 0, 150, 150, 150 }, "Image/dice/dice.png");
    windowRenderer->loadTexture(&dice);

    // Set button
    playButton.setObject({ int(SCREEN_WIDTH /  2.7), int(SCREEN_HEIGHT /  2.5), 1326 / 5, 515 / 5 }, { 0, 0, 1326, 515 }, "Image/play_button.png");
    exitButton.setObject({ int(SCREEN_WIDTH / 2.55), int(SCREEN_HEIGHT / 1.28), 1326 / 6, 515 / 6 }, { 0, 0, 1326, 515 }, "Image/exit_button.png");
    backButton.setObject({ int(SCREEN_WIDTH /  1.1), int(SCREEN_HEIGHT / 1.18),  448 / 6, 497 / 6 }, { 0, 0,  448, 497 }, "Image/back_button.png");
    continueButton.setObject({ int(SCREEN_WIDTH / 2.87), int(SCREEN_HEIGHT / 1.7), 1560 / 5, 513 / 5 }, { 0, 0, 1560, 513 }, "Image/continue_button.png");
    _2playersButton.setObject({ int(SCREEN_WIDTH / 2.9), int(SCREEN_HEIGHT /    4), 1560 / 5, 513 / 5 }, { 0, 0, 1560, 513 }, "Image/2_players_button.png");
    _3playersButton.setObject({ int(SCREEN_WIDTH / 2.9), int(SCREEN_HEIGHT / 2.17), 1560 / 5, 513 / 5 }, { 0, 0, 1560, 513 }, "Image/3_players_button.png");
    _4playersButton.setObject({ int(SCREEN_WIDTH / 2.9), int(SCREEN_HEIGHT /  1.5), 1560 / 5, 513 / 5 }, { 0, 0, 1560, 513 }, "Image/4_players_button.png");

    windowRenderer->loadTexture(&playButton);
    windowRenderer->loadTexture(&exitButton);
    windowRenderer->loadTexture(&backButton);
    windowRenderer->loadTexture(&continueButton);
    windowRenderer->loadTexture(&_2playersButton);
    windowRenderer->loadTexture(&_3playersButton);
    windowRenderer->loadTexture(&_4playersButton);

    setMenuComponents();
}

void ParcheesiGame::setAlertComponents() {
    menuBoard.getBoard_It(RETURN_HOME)->setObject({ 417, 204, 277, 215 }, { 0, 0, 387, 300 }, "Image/menu/really_return_home_board.png");
    menuBoard.getBoard_It(RETURN_HOME)->getButtonYes_It()->setObject({ 458, 340, 82, 41 }, { 0, 0, 250, 127 }, "Image/menu/yes_button.png");
    menuBoard.getBoard_It(RETURN_HOME)->getButtonNo_It()->setObject({ 575, 340, 82, 41 }, { 0, 0, 250, 127 }, "Image/menu/no_button.png");

    windowRenderer->loadTexture(menuBoard.getBoard_It(RETURN_HOME));
    windowRenderer->loadTexture(menuBoard.getBoard_It(RETURN_HOME)->getButtonYes_It());
    windowRenderer->loadTexture(menuBoard.getBoard_It(RETURN_HOME)->getButtonNo_It());

    menuBoard.getBoard_It(RESTART_GAME)->setObject({ 417, 204, 277, 215 }, { 0, 0, 387, 300 }, "Image/menu/really_restart_game_board.png");
    menuBoard.getBoard_It(RESTART_GAME)->getButtonYes_It()->setObject({ 458, 340, 82, 41 }, { 0, 0, 250, 127 }, "Image/menu/yes_button.png");
    menuBoard.getBoard_It(RESTART_GAME)->getButtonNo_It()->setObject({ 575, 340, 82, 41 }, { 0, 0, 250, 127 }, "Image/menu/no_button.png");

    windowRenderer->loadTexture(menuBoard.getBoard_It(RESTART_GAME));
    windowRenderer->loadTexture(menuBoard.getBoard_It(RESTART_GAME)->getButtonYes_It());
    windowRenderer->loadTexture(menuBoard.getBoard_It(RESTART_GAME)->getButtonNo_It());

    //menuBoard.getBoard_It(SAVE_GAME)->setObject({ 417, 204, 277, 215 }, { 0, 0, 387, 275 }, "Image/menu/save_game_board.png");
    //menuBoard.getBoard_It(SAVE_GAME)->getButtonYes_It()->setObject({ 458, 340, 82, 41 }, { 0, 0, 250, 127 }, "Image/menu/save_game_board.png");

    //windowRenderer->loadTexture(menuBoard.getBoard_It(SAVE_GAME));
    //windowRenderer->loadTexture(menuBoard.getBoard_It(SAVE_GAME)->getButtonYes_It());

}

void ParcheesiGame::setMenuComponents() {
    // Set menu board
    menuBoard.setObject({ 392, 76, 326, 514 }, { 0, 0, 326, 514 }, "Image/menu/menu_board.png");
    windowRenderer->loadTexture(&menuBoard);

    // Set background
    menuBoard.getBackground_It()->setObject({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, "Image/menu/shadow.png");
    windowRenderer->loadTexture(menuBoard.getBackground_It());

    setAlertComponents();

    // Set button
    openMenu.setObject({ 19, 180, 68, 68 }, { 0, 0, 68, 68 }, "Image/menu/menu_button.png");
    
    menuBoard.getButton_It(EXIT_MENU)->setObject({ 633, 76, 82, 82 }, { 0, 0, 82, 82 }, "Image/menu/exit_menu.png");
    menuBoard.getButton_It(HOME_BUTTON)->setObject({ 442, 164, 232, 82 }, { 0, 0, 232, 82 }, "Image/menu/home_button.png");
    menuBoard.getButton_It(RESTART_BUTTON)->setObject({ 442, 255, 232, 82 }, { 0, 0, 232, 82 }, "Image/menu/restart_button.png");
    menuBoard.getButton_It(SAVE_BUTTON)->setObject({ 442, 346, 232, 82 }, { 0, 0, 232, 82 }, "Image/menu/save_button.png");
    menuBoard.getButton_It(ABOUT_BUTTON)->setObject({ 453, 459, 76, 76 }, { 0, 0, 76, 76 }, "Image/menu/about_button.png");
    menuBoard.getButton_It(SOUND_BUTTON)->setObject({ 583, 459, 76, 76 }, { 0, 0, 76, 76 }, "Image/menu/sound_button.png");

    windowRenderer->loadTexture(&openMenu);
    windowRenderer->loadTexture(menuBoard.getButton_It(EXIT_MENU));
    windowRenderer->loadTexture(menuBoard.getButton_It(HOME_BUTTON));
    windowRenderer->loadTexture(menuBoard.getButton_It(RESTART_BUTTON));
    windowRenderer->loadTexture(menuBoard.getButton_It(SAVE_BUTTON));
    windowRenderer->loadTexture(menuBoard.getButton_It(ABOUT_BUTTON));
    windowRenderer->loadTexture(menuBoard.getButton_It(SOUND_BUTTON));
}

// Animations

void ParcheesiGame::animationMoveChess(Chess* chess) {
    int idPositionChess = chess->getIdPosition();
    int position_x = mapChessboard[idPositionChess].first;
    int position_y = mapChessboard[idPositionChess].second;

    int nextIdPositionChess = idMoveForward(idPositionChess);

    int nextPosition_x = mapChessboard[nextIdPositionChess].first;
    int nextPosition_y = mapChessboard[nextIdPositionChess].second;

    switch (chess->getStatus()) {
    case 0:
        windowRenderer->rendererChess(position_x, position_y, chess);
        break;

    case 1:
        windowRenderer->rendererChess(position_x, position_y, chess);
        break;

    case 2:
        windowRenderer->rendererChess((position_x + nextPosition_x) / 2, (position_y + nextPosition_y) / 2, chess);
        break;
    }

    int time = 40;
    if (chess->getFpsTime()->getTicks() > time) {
        if (chess->getStatus() == chess->getMaxStatus() - 1) {
            chess->setIdPosition(nextIdPositionChess);

            if (nextIdPositionChess == chess->getEndIdPosition()) {

                // Kick chess
                for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
                    if (idPlayer == playerTurn) continue;

                    for (int idChess = 0; idChess < 4; ++idChess) {
                        if (player[idPlayer].getChess_It(idChess)->getIdPosition() == nextIdPositionChess) {
                            player[idPlayer].getChess_It(idChess)->setIdPosition(player[idPlayer].getChess_It(idChess)->getStartId());
                            break;
                        }
                    }
                }

                chess->finishAnimations();
                return;
            }

        }
        chess->nextStatus();
        chess->getFpsTime()->start();
    }
    
}

void ParcheesiGame::animationRollDice() {
    windowRenderer->rendererDiceAnimations(dice, dice.getStatus());

    if (dice.getStatus() == dice.getMaxStatus() - 1) {
        dice.finishAnimations();
        return;
    }

    dice.nextStatus();
}

// Display

void ParcheesiGame::displayHome() {
    // Load background
    windowRenderer->rendererBackground(&background);

    // Load button 
    windowRenderer->rendererButton(&playButton);
    windowRenderer->rendererButton(&exitButton);
    windowRenderer->rendererButton(&continueButton);
}

void ParcheesiGame::displayPlayerNumberSelection() {
    // Load background
    windowRenderer->rendererBackground(&background);

    //// Load button 
    windowRenderer->rendererButton(&backButton);
    windowRenderer->rendererButton(&_2playersButton);
    windowRenderer->rendererButton(&_3playersButton);
    windowRenderer->rendererButton(&_4playersButton);
}

void ParcheesiGame::displayGame() {
    // Load background
    windowRenderer->rendererBackground(&background);

    // Set direction chess
    for (int idPlayer = 0; idPlayer < 4; ++idPlayer) {
        for (int idChess = 0; idChess < 4; ++idChess) {
            int idPositionChess = player[idPlayer].getChess_It(idChess)->getIdPosition();

            if (idPositionChess <= 15) {
                player[idPlayer].setDirectionChess(idChess, RIGHT);
                continue;
            }

            int nextIdPositionChess = idMoveForward(idPositionChess);

            if (mapChessboard[idPositionChess].first < mapChessboard[nextIdPositionChess].first) {
                player[idPlayer].setDirectionChess(idChess, RIGHT);
            }
            else player[idPlayer].setDirectionChess(idChess, LEFT);
        }
    }

    // Load avatar players
    for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer)
        windowRenderer->rendererAvatar(player[idPlayer]);

    // Load layers board
    for (int layerBoard = chessboard.getNumLayers() - 1; layerBoard >= 0; --layerBoard) {
        chessboard.setLayer(layerBoard);
        windowRenderer->rendererChessboard(chessboard);

        for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
            for (int idChess = 0; idChess < 4; ++idChess) {
                Chess* chess = player[idPlayer].getChess_It(idChess);
                int idPositionChess = chess->getIdPosition();

                // Animation move chess
                if (chess->getAnimations() == true) {
                    if (checkIdChessInLayer(idPositionChess, layerBoard)) animationMoveChess(chess);
                    continue;
                }

                if (checkIdChessInLayer(idPositionChess, layerBoard)) {

                    // Load arrow
                    if (player[idPlayer].getChess(idChess).getCanMoveChess()) {
                        windowRenderer->rendererArrow(mapChessboard[idPositionChess].first + 11, mapChessboard[idPositionChess].second + 5, &arrow);
                    }

                    // Load chess
                    windowRenderer->rendererChess(mapChessboard[idPositionChess].first, mapChessboard[idPositionChess].second, player[idPlayer].getChess_It(idChess));
                }
            }
        }
    }
    
    windowRenderer->rendererButton(&openMenu);

    // Back dice
    if (playerTurn == 0) backDice.setRect({ 150, 540, 160 , 132 }); else
    if (playerTurn == 1) backDice.setRect({ 792, 540, 160 , 132 }); else
    if (playerTurn == 2) backDice.setRect({ 792,   5, 160 , 132 }); else
    if (playerTurn == 3) backDice.setRect({ 150,   5, 160 , 132 });

    windowRenderer->rendererBackDice(backDice, playerTurn);

    // Dice
    if (playerTurn == 0) dice.setRect({ 189, 550, 110 , 110 }); else
    if (playerTurn == 1) dice.setRect({ 800, 550, 110 , 110 }); else
    if (playerTurn == 2) dice.setRect({ 800,  13, 110 , 110 }); else
    if (playerTurn == 3) dice.setRect({ 189,  13, 110 , 110 });

    if (dice.getAnimations()) animationRollDice();
    else windowRenderer->rendererDice(dice);

    if (statusPlayer == ROLL_DICE) {
        switch (playerTurn) {
            case 0:
                clickToRoll.setClip({ 98, 98, 98, 98 });
                windowRenderer->rendererArrow(336, 585, &clickToRoll);
                break;
            case 1:
                clickToRoll.setClip({ 0, 98, 98, 98 });
                windowRenderer->rendererArrow(723, 585, &clickToRoll);
                break;
            case 2:
                clickToRoll.setClip({ 0, 98, 98, 98 });
                windowRenderer->rendererArrow(723, 45, &clickToRoll);
                break;
            case 3:
                clickToRoll.setClip({ 98, 98, 98, 98 });
                windowRenderer->rendererArrow(336, 45, &clickToRoll);
                break;
        }
    }
}

void ParcheesiGame::displayMenu() {
    if (menuBoard.getShadow_on() == false) {
        menuBoard.setShadow_on(true);
        windowRenderer->rendererBackground(menuBoard.getBackground_It());
    }
    windowRenderer->rendererMenuBoard(&menuBoard);
    windowRenderer->rendererButton(menuBoard.getButton_It(EXIT_MENU));
    windowRenderer->rendererButton(menuBoard.getButton_It(HOME_BUTTON));
    windowRenderer->rendererButton(menuBoard.getButton_It(RESTART_BUTTON));
    windowRenderer->rendererButton(menuBoard.getButton_It(SAVE_BUTTON));
    windowRenderer->rendererButton(menuBoard.getButton_It(ABOUT_BUTTON));
    windowRenderer->rendererButton(menuBoard.getButton_It(SOUND_BUTTON));
}

void ParcheesiGame::displayAlertBoard(BOARD nameAlert) {
    windowRenderer->rendererAlert(menuBoard.getBoard_It(nameAlert));
    windowRenderer->rendererButton(menuBoard.getBoard_It(nameAlert)->getButtonYes_It());
    windowRenderer->rendererButton(menuBoard.getBoard_It(nameAlert)->getButtonNo_It());
}

void ParcheesiGame::displaySaveGame() {

}

void ParcheesiGame::displayAbout() {

}

// Events

void ParcheesiGame::eventsHome() {
    playButton.setStatus(mouse->CheckMouseInButton(playButton));
    exitButton.setStatus(mouse->CheckMouseInButton(exitButton));
    continueButton.setStatus(mouse->CheckMouseInButton(continueButton));

    if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (playButton.getStatus() == ON_CLICK) display = PLAYER_NUMBER_SELECTION;
        if (exitButton.getStatus() == ON_CLICK) { SDL_Quit(); exit(1); }
        if (continueButton.getStatus() == ON_CLICK) {  }
    }
}

void ParcheesiGame::eventsPlayerNumberSelection() {
    backButton.setStatus(mouse->CheckMouseInButton(backButton));
    _2playersButton.setStatus(mouse->CheckMouseInButton(_2playersButton));
    _3playersButton.setStatus(mouse->CheckMouseInButton(_3playersButton));
    _4playersButton.setStatus(mouse->CheckMouseInButton(_4playersButton));

    if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (backButton.getStatus() == ON_CLICK) { display = HOME; return; }
        if (_2playersButton.getStatus() == ON_CLICK) { display = GAME; numberPlayers = 2; return; }
        if (_3playersButton.getStatus() == ON_CLICK) { display = GAME; numberPlayers = 3; return; }
        if (_4playersButton.getStatus() == ON_CLICK) { display = GAME; numberPlayers = 4; return; }
    }
}

void ParcheesiGame::eventsGame() {
    // Menu
    openMenu.setStatus(mouse->CheckMouseInButton(openMenu));

    if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (openMenu.getStatus() == ON_CLICK) {
            menuBoard.setShadow_on(false);
            openMenu.setStatus(NORMAL);
            display = MENU;
            return;
        }
    }

    // Animations
    for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
        for (int idChess = 0; idChess < 4; ++idChess) {
            if (player[idPlayer].getChess(idChess).getAnimations() == true) return;
        }
    }

    if (dice.getAnimations()) return;

    // Player
    switch (statusPlayer) {
        case ROLL_DICE:
            if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
                if (mouse->CheckMouseInDice(dice) == ON_CLICK) {
                    //int x;
                    //cin >> x;
                    //dice.setNumDice(x);
                    dice.rollDice();
                    dice.setAnimations(true);
                    statusPlayer = CHOOSECHESS;
                }
            }
            break;

        case CHOOSECHESS:
            if (!canMove()) {
                //
                cout << "CAN NOT MOVE!!!\n";
                //
                statusPlayer = (dice.getNumDice() == 6) ? ROLL_DICE : ENDTURN;
                break;
            }

            // Chess can move
            for (int idChess = 0; idChess < 4; ++idChess) {
                if (player[playerTurn].getCanMoveChess(idChess)) continue;

                int idPositionChess = player[playerTurn].getChess_It(idChess)->getIdPosition();
                if (chessNextStep(idPositionChess) != -1) player[playerTurn].setCanMoveChess(idChess, true);
            }

            if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
                for (int idChess = 0; idChess < 4; ++idChess) {
                    if (!player[playerTurn].getCanMoveChess(idChess)) continue;

                    int idPositionChess = player[playerTurn].getChess_It(idChess)->getIdPosition();
                    if (mouse->CheckMouseInChess(mapChessboard[idPositionChess].first, mapChessboard[idPositionChess].second, player[playerTurn].getChess_It(idChess))) {

                        // move chess               
                        int nextStep = chessNextStep(idPositionChess);
                        if (nextStep != -1) {

                            if (idPositionChess > 15) {
                                player[playerTurn].getChess_It(idChess)->setChessAnimations(true, nextStep);
                            }
                            else player[playerTurn].getChess_It(idChess)->setIdPosition(nextStep);


                            for (int chess1 = 0; chess1 < 4; ++chess1) {
                                player[playerTurn].setCanMoveChess(chess1, false);
                            }

                            statusPlayer = (dice.getNumDice() == 6) ? ROLL_DICE : ENDTURN;
                            break;

                        }

                    }
                }
            }

            break;

        case ENDTURN:
            playerTurn = (playerTurn + 1) % numberPlayers;
            dice.setNumDice(0);
            statusPlayer = ROLL_DICE;
            break;
    }
}

void ParcheesiGame::eventsMenu() {
    menuBoard.getButton_It(EXIT_MENU)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(EXIT_MENU)));
    menuBoard.getButton_It(HOME_BUTTON)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(HOME_BUTTON)));
    menuBoard.getButton_It(RESTART_BUTTON)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(RESTART_BUTTON)));
    menuBoard.getButton_It(SAVE_BUTTON)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(SAVE_BUTTON)));
    menuBoard.getButton_It(ABOUT_BUTTON)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(ABOUT_BUTTON)));
    menuBoard.getButton_It(SOUND_BUTTON)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(SOUND_BUTTON)));

    if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (menuBoard.getButton_It(EXIT_MENU)->getStatus() == ON_CLICK)      { display = GAME; return; }
        if (menuBoard.getButton_It(HOME_BUTTON)->getStatus() == ON_CLICK)    { display = ALERT_RETURN_HOME; return; }
        if (menuBoard.getButton_It(RESTART_BUTTON)->getStatus() == ON_CLICK) { display = ALERT_RESTART_GAME; return; }
        if (menuBoard.getButton_It(SAVE_BUTTON)->getStatus() == ON_CLICK)    { saveGame();  return; }
        if (menuBoard.getButton_It(ABOUT_BUTTON)->getStatus() == ON_CLICK)   { return; }
        if (menuBoard.getButton_It(SOUND_BUTTON)->getStatus() == ON_CLICK)   { return; }
    }
}

void ParcheesiGame::eventsAlertBoard(BOARD nameAlert) {
    Board* returnHome = menuBoard.getBoard_It(nameAlert);
    returnHome->getButtonYes_It()->setStatus(mouse->CheckMouseInButton(returnHome->getButtonYes()));
    returnHome->getButtonNo_It()->setStatus(mouse->CheckMouseInButton(returnHome->getButtonNo()));

    if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (returnHome->getButtonYes_It()->getStatus() == ON_CLICK) { 
            if (nameAlert ==  RETURN_HOME) display = HOME;
            if (nameAlert == RESTART_GAME) display = GAME; 
            restartGame();
            return; 
        }
        if (returnHome->getButtonNo_It()->getStatus()  == ON_CLICK) { display = MENU; return; }
    }
}

void ParcheesiGame::eventsSaveGame() {

}

void ParcheesiGame::eventsAbout() {

}

// Start game

void ParcheesiGame::startGame() {
    windowRenderer = new WindowRenderer;
    windowRenderer->createWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    setGameComponents();

    FPS fpsTimer;

    display = HOME;

    bool quit = false;
    while (!quit) {
        fpsTimer.start();

        // Handle Events
        while (SDL_PollEvent(events)) {

            //User requests quit
            if (events->type == SDL_QUIT) {
                quit = true;
                break;
            }

            mouse->mouseHandleEvent();

            switch (display) {
                case HOME:
                    eventsHome();
                    break;
                case PLAYER_NUMBER_SELECTION:
                    eventsPlayerNumberSelection();
                    break;
                case GAME:
                    eventsGame();
                    break;
                case MENU:
                    eventsMenu();
                    break;
                case ALERT_RETURN_HOME:
                    eventsAlertBoard(RETURN_HOME);
                    break;
                case ALERT_RESTART_GAME:
                    eventsAlertBoard(RESTART_GAME);
                    break;
                case NOTI_SAVE_GAME:
                    eventsSaveGame();
                    break;
                case ABOUT:
                    eventsAbout();
                    break;
            }
        }

        // Update game status, draw the current frame
        switch (display) {
            case HOME:
                displayHome();
                break;
            case PLAYER_NUMBER_SELECTION:
                displayPlayerNumberSelection();
                break;
            case GAME:
                displayGame();
                break;
            case MENU:
                displayMenu();
                break;
            case ALERT_RETURN_HOME:
                displayAlertBoard(RETURN_HOME);
                break;
            case ALERT_RESTART_GAME:
                displayAlertBoard(RESTART_GAME);
                break;
            case NOTI_SAVE_GAME:
                displaySaveGame();
            case ABOUT:
                displayAbout();
                break;
        }
        
        // Cursor
        mouse->setRect({ mouse->getPosition_x(), mouse->getPosition_y(), 40, 40 });
        windowRenderer->rendererMouse(mouse);
        SDL_ShowCursor(false);

        windowRenderer->displayImage();

        // FPS game components
        arrow.setFps(200);
        clickToRoll.setFps(300);
        background.setFps(400);

        // FPS
        int real_time = fpsTimer.getTicks();
        int time_one_frame = 1000 / FRAME_PER_SECOND; // ms
        if (real_time < time_one_frame) {
            int delay_time = time_one_frame - real_time;
            if (delay_time >= 0) SDL_Delay(delay_time);
        }
    }

    windowRenderer->deleteWindow();
    SDL_Quit();
}