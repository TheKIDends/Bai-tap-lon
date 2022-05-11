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

Painter::~Painter() {}

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

void Painter::setObject(SDL_Rect rect, SDL_Rect clip, string pathImg) {
    this->rect      = rect;
    this->clip      = clip;
    this->pathImg   = pathImg;
}

bool Painter::createRenderingImage(SDL_Renderer* renderer, SDL_Rect clip, SDL_Rect rect) {
    if (texture == NULL) return false;
    SDL_RenderCopy(renderer, texture, &clip, &rect);
    return true;
}

bool Painter::createImage(SDL_Texture* texture, SDL_Rect renderQuad) {
    if (texture == NULL) return false;
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
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
    texture = newTexture;
    return texture;
}

bool Painter::loadTexture(SDL_Renderer* renderer, string path) {
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
    texture = newTexture;
    return bool (texture != NULL);
}

bool Painter::displayImage() {
    if (renderer == NULL) return false;
    SDL_RenderPresent(renderer);
    return true;
}