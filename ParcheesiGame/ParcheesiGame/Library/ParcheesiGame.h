#ifndef __PARCHEESIGAME__
#define __PARCHEESIGAME__

#include "FPS.h"
#include "GameComponents.h"
#include "WindowRenderer.h"
#include "Animations.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <exception>

using namespace std;

enum DISPLAY{
    MENU,
    PLAYER_NUMBER_SELECTION,
    GAME,
};

enum STATE {
    ROLLDICE,
    CHOOSECHESS,
    ENDTURN,
};

class ParcheesiGame {
    private:
        const int FRAME_PER_SECOND  = 60;
        const int SCREEN_WIDTH      = 1100;     // int (1747.0 * 0.63);
        const int SCREEN_HEIGHT     = 684;      // int (1086.0 * 0.63);
        const string WINDOW_TITLE   = "Parcheesi Game";

        DISPLAY display;
        int numberPlayers = 4;
        int playerTurn;

        ArrowAnimations arrowAnimations = ArrowAnimations(2);
        ChessAnimations chessAnimation = ChessAnimations(3);
        BackgroundAnimations backgroundAnimations = BackgroundAnimations(2);

        int idStartPosition[4];
        pair <int, int> mapChessBoard[100];

        MouseEvents* mouse;

        Dice* dice;
        Player* player[4];
        
        Button playButton;
        Button exitButton;
        Button _2playersButton;
        Button _3playersButton;
        Button _4playersButton;
        Button backButton;
        Button rollButton;

        STATE statePlayer;

        SDL_Event* events = new SDL_Event;

        WindowRenderer* windowRenderer;

        void buildMap();

        void setGameObject();
        
        bool idChessInLayer(int idPositionChess, int layer);

        void displayMenu();
        void displayPlayerNumberSelection();
        void displayGame();

        void eventsMenu();
        void eventsPlayerNumberSelection();
        void eventsGame();

        bool canMove();
        bool checkIdInStartPosition(int idPosition);
        int chessNextStep(int idPosition);
        int idMoveForward(int idPosition);

        void animationMoveChess();

    public:
        void startGame();
};

#endif // __PARCHEESIGAME__
