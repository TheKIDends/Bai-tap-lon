#include "GameComponents.h"

// Button

void Button::setButton(SDL_Rect sizeButton, int clipWidthButton, int clipHeightButton, string pathImgButton) {
    this->clipWidthButton   = clipWidthButton;
    this->clipHeightButton  = clipHeightButton;
    this->sizeButton        = sizeButton;
    this->pathImgButton     = pathImgButton;
}

// Chess

void Chess::setChess(int widthChess, int heightChess, SDL_Rect clipChess, string pathImgChess) {
    this->widthChess      = widthChess;
    this->heightChess     = heightChess;
    this->clipChess       = clipChess;
    this->pathImgChess    = pathImgChess;
}

// Player

void Player::setAllChessPlayer(int widthChess, int heightChess, SDL_Rect clipChess, string pathImgChess) {
    for (int i = 0; i < 4; ++i) {
        chess[i].setChess(widthChess, heightChess, clipChess, pathImgChess);
    }
}

void Player::setAvatarPlayer(SDL_Rect sizeAvatar, int clipWidthAvatar, int clipHeightAvatar, string pathImgAvatar) {
    this->clipWidthAvatar   = clipWidthAvatar;
    this->clipHeightAvatar  = clipHeightAvatar;
    this->pathImgAvatar     = pathImgAvatar;
    this->sizeAvatar        = sizeAvatar;
}

// MouseEvents

void MouseEvents::mouseHandleEvent() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    setPosition(x, y);
}

void MouseEvents::setPosition(int x, int y) {
    mousePosition_x = x;
    mousePosition_y = y;
}

bool MouseEvents::CheckMouseInRect(SDL_Rect rect) {
    // Mouse is left of the rect
    if (mousePosition_x < rect.x) return false;

    //Mouse is right of the rect
    if (mousePosition_x > rect.x + rect.w - 1) return false;

    //Mouse above the rect
    if (mousePosition_y < rect.y) return false;

    //Mouse below the rect
    if (mousePosition_y > rect.y + rect.h - 1) return false;

    return true;
}

bool MouseEvents::CheckMouseInButton(Button* button) {
    return CheckMouseInRect(button->getSizeButton());
}

bool MouseEvents::CheckMouseInChess(int chessPosition_x, int chessPosition_y, Chess chess) {
    return CheckMouseInRect({ chessPosition_x, chessPosition_y, chess.getWidthChess(), chess.getHeightChess() });
}