#ifndef __UTILS__
#define __UTILS__

#include "GameComponents.h"

#include <iostream>
#include <SDL.h>

using namespace std;

class MouseEvents {
    private:
        int mousePosition_x;
        int mousePosition_y;

        void setPosition(int x, int y);

    public:
        void mouseHandleEvent();

        bool CheckMouseInButton(Button* button);
};

#endif // __UTILS__
