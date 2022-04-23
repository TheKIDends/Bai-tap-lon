#ifndef __GAMECOMPONENTS__
#define __GAMECOMPONENTS__

#include "Utils.h"

#include <iostream>
#include <SDL.h>

using namespace std;

class Button {
	private:
		bool typeButton;

		int clipWidthButton, clipHeightButton;

		string pathImgButton;

		SDL_Rect sizeButton;

	public:
		Button() { typeButton = false;  }

		void setButton(SDL_Rect sizeButton, int clipWidthButton, int clipHeightButton, string pathImgButton);

		void setTypeButton(bool typeButton) { this->typeButton = typeButton; }

		int getTypeButton() { return typeButton; }

		SDL_Rect getSizeButton()	{ return sizeButton; }

		string getPathImgButton()	{ return pathImgButton; }

		int getClipWidthButton()	{ return clipWidthButton; }
		
		int getClipHeightButton()	{ return clipHeightButton; }

};

class Dice {
	private:
		int dice;

	public:
		int getDice() { return dice; }

		void rollDice() { dice = Random::random(3, 6); }
};

class Chess {
	private:
		bool canMoveChess;

		int idPositionChess;

		int widthChess, heightChess;

		string pathImgChess;

		SDL_Rect clipChess;

	public:
		Chess() { canMoveChess = false; }

		void setIdPositionChess(int idPositionChess) { this->idPositionChess = idPositionChess;  }
		int  getIdPositionChess() { return idPositionChess; }

		void setCanMoveChess(bool canMoveChess) { this->canMoveChess = canMoveChess; }
		bool getCanMoveChess() { return canMoveChess; }
		
		void setChess(int widthChess, int heightChess, SDL_Rect clipChess, string pathImgChess);
		int getWidthChess()			{ return widthChess; }
		int getHeightChess()		{ return heightChess; }
		SDL_Rect getClipChess()		{ return clipChess; }
		string getPathImgChess()	{ return pathImgChess; }
};

class Player {
	private:
		bool playerWin;

		int clipWidthAvatar, clipHeightAvatar;

		string pathImgAvatar;

		SDL_Rect sizeAvatar;

		Chess chess[4];

	public:
		Player() { playerWin = false; }

		void setWinner() { playerWin = true; }

		bool getWinner() { return playerWin; }
		
		void setAllChessPlayer(int widthChess, int heightChess, SDL_Rect clipChess, string pathImgChess);

		void setAvatarPlayer(SDL_Rect sizeAvatar, int clipWidthAvatar, int clipHeightAvatar, string pathImgAvatar);
		
		void setIdPositionChess(int id, int idPositionChess) { chess[id].setIdPositionChess(idPositionChess); }

		void setCanMoveChess(int id, bool canMoveChess) { chess[id].setCanMoveChess(canMoveChess); }
		bool getCanMoveChess(int id) { return chess[id].getCanMoveChess(); }

		int getClipWidthAvatar()	{ return clipWidthAvatar; }

		int getClipHeightAvatar()	{ return clipHeightAvatar; }

		string getPathImgAvatar()	{ return pathImgAvatar; }

		SDL_Rect getSizeAvatar()	{ return sizeAvatar; }

		Chess getChess(int id)		{ return chess[id]; }
};

class MouseEvents {
	private:
		int mousePosition_x;
		int mousePosition_y;

		void setPosition(int x, int y);

	public:
		void mouseHandleEvent();

		bool CheckMouseInRect(SDL_Rect rect);

		bool CheckMouseInChess(int chessPosition_x, int chessPosition_y, Chess chess);

		bool CheckMouseInButton(Button* button);
};

#endif // __GAMECOMPONENTS__