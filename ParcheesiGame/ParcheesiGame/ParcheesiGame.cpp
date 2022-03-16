#include "ParcheesiGame.h"

#include "Util.h"
#include "Painter.h"

#include <iostream>
#include <stdio.h>
#include <SDL.h>

using namespace std;

void ParcheesiGame::startGame() {
    Util* util = new Util;
    util->initSDL(window, renderer);

    Painter* painter = new Painter(window, renderer);

    SDL_Texture* background;
    background = painter->loadTexture("img/cat.png");
    painter->createImage(background, 0, 0, 600, 600);

    SDL_Texture* character;
    character = painter->loadTexture("img/01.png");
    painter->createImage(character, 0, 0, 100, 100);
       
    painter->displayImage();

    int x = 0, y = 0;

    SDL_Event events;
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
                        cout << 1;
                        y -= 20;
                        break;

                    case SDLK_DOWN:
                        y += 20;
                        cout << 2;
                        break;

                    case SDLK_LEFT:
                        x -= 20;
                        cout << 3;
                        break;

                    case SDLK_RIGHT:
                        x += 20;
                        cout << 4;
                        break;
                }
                painter->createImage(background, 0, 0, 600, 600);
                painter->createImage(character, x, y, 100, 100);
                painter->displayImage();
            }
        }
    }

    util->quitSDL(window, renderer);
}