#ifndef __UTIL__
#define __UTIL__

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Util {
    private:
        const int SCREEN_WIDTH      = 600;
        const int SCREEN_HEIGHT     = 600;
        const string WINDOW_TITLE   = "Parcheesi Game";
    public:
        void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);

        void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);

        void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
};

#endif // __UTIL__
