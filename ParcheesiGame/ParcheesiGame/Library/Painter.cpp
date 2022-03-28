#include "Painter.h"

Painter::Painter(SDL_Window* window, SDL_Renderer* renderer_) : renderer(renderer_) {
    int width, height;
    
    SDL_RenderGetLogicalSize(renderer, &width, &height);

    if (!width && !height)
        SDL_GetWindowSize(window, &width, &height);

    setPosition(width / 2, height / 2);
    setAngle(0);
    setColor(WHITE_COLOR);
    clearWithBgColor(DEFAULT_COLOR);
}

void Painter::clearWithBgColor(SDL_Color bgColor) {
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
}

void Painter::setColor(SDL_Color color) {
    this->color = color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
}

void Painter::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void Painter::setAngle(float angle) {
    this->angle = angle - floor(angle / 360) * 360;
}

bool Painter::createImage(SDL_Texture* texture, Button* button) {
    if (texture == NULL) return false;
    SDL_Rect dstrect = { button->getButtonPosition_x(), button->getButtonPosition_y(), button->getButtonWidth(), button->getButtonHeight() };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    return true;
}

bool Painter::createImage(SDL_Texture* texture, int x, int y, int w, int h) {
    if (texture == NULL) return false;
    SDL_Rect dstrect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    return true;
}

bool Painter::createImageFullWindow(SDL_Texture * texture) {
    if (texture == NULL) return false;
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    return true;
}

SDL_Texture* Painter::loadTexture(string path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << '\n';
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << '\n';
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool Painter::displayImage() {
    if (renderer == NULL) return false;
    SDL_RenderPresent(renderer);
    return true;
}