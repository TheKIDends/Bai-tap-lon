#ifndef __COMMONFUNCTION__
#define __COMMONFUNCTION__

#include "AudioMixer.h"
#include "WindowRenderer.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

static Mouse* mouse = new Mouse;
static SDL_Event* events = new SDL_Event;
static AudioMixer* audioMixer = new AudioMixer;
static WindowRenderer* windowRenderer = new WindowRenderer;

// SCREEN

const int SCREEN_WIDTH	= 1100;     // int (1747.0 * 0.63);
const int SCREEN_HEIGHT = 684;      // int (1086.0 * 0.63);

// FRAME
const int FRAME_PER_SECOND = 20;

// TITLE
const string WINDOW_TITLE = "Parcheesi Game";

// 
const int MAX_PLAYERS = 4;
const int MAX_DICE = 6;
const int MAX_ID_MAP = 200;
const int MAX_LAYERS_CHESSBOARD = 7;
const int MAX_LAYERS_BACKGROUND = 2;



#endif // __COMMONFUNCTION__