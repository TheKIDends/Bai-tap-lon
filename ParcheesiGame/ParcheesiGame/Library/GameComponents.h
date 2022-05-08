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

class Button : public Painter {
	private:
		CLICK status;

	public:
		Button() { status = NORMAL; }

		void setStatus(CLICK status) { this->status = status; }
		CLICK getStatus() { return status; }
};

class Dice : public Painter {
	private:
		int dice;

	public:
		Dice() {}
		int getDice() { return dice; }
		void rollDice() { dice = Random::random(3, 6); }
};

class Chess : public Painter {
	private:
		bool canMoveChess = false;
		int idPositionChess;

	public:
		Chess() {}
		void setIdPositionChess(int idPositionChess) { this->idPositionChess = idPositionChess; }
		int  getIdPositionChess() { return idPositionChess; }

		void setCanMoveChess(bool canMoveChess) { this->canMoveChess = canMoveChess; }
		bool getCanMoveChess() { return canMoveChess; }
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

		void setIdPositionChess(int idChess, int idPositionChess) { chess[idChess].setIdPositionChess(idPositionChess); }

		void setPathImgChess(int idChess, string pathImg) { chess[idChess].setPathImg(pathImg); }

		void setCanMoveChess(int idChess, bool canMoveChess) { chess[idChess].setCanMoveChess(canMoveChess); }
		bool getCanMoveChess(int idChess) { return chess[idChess].getCanMoveChess(); }

		Chess getChess(int id) { return chess[id]; }
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
		CLICK CheckMouseInChess(int chessPosition_x, int chessPosition_y, Chess chess);
		CLICK CheckMouseInButton(Button button);
};

#endif // __GAMECOMPONENTS__