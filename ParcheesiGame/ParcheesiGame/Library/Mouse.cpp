#include "Mouse.h"

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
    if (position_x < rect.x) return CLICK::NORMAL;

    //Mouse is right of the rect
    if (position_x > rect.x + rect.w - 1) return CLICK::NORMAL;

    //Mouse above the rect
    if (position_y < rect.y) return CLICK::NORMAL;

    //Mouse below the rect
    if (position_y > rect.y + rect.h - 1) return CLICK::NORMAL;

    return CLICK::ON_CLICK;
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