#include "WindowRenderer.h"

// Noti
void WindowRenderer::rendererNoti(Notification* noti, int idPlayer) {
    SDL_Rect clip = noti->getClip();
    for (int i = 0; i < idPlayer; ++i) clip.y += clip.h;

    noti->createImage(renderer, clip, noti->getRect());
}

// Button
void WindowRenderer::rendererButton(Button* button) {
    if (!button->getStatus()) {
        button->createImage(renderer, button->getClip(), button->getRect());
    }
    else {
        button->createImage(renderer, { button->getClip().w, button->getClip().y, button->getClip().w, button->getClip().h }, button->getRect());
    }
}

// Avatar
void WindowRenderer::rendererAvatar(Player player) {
    if (player.getWinner()) {
        player.createImage(renderer, { player.getClip().w, player.getClip().y, player.getClip().w, player.getClip().h }, player.getRect());
    }
    else {
        player.createImage(renderer, player.getClip(), player.getRect());
    }
}

void WindowRenderer::rendererAvatar(int position_x, int position_y, Player player) {
    SDL_Rect rect = player.getRect();
    rect.x = position_x;
    rect.y = position_y;
    if (player.getWinner()) {
        player.createImage(renderer, { player.getClip().w, player.getClip().y, player.getClip().w, player.getClip().h }, rect);
    }
    else {
        player.createImage(renderer, player.getClip(), rect);
    }
}


// Arrow
void WindowRenderer::rendererArrow(int position_x, int position_y, Arrow* arrow) {
    SDL_Rect rect = { position_x, position_y, arrow->getRect().w, arrow->getRect().h };

    if (arrow->getStatus()) {
        switch (arrow->getDirection()) {
            case DIRECTION::LEFT:
                rect.x -= arrow->getDistance();
                break;
            case DIRECTION::RIGHT:
                rect.x += arrow->getDistance();
                break;
            case DIRECTION::UP:
                rect.y -= arrow->getDistance();
                break;
            case DIRECTION::DOWN:
                rect.y += arrow->getDistance();
                break;
        }
    }

    arrow->createImage(renderer, arrow->getClip(), rect);
}

// Chess
void WindowRenderer::rendererChess(int chessPosition_x, int chessPosition_y, Chess* chess) {
    SDL_Rect clip = chess->getClip();
    
    for (int i = 0; i < chess->getStatus(); ++i) clip.x += clip.w;

    if (chess->getDirection() == LEFT) clip.y += 4 * clip.h;

    chess->createImage(renderer, clip, { chessPosition_x, chessPosition_y, chess->getRect().w, chess->getRect().h });
}

// Chessboard
void WindowRenderer::rendererChessboard(Chessboard chessboard) {
    SDL_Rect clip = chessboard.getClip();
    for (int i = 0; i < chessboard.getLayer(); ++i) clip.x += clip.w;
    chessboard.createImage(renderer, clip, chessboard.getRect());
}

// Back dice
void WindowRenderer::rendererBackDice(Image backDice, int idPlayer) {
    SDL_Rect clip = backDice.getClip();
    for (int i = 0; i < idPlayer; ++i) clip.x += clip.w;

    backDice.createImage(renderer, clip, backDice.getRect());
}

// Dice
void WindowRenderer::rendererDice(Dice dice) {
    SDL_Rect clip = dice.getClip();
    for (int i = 0; i < dice.getNumDice(); ++i) clip.x += clip.w;

    dice.createImage(renderer, clip, dice.getRect());
}

void WindowRenderer::rendererDiceAnimations(Dice dice) {
    SDL_Rect clip = dice.getClip();
    clip.y -= clip.h;
    for (int i = 0; i < dice.getStatus(); ++i) clip.x += clip.w;
    dice.createImage(renderer, clip, dice.getRect());
}

// Background
void WindowRenderer::rendererBackground(Background* background) {
    SDL_Rect clip = background->getClip();
    for (int i = 0; i < background->getStatus(); ++i) clip.x += clip.w;
    background->createImage(renderer, clip, background->getRect());
}

void WindowRenderer::displayImage() {
    painter->displayImage();
}

// Init SDL
void WindowRenderer::createWindow(int screenWidth, int screenHeight, string windowTitle, string pathWindowIcon) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);

    // Create window icon
    SDL_Surface* surfaceIcon = IMG_Load(pathWindowIcon.c_str());
    if (surfaceIcon == NULL) cout << "Unable to load surfaceIcon " << pathWindowIcon << " SDL_image Error: " << IMG_GetError() << '\n';
    else SDL_SetWindowIcon(window, surfaceIcon);

    painter = new Painter(window, renderer);
}

void WindowRenderer::deleteWindow() {
    IMG_Quit();
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