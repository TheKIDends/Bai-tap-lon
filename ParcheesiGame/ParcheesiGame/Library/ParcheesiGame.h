#ifndef __PARCHEESIGAME__
#define __PARCHEESIGAME__

#include "WindowRenderer.h"
#include "Utils.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class ParcheesiGame {
    private:
        const int SCREEN_WIDTH      = 1747.0 * 0.63;
        const int SCREEN_HEIGHT     = 1086.0 * 0.63;
        const string WINDOW_TITLE   = "Parcheesi Game";

        int display, numberOfPlayers;

        SDL_Event* events = new SDL_Event;

        WindowRenderer* windowRenderer;

        void displayMenu();                   // display = 0

        void displayPlayerNumberSelection();  // display = 1

        void displayGame();                   // display = 2

    public:
        void startGame();
};

#endif // __PARCHEESIGAME__
