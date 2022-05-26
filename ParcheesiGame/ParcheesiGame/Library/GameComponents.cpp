#include "GameComponents.h"

// Player

void Player::setAllChessPlayer(SDL_Rect rect, SDL_Rect clip, string pathImg) {
    for (int i = 0; i < 4; ++i) chess[i].setObject(rect, clip, pathImg);
}

void Player::setAvatarPlayer(SDL_Rect rect, SDL_Rect clip, string pathImg) {
    this->rect = rect;
    this->clip = clip;
    this->pathImg = pathImg;
}

// Menu board
Button MenuBoard::getButton(BUTTON nameButton) {
    switch (nameButton) {
        case BUTTON::EXIT_MENU:
            return exit;
            break;
        case BUTTON::HOME_BUTTON:
            return home;
            break;
        case BUTTON::RESTART_BUTTON:
            return restart;
            break;
        case BUTTON::SAVE_BUTTON:
            return save;
            break;
        case BUTTON::ABOUT_BUTTON:
            return about;
            break;
        case BUTTON::MUSIC_BUTTON:
            return music;
            break;
        case BUTTON::CHUNK_BUTTON:
            return sound;
            break;
    }
}

Button* MenuBoard::getButton_It(BUTTON nameButton) {
    switch (nameButton) {
        case BUTTON::EXIT_MENU:
            return &exit;
            break;
        case BUTTON::HOME_BUTTON:
            return &home;
            break;
        case BUTTON::RESTART_BUTTON:
            return &restart;
            break;
        case BUTTON::SAVE_BUTTON:
            return &save;
            break;
        case BUTTON::ABOUT_BUTTON:
            return &about;
            break;
        case BUTTON::MUSIC_BUTTON:
            return &music;
            break;
        case BUTTON::CHUNK_BUTTON:
            return &sound;
            break;
    }
}

Board MenuBoard::getBoard(BOARD nameBoard) {
    switch (nameBoard) {
        case BOARD::RETURN_HOME:
            return returnHome;
            break;
        case BOARD::RESTART_GAME:
            return restartGame;
            break;
        case BOARD::SAVE_GAME:
            return saveGame;
            break;
    }
}

Board* MenuBoard::getBoard_It(BOARD nameBoard) {
    switch (nameBoard) {
        case BOARD::RETURN_HOME:
            return &returnHome; 
            break;
        case BOARD::RESTART_GAME:
            return &restartGame;
            break;
        case BOARD::SAVE_GAME:
            return &saveGame;
            break;
    }
}