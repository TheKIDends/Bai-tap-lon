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

CLICK MouseEvents::CheckMouseInRect(SDL_Rect rect) {
    // Mouse is left of the rect
    if (mousePosition_x < rect.x) return NORMAL;

    //Mouse is right of the rect
    if (mousePosition_x > rect.x + rect.w - 1) return NORMAL;

    //Mouse above the rect
    if (mousePosition_y < rect.y) return NORMAL;

    //Mouse below the rect
    if (mousePosition_y > rect.y + rect.h - 1) return NORMAL;

    return ON_CLICK;
}

CLICK MouseEvents::CheckMouseInButton(Button button) {
    return CheckMouseInRect(button.getRect());
}

CLICK MouseEvents::CheckMouseInChess(int chessPosition_x, int chessPosition_y, Chess chess) {
    return CheckMouseInRect({ chessPosition_x, chessPosition_y, chess.getRect().w, chess.getRect().h });
}