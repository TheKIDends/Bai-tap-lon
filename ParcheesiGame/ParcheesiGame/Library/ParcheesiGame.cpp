#include "ParcheesiGame.h"

bool ParcheesiGame::checkIdInStartPosition(int idPosition) {
    for (int idPlayer = 0; idPlayer < MAX_NUMBER_PLAYERS; ++idPlayer)
        if (idPosition == idStartPosition[idPlayer]) return true;
    return false;
}

int ParcheesiGame::idMoveForward(int idPosition, int turn) {
    // chess in stable door
    if (idPosition == idStartPosition[turn] - 1) return idStartStable[turn];

    int nextIdPosition = idPosition + 1;

    // chess in stable
    if (idPosition > MAX_ID_RACETRACK) {
        if (nextIdPosition > idStartStable[turn] + NUMBER_ID_STABLE - 1) return -1;
        return nextIdPosition;
    }

    // chess in racetrack
    if (nextIdPosition > MAX_ID_RACETRACK) nextIdPosition -= NUMBER_ID_RACETRACK;
    if (checkIdInStartPosition(nextIdPosition)) { ++nextIdPosition; }
    if (nextIdPosition > MAX_ID_RACETRACK) nextIdPosition -= NUMBER_ID_RACETRACK;
    return nextIdPosition;
}

int ParcheesiGame::chessNextStep(Chess* chess) {
    int idPosition = chess->getIdPosition();

    // chess in start
    if (idPosition <= NUMBER_ID_START) {
        for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess) {
            int id = player[playerTurn].getChess_It(idChess)->getIdPosition();
            if (idStartPosition[playerTurn] == id) return -1;
        }
        if (dice.getNumDice() == 6) return idStartPosition[playerTurn];
        return -1;
    }

    int step = dice.getNumDice();

    // chess in stable
    if (idPosition > MAX_ID_RACETRACK) {
        if (step != (idPosition - idStartStable[playerTurn] + 1) + 1) return -1;
        int nextIdPosition = idMoveForward(idPosition, playerTurn);
        if (nextIdPosition == -1) return -1;

        for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess) {
            int id = player[playerTurn].getChess_It(idChess)->getIdPosition();
            if (nextIdPosition == id) return -1;
        }

        return nextIdPosition;
    }

    // chess in racetrack
    int nextIdPosition = idPosition;
    while (step--) {
        nextIdPosition = idMoveForward(nextIdPosition, playerTurn);
        if (nextIdPosition == -1) return -1;

        if (idPosition != idStartPosition[playerTurn] - 1 && nextIdPosition == idStartPosition[playerTurn] - 1 && step) return -1;

        for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
            if (!step && idPlayer != playerTurn) continue;

            for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess) {
                int id = player[idPlayer].getChess_It(idChess)->getIdPosition();
                if (nextIdPosition == id) return -1;
            }
        }
    }
    return nextIdPosition;
}

bool ParcheesiGame::canMove() {
    for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess) {
        if (chessNextStep(player[playerTurn].getChess_It(idChess)) != -1) return true;
    }
    return false;
}

bool ParcheesiGame::checkIdChessInLayer(int idPosition, int layer) {
    switch (layer) {
        case 0:
            if (17 <= idPosition && idPosition <= 29) return true;
            break;
        case 1:
            if (idPosition == 30 || idPosition == 16) return true;
            if (72 <= idPosition && idPosition <= 77) return true;
            if (78 <= idPosition && idPosition <= 83) return true;
            break;
        case 2:
            if (31 <= idPosition && idPosition <= 37) return true;
            if (65 <= idPosition && idPosition <= 71) return true;
            break;
        case 3:
            if (38 <= idPosition && idPosition <= 43) return true;
            if (59 <= idPosition && idPosition <= 64) return true;
            break;
        case 4:
            if (44 == idPosition || idPosition == 58) return true;
            if (84 <= idPosition && idPosition <= 89) return true;
            if (90 <= idPosition && idPosition <= 95) return true;
            break;
        case 5:
            if (45 <= idPosition && idPosition <= 57) return true;
            break;
        case 6:
            if ( 0 <= idPosition && idPosition <= 15) return true;
            break;
    }
    return false;
}

void ParcheesiGame::nextPlayer() {
    while (player[playerTurn].getWinner() == true) {
        playerTurn = (playerTurn + 1) % numberPlayers;
    }
}

void ParcheesiGame::setWinner() {
    for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
        if (player[idPlayer].getWinner() == true) continue;

        int numberWinChess = 0;
        for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess) {
            int idPosition = player[idPlayer].getChess_It(idChess)->getIdPosition();
            if (idStartStable[idPlayer] + 2 <= idPosition && idPosition <= idStartStable[idPlayer] + NUMBER_ID_STABLE - 1) ++numberWinChess;
        }

        if (numberWinChess == MAX_NUMBER_CHESS) {
            ordWinner += char (idPlayer + '0');
            player[idPlayer].setWinner(true);
            if (audioMixer->getMutedChunk() == false) Mix_PlayChannel(-1, player_win, 0);
        }
    }
}

void ParcheesiGame::restartGame() {
    playerTurn = 0;
    statusPlayer = STATUS_PLAYER::ROLL_DICE;
    ordWinner = ">";

    // Reset chess
    int idPosition = 0;
    for (int idPlayer = 0; idPlayer < MAX_NUMBER_PLAYERS; ++idPlayer) {
        player[idPlayer].setWinner(false);
        for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess) {
            player[idPlayer].setCanMoveChess(idChess, false);
            player[idPlayer].getChess_It(idChess)->setStartId(idPosition++);
        }
    }

    // Resrt animations
    for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
        for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess) {
            player[idPlayer].getChess_It(idChess)->finishAnimations();
        }
    }
    dice.setNumDice(0);
    dice.finishAnimations();
}

void ParcheesiGame::continueGame() {
    restartGame();

    string filepath = "Save/save.txt";
    ifstream ifs(filepath.c_str());

    ifs >> numberPlayers;
    ifs >> playerTurn;
    ifs >> ordWinner;

    for (int i = 0; i < ordWinner.size(); ++i) {
        int idPlayer = int (ordWinner[i] - '0');
        player[idPlayer].setWinner(true);
    }

    for (int idPlayer = 0; idPlayer < MAX_NUMBER_PLAYERS; ++idPlayer) {
        for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess) {
            int idPosition; ifs >> idPosition;
            player[idPlayer].getChess_It(idChess)->setIdPosition(idPosition);
        }
    }
    ifs.close();
}

void ParcheesiGame::saveGame() {
    string filepath = "Save/save.txt";
    ofstream ofs(filepath.c_str());

    ofs << numberPlayers << '\n';
    ofs << playerTurn << '\n';
    ofs << ordWinner << '\n';

    for (int idPlayer = 0; idPlayer < MAX_NUMBER_PLAYERS; ++idPlayer) {
        for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess) {
            ofs << player[idPlayer].getChess_It(idChess)->getIdPosition() << '\n';
        }
    }

    ofs.close();
}

// 
void ParcheesiGame::setGameComponents() {
    restartGame();

    // Set mouse
    mouse->setObject(BASE_RECT, MOUSE_CLIP, "Image/mouse.png");
    windowRenderer->loadTexture(mouse);

    buildMap();

    // Set leaderboard
    leaderboard.setObject(LEADERBOARD_RECT, LEADERBOARD_CLIP, "Image/leaderboard.png");
    windowRenderer->loadTexture(&leaderboard);

    // Set title
    title.setObject(TITLE_RECT, TITLE_CLIP, "Image/title.png");
    windowRenderer->loadTexture(&title);

    // Set background
    background.getFpsTime()->start();
    background.setObject(BACKGROUND_RECT, BACKGROUND_CLIP, "Image/background.png");
    windowRenderer->loadTexture(&background);

    // Set arrow
    arrow.getFpsTime()->start();
    arrow.setArrow(ARROW_DISTANCE, DIRECTION::DOWN, ARROW_RECT, ARROW_CLIP, "Image/arrow.png");
    windowRenderer->loadTexture(&arrow);

    arrowClickToRoll.getFpsTime()->start();
    arrowClickToRoll.setArrow(ARROW_CLICK_TO_ROLL_DISTANCE, DIRECTION::LEFT, ARROW_CLICK_TO_ROLL_RECT, ARROW_CLICK_TO_ROLL_CLIP, "Image/arrow.png");
    windowRenderer->loadTexture(&arrowClickToRoll);

    // Set avatar
    player[0].setAvatarPlayer(AVATAR_PLAYER_0_RECT, AVATAR_PLAYER_0_CLIP, "Image/green_avatar.png");
    player[1].setAvatarPlayer(AVATAR_PLAYER_1_RECT, AVATAR_PLAYER_1_CLIP, "Image/yellow_avatar.png");
    player[2].setAvatarPlayer(AVATAR_PLAYER_2_RECT, AVATAR_PLAYER_2_CLIP, "Image/red_avatar.png");
    player[3].setAvatarPlayer(AVATAR_PLAYER_3_RECT, AVATAR_PLAYER_3_CLIP, "Image/blue_avatar.png");
    for (int idPlayer = 0; idPlayer < MAX_NUMBER_PLAYERS; ++idPlayer) windowRenderer->loadTexture(&player[idPlayer]);

    // Set chess image
    int clipPosition_y = 0;
    for (int idPlayer = 0; idPlayer < MAX_NUMBER_PLAYERS; ++idPlayer) {
        SDL_Rect chessClip = CHESS_CLIP;
        chessClip.y = clipPosition_y;
        player[idPlayer].setAllChessPlayer(CHESS_RECT, chessClip, "Image/chess.png");
        for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess)
            windowRenderer->loadTexture(player[idPlayer].getChess_It(idChess));

        clipPosition_y += CHESS_CLIP.h;
    }

    // Start FPS Chess
    for (int idPlayer = 0; idPlayer < MAX_NUMBER_PLAYERS; ++idPlayer) {
        for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess) {
            player[idPlayer].getChess_It(idChess)->getFpsTime()->start();
        }
    }

    // Set chessboard
    chessboard.setObject(CHESSBOARD_RECT, CHESSBOARD_CLIP, "Image/chessboard.png");
    windowRenderer->loadTexture(&chessboard);

    // Set back dice
    backDice.setObject(BASE_RECT, BACK_DICE_CLIP, "Image/dice/dice_back.png");
    windowRenderer->loadTexture(&backDice);

    // Set noti loser
    notiLoser.setObject(NOTI_LOSER_RECT, NOTI_LOSER_CLIP, "Image/loser.png");
    windowRenderer->loadTexture(&notiLoser);

    // Set boom
    boom.setObject(BOOM_RECT, BOOM_CLIP, "Image/boom.png");
    windowRenderer->loadTexture(&boom);

    // Set can not move
    notiCanNotMove.setObject(NOTI_CAN_NOT_MOVE_RECT, NOTI_CAN_NOT_MOVE_CLIP, "Image/can_not_move.png");
    windowRenderer->loadTexture(&notiCanNotMove);

    // Set Dice
    dice.setObject(BASE_RECT, DICE_CLIP, "Image/dice/dice.png");
    windowRenderer->loadTexture(&dice);

    // Set button
    backHome.setObject(BACK_HOME_RECT, BACK_HOME_CLIP, "Image/menu/home_button.png");
    playButton.setObject(PLAY_BUTTON_RECT, PLAY_BUTTON_CLIP, "Image/play_button.png");
    exitButton.setObject(EXIT_BUTTON_RECT, EXIT_BUTTON_CLIP, "Image/exit_button.png");
    backButton.setObject(BACK_BUTTON_RECT, BACK_BUTTON_CLIP, "Image/back_button.png");
    continueButton.setObject(CONTINUE_BUTTON_RECT, CONTINUE_BUTTON_CLIP, "Image/continue_button.png");
    _2playersButton.setObject(_2PLAYERS_BUTTON_RECT, _2PLAYERS_BUTTON_CLIP, "Image/2_players_button.png");
    _3playersButton.setObject(_3PLAYERS_BUTTON_RECT, _3PLAYERS_BUTTON_CLIP, "Image/3_players_button.png");
    _4playersButton.setObject(_4PLAYERS_BUTTON_RECT, _4PLAYERS_BUTTON_CLIP, "Image/4_players_button.png");

    windowRenderer->loadTexture(&backHome);
    windowRenderer->loadTexture(&playButton);
    windowRenderer->loadTexture(&exitButton);
    windowRenderer->loadTexture(&backButton);
    windowRenderer->loadTexture(&continueButton);
    windowRenderer->loadTexture(&_2playersButton);
    windowRenderer->loadTexture(&_3playersButton);
    windowRenderer->loadTexture(&_4playersButton);

    setMenuComponents();
}

void ParcheesiGame::setBoardComponents() {
    menuBoard.getBoard_It(BOARD::RETURN_HOME)->setObject({ 417, 204, 277, 215 }, { 0, 0, 387, 300 }, "Image/menu/really_return_home_board.png");
    menuBoard.getBoard_It(BOARD::RETURN_HOME)->getButtonYes_It()->setObject({ 458, 340, 82, 41 }, { 0, 0, 250, 127 }, "Image/menu/yes_button.png");
    menuBoard.getBoard_It(BOARD::RETURN_HOME)->getButtonNo_It()->setObject({ 575, 340, 82, 41 }, { 0, 0, 250, 127 }, "Image/menu/no_button.png");

    windowRenderer->loadTexture(menuBoard.getBoard_It(BOARD::RETURN_HOME));
    windowRenderer->loadTexture(menuBoard.getBoard_It(BOARD::RETURN_HOME)->getButtonYes_It());
    windowRenderer->loadTexture(menuBoard.getBoard_It(BOARD::RETURN_HOME)->getButtonNo_It());

    menuBoard.getBoard_It(BOARD::RESTART_GAME)->setObject({ 417, 204, 277, 215 }, { 0, 0, 387, 300 }, "Image/menu/really_restart_game_board.png");
    menuBoard.getBoard_It(BOARD::RESTART_GAME)->getButtonYes_It()->setObject({ 458, 340, 82, 41 }, { 0, 0, 250, 127 }, "Image/menu/yes_button.png");
    menuBoard.getBoard_It(BOARD::RESTART_GAME)->getButtonNo_It()->setObject({ 575, 340, 82, 41 }, { 0, 0, 250, 127 }, "Image/menu/no_button.png");

    windowRenderer->loadTexture(menuBoard.getBoard_It(BOARD::RESTART_GAME));
    windowRenderer->loadTexture(menuBoard.getBoard_It(BOARD::RESTART_GAME)->getButtonYes_It());
    windowRenderer->loadTexture(menuBoard.getBoard_It(BOARD::RESTART_GAME)->getButtonNo_It());

    menuBoard.getBoard_It(BOARD::SAVE_GAME)->setObject({ 417, 220, 277, 197 }, { 0, 0, 387, 275 }, "Image/menu/save_game_board.png");
    menuBoard.getBoard_It(BOARD::SAVE_GAME)->getButtonOk_It()->setObject({ 518, 355, 82, 41 }, { 0, 0, 250, 127 }, "Image/menu/ok_button.png");

    windowRenderer->loadTexture(menuBoard.getBoard_It(BOARD::SAVE_GAME));
    windowRenderer->loadTexture(menuBoard.getBoard_It(BOARD::SAVE_GAME)->getButtonOk_It());

}

void ParcheesiGame::setMenuComponents() {
    // Set menu board
    menuBoard.setObject({ 392, 76, 326, 514 }, { 0, 0, 326, 514 }, "Image/menu/menu_board.png");
    windowRenderer->loadTexture(&menuBoard);

    // Set background
    menuBoard.getBackground_It()->setObject({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, "Image/menu/shadow.png");
    windowRenderer->loadTexture(menuBoard.getBackground_It());

    setBoardComponents();

    // Set button
    openMenu.setObject({ 19, 180, 68, 68 }, { 0, 0, 68, 68 }, "Image/menu/menu_button.png");

    menuBoard.getButton_It(BUTTON::EXIT_MENU)->setObject({ 633, 76, 82, 82 }, { 0, 0, 82, 82 }, "Image/menu/exit_menu.png");
    menuBoard.getButton_It(BUTTON::HOME_BUTTON)->setObject({ 442, 164, 232, 82 }, { 0, 0, 232, 82 }, "Image/menu/home_button.png");
    menuBoard.getButton_It(BUTTON::RESTART_BUTTON)->setObject({ 442, 255, 232, 82 }, { 0, 0, 232, 82 }, "Image/menu/restart_button.png");
    menuBoard.getButton_It(BUTTON::SAVE_BUTTON)->setObject({ 442, 346, 232, 82 }, { 0, 0, 232, 82 }, "Image/menu/save_button.png");
    menuBoard.getButton_It(BUTTON::ABOUT_BUTTON)->setObject({ 427, 458, 76, 76 }, { 0, 0, 76, 76 }, "Image/menu/about_button.png");
    menuBoard.getButton_It(BUTTON::MUSIC_BUTTON)->setObject({ 463, 459, 76, 76 }, { 0, 0, 76, 76 }, "Image/menu/music_button.png");
    menuBoard.getButton_It(BUTTON::CHUNK_BUTTON)->setObject({ 573, 459, 76, 76 }, { 0, 0, 76, 76 }, "Image/menu/sound_button.png");
    //menuBoard.getButton_It(BUTTON::MUSIC_BUTTON)->setObject({ 517, 458, 76, 76 }, { 0, 0, 76, 76 }, "Image/menu/music_button.png");
    //menuBoard.getButton_It(BUTTON::CHUNK_BUTTON)->setObject({ 609, 458, 76, 76 }, { 0, 0, 76, 76 }, "Image/menu/sound_button.png");

    windowRenderer->loadTexture(&openMenu);
    windowRenderer->loadTexture(menuBoard.getButton_It(BUTTON::EXIT_MENU));
    windowRenderer->loadTexture(menuBoard.getButton_It(BUTTON::HOME_BUTTON));
    windowRenderer->loadTexture(menuBoard.getButton_It(BUTTON::RESTART_BUTTON));
    windowRenderer->loadTexture(menuBoard.getButton_It(BUTTON::SAVE_BUTTON));
    windowRenderer->loadTexture(menuBoard.getButton_It(BUTTON::ABOUT_BUTTON));
    windowRenderer->loadTexture(menuBoard.getButton_It(BUTTON::MUSIC_BUTTON));
    windowRenderer->loadTexture(menuBoard.getButton_It(BUTTON::CHUNK_BUTTON));
}

void ParcheesiGame::setAudioMixer() {
    gMusic      = Mix_LoadMUS("Audio/music.mp3");
    jump        = Mix_LoadWAV("Audio/jump.mp3");
    click       = Mix_LoadWAV("Audio/click.wav");
    kick        = Mix_LoadWAV("Audio/kick.mp3");
    rollDice    = Mix_LoadWAV("Audio/roll_dice.mp3");
    ono         = Mix_LoadWAV("Audio/ono.mp3");
    loser       = Mix_LoadWAV("Audio/lose.mp3");
    win         = Mix_LoadWAV("Audio/win.wav");
    player_win  = Mix_LoadWAV("Audio/player_win.wav");

    if (gMusic      == NULL) printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
    if (jump        == NULL) printf("Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    if (click       == NULL) printf("Failed to load click sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    if (kick        == NULL) printf("Failed to load kick sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    if (rollDice    == NULL) printf("Failed to load rollDice sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    if (ono         == NULL) printf("Failed to load ono sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    if (loser       == NULL) printf("Failed to load loser sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    if (win         == NULL) printf("Failed to load win sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    if (player_win  == NULL) printf("Failed to load player_win sound effect! SDL_mixer Error: %s\n", Mix_GetError());
}

// Animations

void ParcheesiGame::animationMoveChess(Chess* chess) {
    int idPositionChess = chess->getIdPosition();
    int position_x = mapChessboard[idPositionChess].first;
    int position_y = mapChessboard[idPositionChess].second;

    int nextIdPositionChess = idMoveForward(idPositionChess, playerTurn);

    int nextPosition_x = mapChessboard[nextIdPositionChess].first;
    int nextPosition_y = mapChessboard[nextIdPositionChess].second;

    if (chess->getFpsTime()->getTicks() > ANIMATION_MOVE_CHESS_TIME_FPS) {
        if (chess->getStatus() == chess->getMaxStatus() - 1) {
            chess->setIdPosition(nextIdPositionChess);
            if (audioMixer->getMutedChunk() == false) Mix_PlayChannel(-1, jump, 0);

            if (nextIdPositionChess == chess->getEndIdPosition()) {

                // Kick chess
                for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
                    if (idPlayer == playerTurn) continue;

                    for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess) {
                        if (player[idPlayer].getChess_It(idChess)->getIdPosition() == nextIdPositionChess) {
                            player[idPlayer].getChess_It(idChess)->setIdPosition(player[idPlayer].getChess_It(idChess)->getStartId());

                            if (audioMixer->getMutedChunk() == false) Mix_PlayChannel(-1, kick, 0);

                            /*boom.setRect({ 200 - 10, 200 - 10, boom.getRect().w, boom.getRect().h });
                            windowRenderer->rendererImage(&boom);*/

                            /*boom.setRect({ position_x - 10, position_y - 10, boom.getRect().w, boom.getRect().h });
                            windowRenderer->rendererImage(&boom);*/

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
    if (dice.getStatus() == dice.getMaxStatus() - 1) {
        dice.finishAnimations();
        return;
    }
    dice.nextStatus();
}

void ParcheesiGame::showNotiCanNotMove() {
    if (notiCanNotMove.getStatus() == notiCanNotMove.getMaxStatus() - 1) {
        notiCanNotMove.finishAnimations();
        return;
    }
    notiCanNotMove.nextStatus();
}

// Set

void ParcheesiGame::setWindowHome() {
    background.nextStatus_Fps(BACKGROUND_TIME_FPS);
}

void ParcheesiGame::setWindowPlayerNumberSelection() {
    background.nextStatus_Fps(BACKGROUND_TIME_FPS);
}

void ParcheesiGame::setWindowGame() {
    setWinner();
    nextPlayer();

    // Set direction chess
    for (int idPlayer = 0; idPlayer < MAX_NUMBER_PLAYERS; ++idPlayer) {
        for (int idChess = 0; idChess < MAX_NUMBER_CHESS; ++idChess) {
            int idPositionChess = player[idPlayer].getChess_It(idChess)->getIdPosition();

            if (idPositionChess <= NUMBER_ID_START) {
                player[idPlayer].setDirectionChess(idChess, DIRECTION::RIGHT);
                continue;
            }

            if (idPositionChess == idStartStable[idPlayer] + NUMBER_ID_STABLE - 1) {
                if (idPlayer == 0 || idPlayer == 3) player[idPlayer].setDirectionChess(idChess, DIRECTION::RIGHT);
                if (idPlayer == 1 || idPlayer == 2) player[idPlayer].setDirectionChess(idChess, DIRECTION::LEFT);
                continue;
            }

            int nextIdPositionChess = idMoveForward(idPositionChess, idPlayer);

            if (mapChessboard[idPositionChess].first < mapChessboard[nextIdPositionChess].first) {
                player[idPlayer].setDirectionChess(idChess, DIRECTION::RIGHT);
            }
            else player[idPlayer].setDirectionChess(idChess, DIRECTION::LEFT);
        }
    }


    // Back dice
    switch (playerTurn) {
        case 0: backDice.setRect({ 150, 540, 160 , 132 }); break;
        case 1: backDice.setRect({ 792, 540, 160 , 132 }); break;
        case 2: backDice.setRect({ 792,   5, 160 , 132 }); break;
        case 3: backDice.setRect({ 150,   5, 160 , 132 }); break;
    }

    // Dice
    switch (playerTurn) {
        case 0: dice.setRect({ 189, 550, 110 , 110 }); break;
        case 1: dice.setRect({ 800, 550, 110 , 110 }); break;
        case 2: dice.setRect({ 800,  13, 110 , 110 }); break;
        case 3: dice.setRect({ 189,  13, 110 , 110 }); break;
    }

    // Arrow click to roll
    if (animations == false && statusPlayer == STATUS_PLAYER::ROLL_DICE) {
        switch (playerTurn) {
            case 0: arrowClickToRoll.setClip({ 98, 98, 98, 98 }); break;
            case 1: arrowClickToRoll.setClip({  0, 98, 98, 98 }); break;
            case 2: arrowClickToRoll.setClip({  0, 98, 98, 98 }); break;
            case 3: arrowClickToRoll.setClip({ 98, 98, 98, 98 }); break;
        }
    }

    // All animations
    animations = false;
    for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
        for (int idChess = 0; idChess < 4; ++idChess) {
            Chess* chess = player[idPlayer].getChess_It(idChess);
            if (chess->getAnimations() == true) animations = true;
        }
    }
    if (dice.getAnimations() == true) animations = true;
    if (notiCanNotMove.getAnimations() == true) animations = true;

    // Animation move chess
    for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
        for (int idChess = 0; idChess < 4; ++idChess) {
            Chess* chess = player[idPlayer].getChess_It(idChess);
            if (chess->getAnimations() == true) animationMoveChess(chess);
        }
    }

    // Animations roll dice
    if (dice.getAnimations() == true) animationRollDice();

    // Show noti can not move
    if (notiCanNotMove.getAnimations() == true) showNotiCanNotMove();

    // Chess can move
    if (statusPlayer == STATUS_PLAYER::CHOOSECHESS && animations == false) {
        for (int idChess = 0; idChess < 4; ++idChess) {
            if (player[playerTurn].getCanMoveChess(idChess)) continue;
            if (chessNextStep(player[playerTurn].getChess_It(idChess)) != -1) player[playerTurn].setCanMoveChess(idChess, true);
        }
    }

    // FPS game components
    arrow.nextStatus_Fps(200);
    arrowClickToRoll.nextStatus_Fps(300);
    background.nextStatus_Fps(400);
}

void ParcheesiGame::setWindowMenu() {
    SDL_Rect clipMusicBtn = menuBoard.getButton_It(BUTTON::MUSIC_BUTTON)->getClip();
    SDL_Rect clipSoundBtn = menuBoard.getButton_It(BUTTON::CHUNK_BUTTON)->getClip();

    if (audioMixer->getMutedMusic() == true) {
        menuBoard.getButton_It(BUTTON::MUSIC_BUTTON)->setClip({ 0, clipMusicBtn.h, clipMusicBtn.w, clipMusicBtn.h });
    }
    else menuBoard.getButton_It(BUTTON::MUSIC_BUTTON)->setClip({ 0, 0, clipMusicBtn.w, clipMusicBtn.h });

    if (audioMixer->getMutedChunk() == true) {
        menuBoard.getButton_It(BUTTON::CHUNK_BUTTON)->setClip({ 0, clipSoundBtn.h, clipSoundBtn.w, clipSoundBtn.h });
    }
    else menuBoard.getButton_It(BUTTON::CHUNK_BUTTON)->setClip({ 0, 0, clipSoundBtn.w, clipSoundBtn.h });

}

// Display

void ParcheesiGame::displayHome() {
    // Load background
    windowRenderer->rendererBackground(&background);
    windowRenderer->rendererImage(&title);

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

                if (checkIdChessInLayer(idPositionChess, layerBoard)) {
                    int position_x = mapChessboard[idPositionChess].first;
                    int position_y = mapChessboard[idPositionChess].second;

                    int nextIdPositionChess = idMoveForward(idPositionChess, idPlayer);

                    int nextPosition_x = mapChessboard[nextIdPositionChess].first;
                    int nextPosition_y = mapChessboard[nextIdPositionChess].second;

                    // Load arrow
                    if (chess->getCanMoveChess()) {
                        windowRenderer->rendererArrow(position_x + 11, position_y + 5, &arrow);
                    }

                    // Load chess
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

                }
            }
        }
    }

    // Load button open menu
    windowRenderer->rendererButton(&openMenu);

    //Load back dice
    windowRenderer->rendererBackDice(backDice, playerTurn);

    // Load dice
    if (dice.getAnimations() == true) windowRenderer->rendererDiceAnimations(dice);
    else windowRenderer->rendererDice(dice);

    // Load arrow click to roll
    if (statusPlayer == STATUS_PLAYER::ROLL_DICE) {
        switch (playerTurn) {
            case 0: windowRenderer->rendererArrow(336, 585, &arrowClickToRoll); break;
            case 1: windowRenderer->rendererArrow(723, 585, &arrowClickToRoll); break;
            case 2: windowRenderer->rendererArrow(723,  45, &arrowClickToRoll); break;
            case 3: windowRenderer->rendererArrow(336,  45, &arrowClickToRoll); break;
        }
    }

    if (notiCanNotMove.getAnimations() == true) windowRenderer->rendererImage(&notiCanNotMove);

    //if (statusPlayer == STATUS_PLAYER::ENDTURN) windowRenderer->rendererImage(&blueTurn);
    //for (int i = 72; i <= 100; ++i) {
    //    Chess* chess = player[0].getChess_It(0);
    //    int position_x = mapChessboard[i].first;
    //    int position_y = mapChessboard[i].second;
    //    windowRenderer->rendererChess(position_x, position_y, chess);
    //}
}

void ParcheesiGame::displayMenu() {
    displayGame();
    windowRenderer->rendererBackground(menuBoard.getBackground_It());
    windowRenderer->rendererImage(&menuBoard);
    windowRenderer->rendererButton(menuBoard.getButton_It(BUTTON::EXIT_MENU));
    windowRenderer->rendererButton(menuBoard.getButton_It(BUTTON::HOME_BUTTON));
    windowRenderer->rendererButton(menuBoard.getButton_It(BUTTON::RESTART_BUTTON));
    windowRenderer->rendererButton(menuBoard.getButton_It(BUTTON::SAVE_BUTTON));
    //windowRenderer->rendererButton(menuBoard.getButton_It(BUTTON::ABOUT_BUTTON));
    windowRenderer->rendererButton(menuBoard.getButton_It(BUTTON::MUSIC_BUTTON));
    windowRenderer->rendererButton(menuBoard.getButton_It(BUTTON::CHUNK_BUTTON));
}

void ParcheesiGame::displayAlertBoard(BOARD nameAlert) {
    displayMenu();
    windowRenderer->rendererImage(menuBoard.getBoard_It(nameAlert));
    windowRenderer->rendererButton(menuBoard.getBoard_It(nameAlert)->getButtonYes_It());
    windowRenderer->rendererButton(menuBoard.getBoard_It(nameAlert)->getButtonNo_It());
}

void ParcheesiGame::displaySaveGame() {
    displayMenu();
    windowRenderer->rendererImage(menuBoard.getBoard_It(BOARD::SAVE_GAME));
    windowRenderer->rendererButton(menuBoard.getBoard_It(BOARD::SAVE_GAME)->getButtonOk_It());
}

void ParcheesiGame::displayAbout() {
}

void ParcheesiGame::displayRank() {
    background.nextStatus_Fps(400);
    windowRenderer->rendererBackground(&background);

    int visit[] = { 0, 0, 0, 0 };

    for (int i = 1; i < ordWinner.size(); ++i) {
        int idPlayer = int(ordWinner[i] - '0');
        visit[idPlayer] = 1;
        windowRenderer->rendererAvatar(idLeaderboard[i - 1].first, idLeaderboard[i - 1].second, player[idPlayer]);
    }
    windowRenderer->rendererImage(&leaderboard);

    for (int idPlayer = 0; idPlayer < numberPlayers; ++idPlayer) {
        if (!visit[idPlayer]) {
            windowRenderer->rendererNoti(&notiLoser, idPlayer);
            break;
        }
    }

    windowRenderer->rendererButton(&backHome);

}

// Events

void ParcheesiGame::eventsHome() {
    playButton.setStatus(mouse->CheckMouseInButton(playButton));
    exitButton.setStatus(mouse->CheckMouseInButton(exitButton));
    continueButton.setStatus(mouse->CheckMouseInButton(continueButton));

    // sound
    if (audioMixer->getMutedChunk() == false && events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (playButton.getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
        if (continueButton.getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
    }

    if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (playButton.getStatus() == CLICK::ON_CLICK) { display = DISPLAY::PLAYER_NUMBER_SELECTION; return; }
        if (exitButton.getStatus() == CLICK::ON_CLICK) { SDL_Quit(); windowRenderer->deleteWindow(); exit(1); }
        if (continueButton.getStatus() == CLICK::ON_CLICK) { continueGame(); display = DISPLAY::GAME; return; }
    }
}

void ParcheesiGame::eventsPlayerNumberSelection() {
    backButton.setStatus(mouse->CheckMouseInButton(backButton));
    _2playersButton.setStatus(mouse->CheckMouseInButton(_2playersButton));
    _3playersButton.setStatus(mouse->CheckMouseInButton(_3playersButton));
    _4playersButton.setStatus(mouse->CheckMouseInButton(_4playersButton));

    // sound
    if (audioMixer->getMutedChunk() == false && events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (backButton.getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
        if (_2playersButton.getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
        if (_3playersButton.getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
        if (_4playersButton.getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
    }

    if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (backButton.getStatus() == CLICK::ON_CLICK) { display = DISPLAY::HOME; return; }
        if (_2playersButton.getStatus() == CLICK::ON_CLICK) { display = DISPLAY::GAME; numberPlayers = 2; return; }
        if (_3playersButton.getStatus() == CLICK::ON_CLICK) { display = DISPLAY::GAME; numberPlayers = 3; return; }
        if (_4playersButton.getStatus() == CLICK::ON_CLICK) { display = DISPLAY::GAME; numberPlayers = 4; return; }
    }
}

void ParcheesiGame::eventsGame() {
    // Menu
    openMenu.setStatus(mouse->CheckMouseInButton(openMenu));

    if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (openMenu.getStatus() == CLICK::ON_CLICK) {
            openMenu.setStatus(CLICK::NORMAL);
            display = DISPLAY::MENU;
            if (audioMixer->getMutedChunk() == false) Mix_PlayChannel(-1, click, 0);
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
    if (notiCanNotMove.getAnimations()) return;

    // Player
    switch (statusPlayer) {
    case STATUS_PLAYER::ROLL_DICE:

        if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
            if (mouse->CheckMouseInDice(dice) == CLICK::ON_CLICK) {
                //int x;  cin >> x; dice.setNumDice(x);
                dice.rollDice();
                dice.setAnimations(true);
                if (audioMixer->getMutedChunk() == false) Mix_PlayChannel(-1, rollDice, 0);
                statusPlayer = STATUS_PLAYER::CHOOSECHESS;
            }
        }
        break;

    case STATUS_PLAYER::CHOOSECHESS:
        if (!canMove()) {
            notiCanNotMove.setAnimations(true);
            if (audioMixer->getMutedChunk() == false) Mix_PlayChannel(-1, ono, 0);
            statusPlayer = (dice.getNumDice() == 6) ? STATUS_PLAYER::ROLL_DICE : STATUS_PLAYER::ENDTURN;
            break;
        }

        if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
            for (int idChess = 0; idChess < 4; ++idChess) {
                if (!player[playerTurn].getCanMoveChess(idChess)) continue;
                Chess* chess = player[playerTurn].getChess_It(idChess);
                int idPositionChess = chess->getIdPosition();
                if (mouse->CheckMouseInChess(mapChessboard[idPositionChess].first, mapChessboard[idPositionChess].second, player[playerTurn].getChess_It(idChess))) {

                    // move chess               
                    int nextStep = chessNextStep(chess);
                    if (nextStep != -1) {

                        if (idPositionChess > 15) {
                            chess->setStepsTaken(chess->getStepsTaken() + dice.getNumDice());
                            player[playerTurn].getChess_It(idChess)->setChessAnimations(true, nextStep);
                        }
                        else {
                            chess->setStepsTaken(0);
                            player[playerTurn].getChess_It(idChess)->setIdPosition(nextStep);
                        }


                        for (int i = 0; i < 4; ++i) player[playerTurn].setCanMoveChess(i, false);

                        statusPlayer = (dice.getNumDice() == 6) ? STATUS_PLAYER::ROLL_DICE : STATUS_PLAYER::ENDTURN;
                        break;

                    }

                }
            }
        }

        break;

    case STATUS_PLAYER::ENDTURN:
        playerTurn = (playerTurn + 1) % numberPlayers;
        dice.setNumDice(0);
        statusPlayer = STATUS_PLAYER::ROLL_DICE;
        break;
    }
}

void ParcheesiGame::eventsMenu() {
    menuBoard.getButton_It(BUTTON::EXIT_MENU)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(BUTTON::EXIT_MENU)));
    menuBoard.getButton_It(BUTTON::HOME_BUTTON)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(BUTTON::HOME_BUTTON)));
    menuBoard.getButton_It(BUTTON::RESTART_BUTTON)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(BUTTON::RESTART_BUTTON)));
    menuBoard.getButton_It(BUTTON::SAVE_BUTTON)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(BUTTON::SAVE_BUTTON)));
    //menuBoard.getButton_It(BUTTON::ABOUT_BUTTON)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(BUTTON::ABOUT_BUTTON)));
    menuBoard.getButton_It(BUTTON::MUSIC_BUTTON)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(BUTTON::MUSIC_BUTTON)));
    menuBoard.getButton_It(BUTTON::CHUNK_BUTTON)->setStatus(mouse->CheckMouseInButton(menuBoard.getButton(BUTTON::CHUNK_BUTTON)));

    // Sound
    if (audioMixer->getMutedChunk() == false && events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (menuBoard.getButton_It(BUTTON::EXIT_MENU)->getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
        if (menuBoard.getButton_It(BUTTON::HOME_BUTTON)->getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
        if (menuBoard.getButton_It(BUTTON::RESTART_BUTTON)->getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
        if (menuBoard.getButton_It(BUTTON::SAVE_BUTTON)->getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
        //if (menuBoard.getButton_It(BUTTON::ABOUT_BUTTON)->getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
        if (menuBoard.getButton_It(BUTTON::MUSIC_BUTTON)->getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
        if (menuBoard.getButton_It(BUTTON::CHUNK_BUTTON)->getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
    }

    if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (menuBoard.getButton_It(BUTTON::EXIT_MENU)->getStatus() == CLICK::ON_CLICK) { display = DISPLAY::GAME; return; }
        if (menuBoard.getButton_It(BUTTON::HOME_BUTTON)->getStatus() == CLICK::ON_CLICK) { display = DISPLAY::ALERT_RETURN_HOME; return; }
        if (menuBoard.getButton_It(BUTTON::RESTART_BUTTON)->getStatus() == CLICK::ON_CLICK) { display = DISPLAY::ALERT_RESTART_GAME; return; }
        if (menuBoard.getButton_It(BUTTON::SAVE_BUTTON)->getStatus() == CLICK::ON_CLICK) { saveGame(); display = DISPLAY::NOTI_SAVE_GAME;  return; }
        //if (menuBoard.getButton_It(BUTTON::ABOUT_BUTTON)->getStatus() == CLICK::ON_CLICK) { return; }
        if (menuBoard.getButton_It(BUTTON::MUSIC_BUTTON)->getStatus() == CLICK::ON_CLICK) { audioMixer->changeMutedMusic(); return; }
        if (menuBoard.getButton_It(BUTTON::CHUNK_BUTTON)->getStatus() == CLICK::ON_CLICK) { audioMixer->changeMutedChunk(); return; }
    }
}

void ParcheesiGame::eventsAlertBoard(BOARD nameAlert) {
    Board* board = menuBoard.getBoard_It(nameAlert);

    board->getButtonYes_It()->setStatus(mouse->CheckMouseInButton(board->getButtonYes()));
    board->getButtonNo_It()->setStatus(mouse->CheckMouseInButton(board->getButtonNo()));

    if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (board->getButtonYes_It()->getStatus() == CLICK::ON_CLICK) {
            if (audioMixer->getMutedChunk() == false) Mix_PlayChannel(-1, click, 0);
            if (nameAlert == BOARD::RETURN_HOME) display = DISPLAY::HOME;
            if (nameAlert == BOARD::RESTART_GAME) display = DISPLAY::GAME;
            restartGame();
            return;
        }
        if (board->getButtonNo_It()->getStatus() == CLICK::ON_CLICK) {
            if (audioMixer->getMutedChunk() == false) Mix_PlayChannel(-1, click, 0);
            display = DISPLAY::MENU;
            return;

        }
    }
}

void ParcheesiGame::eventsSaveGame() {
    Board* board = menuBoard.getBoard_It(BOARD::SAVE_GAME);
    board->getButtonOk_It()->setStatus(mouse->CheckMouseInButton(board->getButtonOk()));

    if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (board->getButtonOk_It()->getStatus() == CLICK::ON_CLICK) {
            if (audioMixer->getMutedChunk() == false) Mix_PlayChannel(-1, click, 0);
            display = DISPLAY::MENU;
            return;
        }
    }
}

void ParcheesiGame::eventsAbout() {
}

void ParcheesiGame::eventsRank() {
    backHome.setStatus(mouse->CheckMouseInButton(backHome));

    // sound
    if (audioMixer->getMutedChunk() == false && events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (backHome.getStatus() == CLICK::ON_CLICK) Mix_PlayChannel(-1, click, 0);
    }

    if (events->type == SDL_MOUSEBUTTONDOWN && events->button.button == SDL_BUTTON_LEFT) {
        if (backHome.getStatus() == CLICK::ON_CLICK) { display = DISPLAY::HOME; restartGame(); return; }
    }
}

void ParcheesiGame::checkEndGame() {
    if (ordWinner.size() < numberPlayers) return;
    display = DISPLAY::RANKING;

    SDL_Delay(1000);
    if (audioMixer->getMutedChunk() == false) Mix_PlayChannel(-1, win, 0);
}

// Start game

void ParcheesiGame::startGame() {
    audioMixer->createAudio();
    windowRenderer->createWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, "Image/window_icon.png");

    setAudioMixer();
    setGameComponents();

    FPS fpsTimer;

    display = DISPLAY::HOME;

    Mix_PlayMusic(gMusic, -1);

    bool quit = false;
    while (!quit) {
        fpsTimer.start();

        // Music
        if (Mix_PlayingMusic() == true && audioMixer->getMutedMusic() ==  true) Mix_PauseMusic();
        if (Mix_PausedMusic()  == true && audioMixer->getMutedMusic() == false) Mix_ResumeMusic();

        if (display != DISPLAY::RANKING) checkEndGame();

        // Handle Events
        while (SDL_PollEvent(events)) {

            //User requests quit
            if (events->type == SDL_QUIT) {
                quit = true;
                break;
            }

            mouse->mouseHandleEvent();

            switch (display) {
            case DISPLAY::HOME:
                eventsHome();
                break;
            case DISPLAY::PLAYER_NUMBER_SELECTION:
                eventsPlayerNumberSelection();
                break;
            case DISPLAY::GAME:
                eventsGame();
                break;
            case DISPLAY::MENU:
                eventsMenu();
                break;
            case DISPLAY::ALERT_RETURN_HOME:
                eventsAlertBoard(BOARD::RETURN_HOME);
                break;
            case DISPLAY::ALERT_RESTART_GAME:
                eventsAlertBoard(BOARD::RESTART_GAME);
                break;
            case DISPLAY::NOTI_SAVE_GAME:
                eventsSaveGame();
                break;
            case DISPLAY::ABOUT:
                eventsAbout();
                break;
            case DISPLAY::RANKING:
                eventsRank();
                break;
            }
        }

        // Update game status, draw the current frame
        switch (display) {
        case DISPLAY::HOME:
            setWindowHome();
            displayHome();
            break;
        case DISPLAY::PLAYER_NUMBER_SELECTION:
            setWindowPlayerNumberSelection();
            displayPlayerNumberSelection();
            break;
        case DISPLAY::GAME:
            setWindowGame();
            displayGame();
            break;
        case DISPLAY::MENU:
            setWindowMenu();
            displayMenu();
            break;
        case DISPLAY::ALERT_RETURN_HOME:
            displayAlertBoard(BOARD::RETURN_HOME);
            break;
        case DISPLAY::ALERT_RESTART_GAME:
            displayAlertBoard(BOARD::RESTART_GAME);
            break;
        case DISPLAY::NOTI_SAVE_GAME:
            displaySaveGame();
        case DISPLAY::ABOUT:
            displayAbout();
            break;
        case DISPLAY::RANKING:
            displayRank();
            break;
        }
        
        if (display != DISPLAY::RANKING) checkEndGame();

        // Cursor
        mouse->setRect({ mouse->getPosition_x(), mouse->getPosition_y(), 40, 40 });
        windowRenderer->rendererImage(mouse);
        SDL_ShowCursor(false);

        windowRenderer->displayImage();

        // FPS
        int real_time = fpsTimer.getTicks();
        int time_one_frame = 1000 / FRAME_PER_SECOND; // ms
        if (real_time < time_one_frame) {
            int delay_time = time_one_frame - real_time;
            if (delay_time >= 0) SDL_Delay(delay_time);
        }
    }

    audioMixer->closeAudio();
    windowRenderer->deleteWindow();
    SDL_Quit();
}