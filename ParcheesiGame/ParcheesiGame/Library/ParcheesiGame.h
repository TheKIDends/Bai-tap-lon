#ifndef __PARCHEESIGAME__
#define __PARCHEESIGAME__

#include "FPS.h"
#include "CommonFunction.h"
#include "GameComponents.h"
#include "WindowRenderer.h"
#include "GameMap.h"
#include "Mouse.h"
#include "Animations.h"

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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
    RANKING,
};

enum STATUS_PLAYER {
    ROLL_DICE,
    CHOOSECHESS,
    ENDTURN,
};

class ParcheesiGame : public GameMap {
    private:
        DISPLAY display;
        STATUS_PLAYER statusPlayer;

        bool animations;
        int playerTurn;
        int numberPlayers = MAX_PLAYERS;

        Player player[MAX_PLAYERS];

        string ordWinner;

        Dice dice = Dice(MAX_DICE);
        Arrow arrow;
        Arrow clickToRoll;
        Background background = Background(MAX_LAYERS_BACKGROUND);
        Chessboard chessboard = Chessboard(MAX_LAYERS_CHESSBOARD);

        Image title;
        Image leaderboard;
        Image canNotMove = Image(20);
        Image boom;
        Image backDice;
        Notification notiLoser = Notification(20);

        MenuBoard menuBoard;

        Button backHome;
        Button openMenu;
        Button playButton;
        Button continueButton;
        Button exitButton;
        Button _2playersButton;
        Button _3playersButton;
        Button _4playersButton;
        Button backButton;

        Mix_Chunk* player_win = NULL;
        Mix_Chunk* win = NULL;
        Mix_Chunk* loser = NULL;
        Mix_Chunk* ono = NULL;
        Mix_Chunk* rollDice = NULL;
        Mix_Chunk* kick = NULL;
        Mix_Chunk* jump = NULL;
        Mix_Chunk* click = NULL;
        Mix_Music* gMusic = NULL;

        void restartGame();
        void continueGame();
        void saveGame();
        void setWinner();
        void nextPlayer();

        void setAudioMixer();
        void setGameComponents();
        void setMenuComponents();
        void setBoardComponents();

        bool checkIdChessInLayer(int idPositionChess, int layer);

        void displayHome();
        void displayPlayerNumberSelection();
        void displayGame();
        void displayMenu();
        void displayAlertBoard(BOARD nameAlert);
        void displaySaveGame();
        void displayAbout();
        void displayRank();

        void setWindowHome();
        void setWindowPlayerNumberSelection();
        void setWindowGame();
        void setWindowMenu();

        void eventsHome();
        void eventsPlayerNumberSelection();
        void eventsGame();
        void eventsMenu();
        void eventsAlertBoard(BOARD nameAlert);
        void eventsSaveGame();
        void eventsAbout();
        void eventsRank();

        bool canMove();
        bool checkIdInStartPosition(int idPosition);
        int  chessNextStep(Chess* chess);
        int  idMoveForward(int idPosition, int turn);

        void checkEndGame();
        void showNotiCanNotMove();
        void animationMoveChess(Chess* chess);
        void animationRollDice();

    public:
        ParcheesiGame() {}
        void startGame();
};

#endif // __PARCHEESIGAME__