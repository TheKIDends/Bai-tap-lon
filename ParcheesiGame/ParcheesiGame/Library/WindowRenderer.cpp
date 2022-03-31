#include "WindowRenderer.h"

void WindowRenderer::loadButton(int typeButton, Button* button) {
    if (!typeButton) {
        texture = painter->loadTexture(button->getLinkImgButton());
        painter->createRenderingImage(texture, { 0, 0, button->getClipWidthButton(), button->getClipHeightButton() }, button->getSizeButton());
    }
    else {
        texture = painter->loadTexture(button->getLinkImgButton());
        painter->createRenderingImage(texture, { button->getClipWidthButton(), 0, button->getClipWidthButton(), button->getClipHeightButton() }, button->getSizeButton());
    }
}

void WindowRenderer::loadChessBoard() {
    for (int i = 7; i >= 1; --i) {
        string add = string("Image/chess_board/img") + char(i + '0') + string(".png");
        texture = painter->loadTexture(add);
        painter->createImageFullWindow(texture);
    }
}

void WindowRenderer::loadBackGround(string linkImgBackGround) {
    texture = painter->loadTexture(linkImgBackGround);
    painter->createImageFullWindow(texture);
}

void WindowRenderer::displayImage() {
    painter->displayImage();
}

void WindowRenderer::createWindow(int screenWidth, int screenHeight, string windowTitle) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);

    painter = new Painter(window, renderer);
}

void WindowRenderer::deleteWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void WindowRenderer::logSDLError(std::ostream& os, const std::string& msg, bool fatal) {
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}