#include "WindowRenderer.h"

void WindowRenderer::loadButton(Button button) {
//    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
//    SDL_RenderDrawLine(renderer, 0, 100, 100, 100);

    if (!button.getTypeButton()) {
        texture = painter->loadTexture(button.getPathImgButton());
        painter->createRenderingImage(texture, { 0, 0, button.getClipWidthButton(), button.getClipHeightButton() }, button.getSizeButton());
    }
    else {
        texture = painter->loadTexture(button.getPathImgButton());
        painter->createRenderingImage(texture, { button.getClipWidthButton(), 0, button.getClipWidthButton(), button.getClipHeightButton() }, button.getSizeButton());
    }
    deleteTexture();
}

void WindowRenderer::loadAvatar(Player* player) {
    if (player->getWinner()) {
        texture = painter->loadTexture(player->getPathImgAvatar());
        painter->createRenderingImage(texture, { 128, 0, player->getClipWidthAvatar(), player->getClipHeightAvatar() }, player->getSizeAvatar());
    }
    else {
        texture = painter->loadTexture(player->getPathImgAvatar());
        painter->createRenderingImage(texture, { 0, 0, player->getClipWidthAvatar(), player->getClipHeightAvatar() }, player->getSizeAvatar());
    }
    deleteTexture();
}

void WindowRenderer::loadArrow(int position_x, int position_y) {
    texture = painter->loadTexture("Image/can_move.png");
    painter->createImage(texture, { position_x, position_y, 10, 10 });
    deleteTexture();
}

void WindowRenderer::loadChess(int chessPosition_x, int chessPosition_y, Chess chess, int stateChess) {
    texture = painter->loadTexture(chess.getPathImgChess());

    SDL_Rect clipChess = chess.getClipChess();
    for (int i = 0; i < stateChess; ++i) clipChess.x += clipChess.w;
    painter->createRenderingImage(texture, clipChess, { chessPosition_x, chessPosition_y, chess.getWidthChess(), chess.getHeightChess() });
    deleteTexture();
}

void WindowRenderer::loadImgFullWindow(string pathImage) {
    texture = painter->loadTexture(pathImage);
    painter->createImageFullWindow(texture);
    deleteTexture();
}

void WindowRenderer::displayImage() {
    painter->displayImage();
}

void WindowRenderer::createWindow(int screenWidth, int screenHeight, string windowTitle) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

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