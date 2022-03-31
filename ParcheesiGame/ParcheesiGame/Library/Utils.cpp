#include "Utils.h"

void MouseEvents::mouseHandleEvent() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    setPosition(x, y);
}

void MouseEvents::setPosition(int x, int y) {
    mousePosition_x = x;
    mousePosition_y = y;
}

bool MouseEvents::CheckMouseInButton(Button* button) {
    SDL_Rect rect = button->getSizeButton();

    //Mouse is left of the button
    if (mousePosition_x < rect.x) return false;

    //Mouse is right of the button
    if (mousePosition_x > rect.x + rect.w - 1) return false;

    //Mouse above the button
    if (mousePosition_y < rect.y) return false;

    //Mouse below the button
    if (mousePosition_y > rect.y + rect.h - 1) return false;

    return true;
}
