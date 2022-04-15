#include "WindowRenderer.h"

void WindowRenderer::loadButton(Button* button) {
//    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
//    SDL_RenderDrawLine(renderer, 0, 100, 100, 100);

    if (!button->getTypeButton()) {
        texture = painter->loadTexture(button->getLinkImgButton());
        painter->createRenderingImage(texture, { 0, 0, button->getClipWidthButton(), button->getClipHeightButton() }, button->getSizeButton());
    }
    else {
        texture = painter->loadTexture(button->getLinkImgButton());
        painter->createRenderingImage(texture, { button->getClipWidthButton(), 0, button->getClipWidthButton(), button->getClipHeightButton() }, button->getSizeButton());
    }
    deleteTexture();
}

void WindowRenderer::loadAvatar(Player* player) {
    if (player->getWinner()) {
        texture = painter->loadTexture(player->getLinkImgAvatar());
        painter->createRenderingImage(texture, { 128, 0, player->getClipWidthAvatar(), player->getClipHeightAvatar() }, player->getSizeAvatar());
    }
    else {
        texture = painter->loadTexture(player->getLinkImgAvatar());
        painter->createRenderingImage(texture, { 0, 0, player->getClipWidthAvatar(), player->getClipHeightAvatar() }, player->getSizeAvatar());
    }
    deleteTexture();
}

void WindowRenderer::loadChess(int chessPosition_x, int chessPosition_y, Chess chess) {
    texture = painter->loadTexture(chess.getLinkImgChess());
    painter->createRenderingImage(texture, chess.getClipChess(), { chessPosition_x, chessPosition_y, chess.getWidthChess(), chess.getHeightChess() });

    if (chess.getCanMoveChess()) {
        texture = painter->loadTexture("Image/can_move.png");
        painter->createImage(texture, { chessPosition_x + 10, chessPosition_y + 7, 10, 10 });
    }
    deleteTexture();
}

void WindowRenderer::loadChessBoard(int numLayer) {
    for (int i = numLayer; i >= 1; --i) {
        string add = string("Image/chess_board/img") + char(i + '0') + string(".png");
        texture = painter->loadTexture(add);
        painter->createImageFullWindow(texture);
        deleteTexture();
    }
}

void WindowRenderer::loadBackGround(string linkImgBackGround) {
    texture = painter->loadTexture(linkImgBackGround);
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