#ifndef __PARCHEESIGAME__
#define __PARCHEESIGAME__

#include "FPS.h"
#include "CommonFunction.h"
#include "GameComponents.h"
#include "WindowRenderer.h"
#include "Animations.h"

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <exception>

using namespace std;

enum DISPLAY {
    HOME,
    PLAYER_NUMBER_SELECTION,
    GAME,
    MENU,
    ALERT_RETURN_HOME,
    ALERT_RESTART_GAME,
    NOTI_SAVE_GAME,
    ABOUT,
};

enum STATUS_PLAYER {
    ROLL_DICE,
    CHOOSECHESS,
    ENDTURN,
};

class ParcheesiGame {
    private:
        DISPLAY display;
        STATUS_PLAYER statusPlayer;

        int numberPlayers = 4;
        int playerTurn;

        int idStartPosition[4];
        pair <int, int> mapChessboard[100];

        Mouse* mouse;

        Dice dice = Dice(6);
        Arrow arrow;
        Arrow clickToRoll;
        Background background = Background(2);
        Chessboard chessboard = Chessboard(7);

        BackDice backDice;
        Player player[4];

        MenuBoard menuBoard;

        Button openMenu;
        Button playButton;
        Button continueButton;
        Button exitButton;
        Button _2playersButton;
        Button _3playersButton;
        Button _4playersButton;
        Button backButton;

        void buildMap();
        void restartGame();
        void saveGame();

        void setGameComponents();
        void setMenuComponents();
        void setAlertComponents();

        bool checkIdChessInLayer(int idPositionChess, int layer);

        void displayHome();
        void displayPlayerNumberSelection();
        void displayGame();
        void displayMenu();
        void displayAlertBoard(BOARD nameAlert);
        void displaySaveGame();
        void displayAbout();

        void eventsHome();
        void eventsPlayerNumberSelection();
        void eventsGame();
        void eventsMenu();
        void eventsAlertBoard(BOARD nameAlert);
        void eventsSaveGame();
        void eventsAbout();

        bool canMove();
        bool checkIdInStartPosition(int idPosition);
        int  chessNextStep(int idPosition);
        int  idMoveForward(int idPosition);

        void animationMoveChess(Chess* chess);
        void animationRollDice();

    public:
        ParcheesiGame() {}
        void startGame();
};

#endif // __PARCHEESIGAME__