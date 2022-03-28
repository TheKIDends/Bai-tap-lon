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
    //Mouse is left of the button
    if (mousePosition_x < button->getButtonPosition_x()) return false;

    //Mouse is right of the button
    if (mousePosition_x > button->getButtonPosition_x() + button->getButtonWidth() - 1) return false;

    //Mouse above the button
    if (mousePosition_y < button->getButtonPosition_y()) return false;

    //Mouse below the button
    if (mousePosition_y > button->getButtonPosition_y() + button->getButtonHeight() - 1) return false;

    return true;
}
