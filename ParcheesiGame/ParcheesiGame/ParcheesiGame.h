#ifndef __PARCHEESIGAME__
#define __PARCHEESIGAME__

#include <SDL.h>

using namespace std;

class ParcheesiGame {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
        void startGame();
};

#endif // __PARCHEESIGAME__
