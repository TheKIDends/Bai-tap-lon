#include <iostream>
#include <stdio.h>
#include <SDL.h>

#include "Painter.h"

using namespace std;

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Parcheesi Game";

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);

void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    SDL_Texture* texture;
    SDL_Event events;

    Painter* painter = new Painter(window, renderer);

    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&events)) {
            //User requests quit
            if (events.type == SDL_QUIT) {
                quit = true;
                break;
            }

            //User presses a key
            if (events.type == SDL_KEYDOWN) {
                switch (events.key.keysym.sym) {
                case SDLK_UP:
                    texture = painter->loadTexture("img/cat.jpg");
                    painter->createImage(texture);
                    painter->displayImage();
                    break;

                case SDLK_DOWN:
                    cout << 2;
                    break;

                case SDLK_LEFT:
                    cout << 3;
                    break;

                case SDLK_RIGHT:
                    cout << 4;
                    break;
                }
            }
        }
    }

    // End

    quitSDL(window, renderer);
    return 0;
}

void logSDLError(std::ostream& os, const std::string& msg, bool fatal) {
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}