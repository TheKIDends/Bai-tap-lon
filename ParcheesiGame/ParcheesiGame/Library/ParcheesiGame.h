#ifndef __PARCHEESIGAME__
#define __PARCHEESIGAME__

#include "FPS.h"
#include "CommonFunction.h"
#include "GameComponents.h"
#include "WindowRenderer.h"
#include "Animations.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <exception>

using namespace std;

enum DISPLAY {
    MENU,
    PLAYER_NUMBER_SELECTION,
    GAME,
};

enum STATUS_PLAYER {
    ROLLDICE,
    CHOOSECHESS,
    ENDTURN,
};

class ParcheesiGame {
    private:
        DISPLAY display;

        STATUS_PLAYER statusPlayer;
        int numberPlayers = 4;
        int playerTurn;

        DiceAnimations diceAnimations = DiceAnimations(6);
        ArrowAnimations arrowAnimations = ArrowAnimations(2);
        ChessAnimations chessAnimations = ChessAnimations(3);

        int idStartPosition[4];
        pair <int, int> mapChessboard[100];

        MouseEvents* mouse;

        Background background = Background(2);
        Chessboard chessboard = Chessboard(7);

        BackDice backDice;
        Dice dice;
        Player player[4];

        Button playButton;
        Button exitButton;
        Button _2playersButton;
        Button _3playersButton;
        Button _4playersButton;
        Button backButton;

        void buildMap();

        void setGameComponents();

        bool checkIdChessInLayer(int idPositionChess, int layer);

        void displayMenu();
        void displayPlayerNumberSelection();
        void displayGame();

        void eventsMenu();
        void eventsPlayerNumberSelection();
        void eventsGame();

        bool canMove();
        bool checkIdInStartPosition(int idPosition);
        int  chessNextStep(int idPosition);
        int  idMoveForward(int idPosition);

        void animationMoveChess();
        void animationRollDice();

    public:
        ParcheesiGame() {}
        void startGame();
};

#endif // __PARCHEESIGAME__