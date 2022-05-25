#ifndef __GAMECOMPONENTS__
#define __GAMECOMPONENTS__

#include "Animations.h"
#include "Painter.h"
#include "Utils.h"
#include "FPS.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

enum CLICK {
	NORMAL,
	ON_CLICK,
};

enum DIRECTION {
	LEFT,
	RIGHT,
	UP, 
	DOWN,
};

enum BUTTON {
	EXIT_MENU,
	HOME_BUTTON,
	RESTART_BUTTON,
	SAVE_BUTTON,
	ABOUT_BUTTON,
	MUSIC_BUTTON,
	SOUND_BUTTON,
};

enum BOARD {
	RETURN_HOME,
	RESTART_GAME,
	SAVE_GAME,
};

class Image : public Painter, public Animations {
	private:

	public:
		Image() {}
		Image(int maxStatus) { this->maxStatus = maxStatus; }
};

class Button : public Painter {
	private:
		CLICK status;

	public:
		Button() { status = NORMAL; }

		CLICK getStatus() { return status; }
		void  setStatus(CLICK status) { this->status = status; }
};

class Dice : public Painter, public Animations {
	private:
		int numDice;

	public:
		Dice() {}
		Dice(int maxStatus) { this->maxStatus = maxStatus; }

		int  getNumDice() { return numDice; }
		void rollDice() { numDice = Random::random(1, 6); }
		void setNumDice(int numDice) { this->numDice = numDice; }
};

class Arrow : public Painter, public Animations {
	private:
		int distance;
		DIRECTION direction;

	public:
		Arrow() { direction = UP; maxStatus = 2; }

		void setArrow(int distance, DIRECTION direction, SDL_Rect rect, SDL_Rect clip, string pathImg) {
			this->distance  = distance;
			this->direction = direction;
			setObject(rect, clip, pathImg);
		}

		int  getDistance() { return distance; }
		void setDistance(int distance) { this-> distance = distance; }

		DIRECTION getDirection() { return direction; }
		void setDirection(DIRECTION direction) { this->direction = direction; }
};

class Chess : public Painter, public Animations {
	private:
		int stepsTaken;
		int startId;
		int idPosition;
		bool canMoveChess;
		DIRECTION direction;
		int endIdPosition;

	public:
		Chess() { stepsTaken = 0; maxStatus = 3; status = 0; canMoveChess = false; direction = RIGHT; }

		void setDirection(DIRECTION direction) { this->direction = direction;  }
		DIRECTION getDirection() { return direction;  }

		int  getStartId() { return startId; }
		void setStartId(int startId) { this->startId = startId; this->idPosition = startId; }

		int  getIdPosition() { return idPosition; }
		void setIdPosition(int idPosition) { this->idPosition = idPosition; }

		bool getCanMoveChess() { return canMoveChess; }
		void setCanMoveChess(bool canMoveChess) { this->canMoveChess = canMoveChess; }

		int  getStepsTaken() { return stepsTaken; }
		void setStepsTaken(int stepsTaken) { this->stepsTaken = stepsTaken; }

		// Animations
		void setChessAnimations(bool animations, int endIdPosition) {
			this->animations = animations;
			this->endIdPosition = endIdPosition;
		}

		int  getEndIdPosition() { return endIdPosition; }
		void setEndIdPosition(int endIdPosition) { this->endIdPosition = endIdPosition; }
};

class Player : public Painter {
	private:
		bool playerWin;
		Chess chess[4];

	public:
		Player() { playerWin = false; }

		void setWinner(bool playerWin) { this->playerWin = playerWin; }
		bool getWinner() { return playerWin; }

		// Avatar
		void setAvatarPlayer(SDL_Rect rect, SDL_Rect clip, string pathImg);

		// chess
		void setAllChessPlayer(SDL_Rect rect, SDL_Rect clip, string pathImg);

		void setDirectionChess(int idChess, DIRECTION direction) { chess[idChess].setDirection(direction); }

		void setPathImgChess(int idChess, string pathImg) { chess[idChess].setPathImg(pathImg); }

		bool getCanMoveChess(int idChess) { return chess[idChess].getCanMoveChess(); }
		void setCanMoveChess(int idChess, bool canMoveChess) { chess[idChess].setCanMoveChess(canMoveChess); }

		Chess  getChess(int idChess) { return chess[idChess]; }
		Chess* getChess_It(int idChess) { return &chess[idChess]; }
};

class Chessboard : public Painter {
	private:
		int numLayers;
		int layer;

	public:
		Chessboard() { layer = 0; }
		Chessboard(int numLayers) { layer = 0; this->numLayers = numLayers; }

		int  getNumLayers() { return numLayers; }
		void setNumLayers(int numLayers) { this->numLayers = numLayers; }

		int  getLayer() { return layer; }
		void setLayer(int layer) { this->layer = layer; }
};

class Background : public Painter, public Animations {
	private:

	public:
		Background() { }
		Background(int maxStatus) { this->maxStatus = maxStatus; }
};

class Notification : public Painter, public Animations {
	private:
	public:
		Notification() {}
		Notification(int maxStatus) { this->maxStatus = maxStatus; }
};

class Board : public Painter {
	private:
		Button yes, no, ok;

	public:
		Board() {}

		Button* getButtonYes_It() { return &yes; }
		Button  getButtonYes() { return yes; }

		Button* getButtonNo_It() { return &no; }
		Button  getButtonNo() { return no; }

		Button* getButtonOk_It() { return &ok; }
		Button  getButtonOk() { return ok; }

};

class MenuBoard : public Painter {
	private:
		Background shadow = Background(1);

		Board returnHome;
		Board restartGame;
		Board saveGame;

		Button exit;
		Button home;
		Button restart;
		Button save;
		Button about;
		Button music;
		Button sound;
	
	public:
		MenuBoard() {}

		Background* getBackground_It() { return &shadow; }
		Background  getBackground() { return shadow; }

		Board* getBoard_It(BOARD nameBoard);
		Board  getBoard(BOARD nameBoard);

		Button* getButton_It(BUTTON nameButton);
		Button  getButton(BUTTON nameButton);
};

class Mouse : public Painter {
	private:
		int position_x;
		int position_y;

		void setPosition(int x, int y);

	public:
		Mouse() {}
		void mouseHandleEvent();

		int getPosition_x() { return position_x; }
		int getPosition_y() { return position_y; }

		CLICK CheckMouseInRect(SDL_Rect rect);
		CLICK CheckMouseInChess(int chessPosition_x, int chessPosition_y, Chess* chess);
		CLICK CheckMouseInButton(Button button);
		CLICK CheckMouseInDice(Dice dice);
};

#endif // __GAMECOMPONENTS__ 