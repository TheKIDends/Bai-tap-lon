#ifndef __GAMECOMPONENTS__
#define __GAMECOMPONENTS__

#include "Painter.h"
#include "Utils.h"

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
};

class Button : public Painter {
	private:
		CLICK status;

	public:
		Button() { status = NORMAL; }

		CLICK getStatus() { return status; }
		void  setStatus(CLICK status) { this->status = status; }
};

class BackDice : public Painter {
	private:

	public:
		BackDice() {}
};

class Dice : public Painter {
	private:
		int numDice;

	public:
		Dice() {}
		int  getNumDice() { return numDice; }
		void setNumDice(int numDice) { this->numDice = numDice; }
		void rollDice() { numDice = Random::random(3, 6); }
};

class Arrow : public Painter {
	private:
		int dice;

	public:
		Arrow() {}
		int  getDice() { return dice; }
		void rollDice() { dice = Random::random(3, 6); }
};

class Chess : public Painter {
	private:
		int startId;
		int idPosition;
		bool canMoveChess;

		DIRECTION direction;

	public:
		Chess() { canMoveChess = false; direction = RIGHT; }

		void setDirection(DIRECTION direction) { this->direction = direction;  }
		DIRECTION getDirection() { return direction;  }

		int  getStartId() { return startId; }
		void setStartId(int startId) { this->startId = startId; this->idPosition = startId; }

		int  getIdPosition() { return idPosition; }
		void setIdPosition(int idPosition) { this->idPosition = idPosition; }

		bool getCanMoveChess() { return canMoveChess; }
		void setCanMoveChess(bool canMoveChess) { this->canMoveChess = canMoveChess; }
};

class Player : public Painter {
	private:
		bool playerWin = false;
		Chess chess[4];

	public:
		Player() {}

		void setWinner() { playerWin = true; }
		bool getWinner() { return playerWin; }

		// Avatar
		void setAvatarPlayer(SDL_Rect rect, SDL_Rect clip, string pathImg);

		// chess
		void setAllChessPlayer(SDL_Rect rect, SDL_Rect clip, string pathImg);

		void setDirectionChess(int idChess, DIRECTION direction) { chess[idChess].setDirection(direction); }

		int  getIdPositionChess(int idChess) { return chess[idChess].getIdPosition(); }
		void setIdPositionChess(int idChess, int idPosition) { chess[idChess].setIdPosition(idPosition); }

		int  getStartIdChess(int idChess) { return chess[idChess].getStartId(); }
		void setStartIdChess(int idChess, int startId) { chess[idChess].setStartId(startId); }

		void setPathImgChess(int idChess, string pathImg) { chess[idChess].setPathImg(pathImg); }

		bool getCanMoveChess(int idChess) { return chess[idChess].getCanMoveChess(); }
		void setCanMoveChess(int idChess, bool canMoveChess) { chess[idChess].setCanMoveChess(canMoveChess); }

		Chess  getChess(int idChess) { return chess[idChess]; }
		Chess* getChessIterator(int idChess) { return &chess[idChess]; }
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

class Background : public Painter {
	private:
		int numLayers;
		int layer;

	public:
		Background() { layer = 0; }
		Background(int numLayers) { layer = 0; this->numLayers = numLayers; }

		int  getNumLayers() { return numLayers; }
		void setNumLayers(int numLayers) { this->numLayers = numLayers; }

		int  getLayer() { return layer; }
		void setLayer(int layer) { this->layer = layer; }
		void nextLayer() { layer = (layer + 1) % numLayers; }
};

class MouseEvents {
	private:
		int mousePosition_x;
		int mousePosition_y;

		void setPosition(int x, int y);

	public:
		MouseEvents() {}
		void mouseHandleEvent();
		CLICK CheckMouseInRect(SDL_Rect rect);
		CLICK CheckMouseInChess(int chessPosition_x, int chessPosition_y, Chess* chess);
		CLICK CheckMouseInButton(Button button);
		CLICK CheckMouseInDice(Dice dice);
};

#endif // __GAMECOMPONENTS__