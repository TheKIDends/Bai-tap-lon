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
        case EXIT_MENU:
            return exit;
            break;
        case HOME_BUTTON:
            return home;
            break;
        case RESTART_BUTTON:
            return restart;
            break;
        case SAVE_BUTTON:
            return save;
            break;
        case ABOUT_BUTTON:
            return about;
            break;
        case MUSIC_BUTTON:
            return music;
            break;
        case SOUND_BUTTON:
            return sound;
            break;
    }
}

Button* MenuBoard::getButton_It(BUTTON nameButton) {
    switch (nameButton) {
        case EXIT_MENU:
            return &exit;
            break;
        case HOME_BUTTON:
            return &home;
            break;
        case RESTART_BUTTON:
            return &restart;
            break;
        case SAVE_BUTTON:
            return &save;
            break;
        case ABOUT_BUTTON:
            return &about;
            break;
        case MUSIC_BUTTON:
            return &music;
            break;
        case SOUND_BUTTON:
            return &sound;
            break;
    }
}

Board MenuBoard::getBoard(BOARD nameBoard) {
    switch (nameBoard) {
        case RETURN_HOME:
            return returnHome;
            break;
        case RESTART_GAME:
            return restartGame;
            break;
        case SAVE_GAME:
            return saveGame;
            break;
    }
}

Board* MenuBoard::getBoard_It(BOARD nameBoard) {
    switch (nameBoard) {
        case RETURN_HOME:
            return &returnHome; 
            break;
        case RESTART_GAME:
            return &restartGame;
            break;
        case SAVE_GAME:
            return &saveGame;
            break;
    }
}


// MouseEvents

void Mouse::mouseHandleEvent() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    setPosition(x, y);
}

void Mouse::setPosition(int x, int y) {
    position_x = x;
    position_y = y;
}

CLICK Mouse::CheckMouseInRect(SDL_Rect rect) {
    // Mouse is left of the rect
    if (position_x < rect.x) return NORMAL;

    //Mouse is right of the rect
    if (position_x > rect.x + rect.w - 1) return NORMAL;

    //Mouse above the rect
    if (position_y < rect.y) return NORMAL;

    //Mouse below the rect
    if (position_y > rect.y + rect.h - 1) return NORMAL;

    return ON_CLICK;
}

CLICK Mouse::CheckMouseInButton(Button button) {
    return CheckMouseInRect(button.getRect());
}

CLICK Mouse::CheckMouseInDice(Dice dice) {
    return CheckMouseInRect(dice.getRect());
}

CLICK Mouse::CheckMouseInChess(int chessPosition_x, int chessPosition_y, Chess* chess) {
    return CheckMouseInRect({ chessPosition_x, chessPosition_y, chess->getRect().w, chess->getRect().h });
}