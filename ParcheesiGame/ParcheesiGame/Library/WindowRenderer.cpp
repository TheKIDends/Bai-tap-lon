#include "WindowRenderer.h"

void WindowRenderer::loadButton(Button* button) {
    if (button->getTexture() == NULL) button->loadTexture(renderer, button->getPathImg());

    if (!button->getStatus()) {
        button->createRenderingImage(renderer, button->getClip(), button->getRect());
    }
    else {
        button->createRenderingImage(renderer, { button->getClip().w, 0, button->getClip().w, button->getClip().h }, button->getRect());
    }
}

void WindowRenderer::loadAvatar(Player* player) {
    if (player->getTexture() == NULL) player->loadTexture(renderer, player->getPathImg());

    if (player->getWinner()) {
        player->createRenderingImage(renderer, { player->getClip().w, 0, player->getClip().w, player->getClip().h }, player->getRect());
    }
    else {
        player->createRenderingImage(renderer, player->getClip(), player->getRect());
    }
}

void WindowRenderer::loadArrow(int position_x, int position_y) {
    texture = painter->loadTexture("Image/can_move.png");
    painter->createImage(texture, { position_x, position_y, 10, 10 });
    deleteTexture();
}

void WindowRenderer::loadChess(int chessPosition_x, int chessPosition_y, Chess chess, int statusChess) {
    texture = painter->loadTexture(chess.getPathImg());
    SDL_Rect clipChess = chess.getClip();
    for (int i = 0; i < statusChess; ++i) clipChess.x += clipChess.w;
    painter->createRenderingImage(renderer, clipChess, { chessPosition_x, chessPosition_y, chess.getRect().w, chess.getRect().h });
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