#ifndef __COMMONFUNCTION__
#define __COMMONFUNCTION__

#include "WindowRenderer.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

//static SDL_Window* window		= NULL;
//static SDL_Renderer* renderer	= NULL;
static SDL_Event* events = new SDL_Event;
static WindowRenderer* windowRenderer = new WindowRenderer;

// SCREEN

const int SCREEN_WIDTH		= 1100;     // int (1747.0 * 0.63);
const int SCREEN_HEIGHT		= 684;      // int (1086.0 * 0.63);

// FRAME
const int FRAME_PER_SECOND	= 60;

// TITLE
const string WINDOW_TITLE	= "Parcheesi Game";

#endif // __COMMONFUNCTION__