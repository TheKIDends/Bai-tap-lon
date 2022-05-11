#include "WindowRenderer.h"

// Button
void WindowRenderer::loadButton(Button button) {
    if (!button.getStatus()) {
        button.createRenderingImage(renderer, button.getClip(), button.getRect());
    }
    else {
        button.createRenderingImage(renderer, { button.getClip().w, 0, button.getClip().w, button.getClip().h }, button.getRect());
    }
}

// Avatar
void WindowRenderer::loadAvatar(Player player) {
    if (player.getWinner()) {
        player.createRenderingImage(renderer, { player.getClip().w, 0, player.getClip().w, player.getClip().h }, player.getRect());
    }
    else {
        player.createRenderingImage(renderer, player.getClip(), player.getRect());
    }
}

// Arrow
void WindowRenderer::loadArrow(int position_x, int position_y) {
    texture = painter->loadTexture("Image/can_move.png");
    painter->createImage(texture, { position_x, position_y, 10, 10 });
    deleteTexture();
}

// Chess
void WindowRenderer::loadChess(int chessPosition_x, int chessPosition_y, Chess chess, int statusChess) {
    SDL_Rect clip = chess.getClip();
    
    for (int i = 0; i < statusChess; ++i) clip.x += clip.w;

    if (chess.getDirection() == LEFT) clip.y += 4 * clip.h;

    chess.createRenderingImage(renderer, clip, { chessPosition_x, chessPosition_y, chess.getRect().w, chess.getRect().h });
}

// Chessboard
void WindowRenderer::loadChessboard(Chessboard chessboard) {
    SDL_Rect clip = chessboard.getClip();
    for (int i = 0; i < chessboard.getLayer(); ++i) clip.x += clip.w;
    chessboard.createRenderingImage(renderer, clip, chessboard.getRect());
}

// Back dice
void WindowRenderer::loadBackDice(BackDice backDice, int idPlayer) {
    SDL_Rect rect;
    if (idPlayer == 0) rect = { 150, 540, 160 , 132 };
    if (idPlayer == 1) rect = { 792, 540, 160 , 132 };
    if (idPlayer == 2) rect = { 792, 5, 160 , 132 };
    if (idPlayer == 3) rect = { 150, 5, 160 , 132 };

    SDL_Rect clip = backDice.getClip();
    for (int i = 0; i < idPlayer; ++i) clip.x += clip.w;
    backDice.createRenderingImage(renderer, clip, rect);
}

// Dice
void WindowRenderer::loadDice(Dice dice) {
    SDL_Rect clip = dice.getClip();
    for (int i = 0; i < dice.getNumDice(); ++i) clip.x += clip.w;

    dice.createRenderingImage(renderer, clip, dice.getRect());
}

void WindowRenderer::loadDiceAnimations(Dice dice, int status) {
    SDL_Rect clip = dice.getClip();
    clip.y -= clip.h;
    for (int i = 0; i < status; ++i) clip.x += clip.w;

    dice.createRenderingImage(renderer, clip, dice.getRect());
}

// Background
void WindowRenderer::loadBackground(Background background) {
    SDL_Rect clip = background.getClip();
    for (int i = 0; i < background.getLayer(); ++i) clip.x += clip.w;
    background.createRenderingImage(renderer, clip, background.getRect());
}

void WindowRenderer::displayImage() {
    painter->displayImage();
}

// Init SDL
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