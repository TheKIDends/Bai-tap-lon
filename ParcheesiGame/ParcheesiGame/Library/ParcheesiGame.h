#ifndef __PARCHEESIGAME__
#define __PARCHEESIGAME__

#include "WindowRenderer.h"

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class ParcheesiGame {
    private:
        const int SCREEN_WIDTH      = 1747.0 * 0.63;
        const int SCREEN_HEIGHT     = 1086.0 * 0.63;
        const string WINDOW_TITLE   = "Parcheesi Game";

    public:
        void startGame();
};

#endif // __PARCHEESIGAME__
