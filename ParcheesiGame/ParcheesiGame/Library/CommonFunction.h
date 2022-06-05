#ifndef __COMMONFUNCTION__
#define __COMMONFUNCTION__

#include "FPS.h"
#include "GameComponents.h"
#include "WindowRenderer.h"
#include "Mouse.h"
#include "AudioMixer.h"
#include "Animations.h"

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
const int SCREEN_HEIGHT =  684;      // int (1086.0 * 0.63);

// FRAME
const int FRAME_PER_SECOND = 20;

// TITLE
const string WINDOW_TITLE = "Parcheesi Game";

//
const int MAX_NUMBER_CHESS			=   4;
const int MAX_NUMBER_PLAYERS		=   4;
const int MAX_DICE					=   6;
const int MAX_ID_MAP				= 200;
const int MAX_LAYERS_CHESSBOARD		=   7;
const int MAX_LAYERS_BACKGROUND		=   2;
const int MAX_ID_RACETRACK			=  71;
const int NUMBER_ID_RACETRACK		=  56;
const int NUMBER_ID_STABLE			=   6;
const int NUMBER_ID_START			=  15;

const int ANIMATION_MOVE_CHESS_TIME_FPS = 45;
const int BACKGROUND_TIME_FPS = 400;

const SDL_Rect BASE_RECT = { 0, 0, 0, 0 };


// Game Components

const SDL_Rect MOUSE_CLIP = { 0, 0, 512, 512 };

const SDL_Rect LEADERBOARD_RECT = { 211, 23, 695, 439 };
const SDL_Rect LEADERBOARD_CLIP = {  0,   0, 695, 439 };

const SDL_Rect TITLE_RECT = { 100,  30, 923, 270 };
const SDL_Rect TITLE_CLIP = {   0,   0, 923, 270 };

const SDL_Rect BACKGROUND_RECT = { 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT };
const SDL_Rect BACKGROUND_CLIP = { 0, 0, 1494, 840 };

const SDL_Rect ARROW_RECT = { 0,  0,  10, 10 };
const SDL_Rect ARROW_CLIP = { 0,  0, 122, 98 };
const int ARROW_DISTANCE  = 3;

const SDL_Rect ARROW_CLICK_TO_ROLL_RECT = {  0,  0, 60, 60 };
const SDL_Rect ARROW_CLICK_TO_ROLL_CLIP = {  0, 98, 98, 98 };
const int ARROW_CLICK_TO_ROLL_DISTANCE  = 7;

const SDL_Rect AVATAR_PLAYER_0_RECT = {  18, 551, 110, 115 };
const SDL_Rect AVATAR_PLAYER_0_CLIP = {   0,   0, 128, 138 };

const SDL_Rect AVATAR_PLAYER_1_RECT = { 972, 551, 110, 115 };
const SDL_Rect AVATAR_PLAYER_1_CLIP = {   0,   0, 128, 138 };

const SDL_Rect AVATAR_PLAYER_2_RECT = { 972,  18, 110, 115 };
const SDL_Rect AVATAR_PLAYER_2_CLIP = {   0,   0, 128, 138 };

const SDL_Rect AVATAR_PLAYER_3_RECT = {  18,  18, 110, 115 };
const SDL_Rect AVATAR_PLAYER_3_CLIP = {   0,   0, 128, 138 };

const SDL_Rect CHESS_RECT = { 0, 0, 35, 64 };
const SDL_Rect CHESS_CLIP = { 0, 0, 54, 99 };

const SDL_Rect CHESSBOARD_RECT = { 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT };
const SDL_Rect CHESSBOARD_CLIP = { 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT };

const SDL_Rect BACK_DICE_CLIP  = { 0, 0, 160, 132 };

const SDL_Rect NOTI_LOSER_RECT = { 122, 400, 850, 180 };
const SDL_Rect NOTI_LOSER_CLIP = {   0,   0, 850, 180 };

const SDL_Rect BOOM_RECT = { 0, 0, 138,  66 };
const SDL_Rect BOOM_CLIP = { 0, 0, 212, 100 };

const SDL_Rect NOTI_CAN_NOT_MOVE_RECT = { 122, 233, 850, 180 };
const SDL_Rect NOTI_CAN_NOT_MOVE_CLIP = {   0,   0, 850, 180 };

const SDL_Rect DICE_CLIP = { 0, 150, 150, 150 };

const SDL_Rect BACK_HOME_RECT = { 475, 600, 160, 57 };
const SDL_Rect BACK_HOME_CLIP = {   0,   0, 232, 82 };

const SDL_Rect PLAY_BUTTON_RECT = { 407, 273,  265, 103 };
const SDL_Rect PLAY_BUTTON_CLIP = {   0,   0, 1326, 515 };

const SDL_Rect EXIT_BUTTON_RECT = { 431, 534,  221,  85 };
const SDL_Rect EXIT_BUTTON_CLIP = {   0,   0, 1326, 515 };

const SDL_Rect BACK_BUTTON_RECT = { 999, 579,   74,  82 };
const SDL_Rect BACK_BUTTON_CLIP = {   0,   0,  448, 497 };

const SDL_Rect CONTINUE_BUTTON_RECT = { 383, 402,  312, 102 };
const SDL_Rect CONTINUE_BUTTON_CLIP = {   0,   0, 1560, 513 };

const SDL_Rect _2PLAYERS_BUTTON_RECT = { 379, 171,  312, 102 };
const SDL_Rect _2PLAYERS_BUTTON_CLIP = {   0,   0, 1560, 513 };

const SDL_Rect _3PLAYERS_BUTTON_RECT = { 379, 315,  312, 102 };
const SDL_Rect _3PLAYERS_BUTTON_CLIP = {   0,   0, 1560, 513 };

const SDL_Rect _4PLAYERS_BUTTON_RECT = { 379, 456,  312, 102 };
const SDL_Rect _4PLAYERS_BUTTON_CLIP = {   0,   0, 1560, 513 };


// Board Components

const SDL_Rect RETURN_HOME_BOARD_RECT = { 417, 204, 277, 215 };
const SDL_Rect RETURN_HOME_BOARD_CLIP = {   0,   0, 387, 300 };

const SDL_Rect RESTART_GAME_BOARD_RECT = { 417, 204, 277, 215 };
const SDL_Rect RESTART_GAME_BOARD_CLIP = {   0,   0, 387, 300 };

const SDL_Rect SAVE_GAME_BOARD_RECT = { 417, 220, 277, 197 };
const SDL_Rect SAVE_GAME_BOARD_CLIP = {   0,   0, 387, 275 };

const SDL_Rect YES_BUTTON_RECT = { 458, 340,  82,  41 };
const SDL_Rect YES_BUTTON_CLIP = {   0,   0, 250, 127 };

const SDL_Rect NO_BUTTON_RECT = { 575, 340,  82,  41 };
const SDL_Rect NO_BUTTON_CLIP = {   0,   0, 250, 127 };

const SDL_Rect OK_BUTTON_RECT = { 518, 355,  82,  41 };
const SDL_Rect OK_BUTTON_CLIP = {   0,   0, 250, 127 };


// Menu Components

const SDL_Rect MENU_BOARD_RECT = { 392, 76, 326, 514 };
const SDL_Rect MENU_BOARD_CLIP = {   0,  0, 326, 514 };

const SDL_Rect MENU_BACKGROUND_RECT = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
const SDL_Rect MENU_BACKGROUND_CLIP = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

const SDL_Rect OPEN_MENU_RECT = { 19, 180, 68, 68 };
const SDL_Rect OPEN_MENU_CLIP = {  0,   0, 68, 68 };

const SDL_Rect EXIT_MENU_RECT = { 633, 76, 82, 82 };
const SDL_Rect EXIT_MENU_CLIP = {   0,  0, 82, 82 };

const SDL_Rect HOME_BUTTON_RECT = { 442, 164, 232, 82 };
const SDL_Rect HOME_BUTTON_CLIP = {   0,   0, 232, 82 };

const SDL_Rect RESTART_BUTTON_RECT = { 442, 255, 232, 82 };
const SDL_Rect RESTART_BUTTON_CLIP = {   0,   0, 232, 82 };

const SDL_Rect SAVE_BUTTON_RECT = { 442, 346, 232, 82 };
const SDL_Rect SAVE_BUTTON_CLIP = {   0,   0, 232, 82 };

const SDL_Rect ABOUT_BUTTON_RECT = { 427, 458, 76, 76 };
const SDL_Rect ABOUT_BUTTON_CLIP = {   0,   0, 76, 76 };

const SDL_Rect MUSIC_BUTTON_RECT = { 463, 459, 76, 76 }; // { 517, 458, 76, 76 }
const SDL_Rect MUSIC_BUTTON_CLIP = {   0,   0, 76, 76 };

const SDL_Rect CHUNK_BUTTON_RECT = { 573, 459, 76, 76 }; // { 609, 458, 76, 76 }
const SDL_Rect CHUNK_BUTTON_CLIP = {   0,   0, 76, 76 }; 


#endif // __COMMONFUNCTION__