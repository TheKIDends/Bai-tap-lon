#ifndef __PARCHEESIGAME__
#define __PARCHEESIGAME__

#include "FPS.h"
#include "GameComponents.h"
#include "WindowRenderer.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

enum DISPLAY{
    MENU,
    PLAYER_NUMBER_SELECTION,
    GAME,
};

enum STATE {
    ROLLDICE,
    CHOSECHESS,
    MOVECHESS,
    ENDTURN,
};

class ParcheesiGame {
    private:
        const int FRAME_PER_SECOND  = 60;
        const int SCREEN_WIDTH      = 1100;     // int (1747.0 * 0.63);
        const int SCREEN_HEIGHT     = 684;      // int (1086.0 * 0.63);
        const string WINDOW_TITLE   = "Parcheesi Game";

        DISPLAY display;
        int numberPlayers;
        int playerTurn;

        int idStartPosition[4];
        pair <int, int> mapChessBoard[100];

        MouseEvents* mouse;

        Dice* dice;
        Player* player[4];
        
        Button* playButton;
        Button* exitButton;
        Button* _2playersButton;
        Button* _3playersButton;
        Button* _4playersButton;
        Button* backButton;
        Button* rollButton;

        STATE statePlayer;

        SDL_Event* events = new SDL_Event;

        WindowRenderer* windowRenderer;

        void buildMap();

        void setGameObject();
        
        void displayMenu();
        void displayPlayerNumberSelection();
        void displayGame();

        void eventsMenu();
        void eventsPlayerNumberSelection();
        void eventsGame();

        bool canMove();
        bool checkIdInStartPosition(int idPosition);
        int chessNextStep(int idPosition);

    public:
        void startGame();
};

#endif // __PARCHEESIGAME__
