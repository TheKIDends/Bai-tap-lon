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

		string linkImgButton;

		SDL_Rect sizeButton;

	public:
		Button() { typeButton = false;  }

		void setButton(SDL_Rect sizeButton, int clipWidthButton, int clipHeightButton, string linkImgButton);

		void setTypeButton(bool typeButton) { this->typeButton = typeButton; }

		int getTypeButton() { return typeButton; }

		SDL_Rect getSizeButton()	{ return sizeButton; }

		string getLinkImgButton()	{ return linkImgButton; }

		int getClipWidthButton()	{ return clipWidthButton; }
		
		int getClipHeightButton()	{ return clipHeightButton; }

};

class Dice {
	private:
		int dice;

	public:
		int getDice() { return dice; }

		void rollDice() { dice = Random::random(1, 6); }
};

class Chess {
	private:
		int idPositionChess;

		int widthChess, heightChess;

		string linkImgChess;

		SDL_Rect clipChess;

	public:
		void setIdPositionChess(int idPositionChess) { this->idPositionChess = idPositionChess;  }

		void setChess(int widthChess, int heightChess, SDL_Rect clipChess, string linkImgChess);

		int getIdPositionChess()	{ return idPositionChess; }

		int getWidthChess()			{ return widthChess; }

		int getHeightChess()		{ return heightChess; }

		SDL_Rect getClipChess()		{ return clipChess; }

		string getLinkImgChess()	{ return linkImgChess; }
};

class Player {
	private:
		bool playerWin = false;

		int clipWidthAvatar, clipHeightAvatar;

		string linkImgAvatar;

		SDL_Rect sizeAvatar;

		Chess chess[4];

	public:
		void setWinner() { playerWin = true; }

		bool getWinner() { return playerWin; }
		
		void setAllChessPlayer(int widthChess, int heightChess, SDL_Rect clipChess, string linkImgChess);

		void setAvatarPlayer(SDL_Rect sizeAvatar, int clipWidthAvatar, int clipHeightAvatar, string linkImgAvatar);
		
		void setIdPositionChess(int id, int idPositionChess) { chess[id].setIdPositionChess(idPositionChess); }

		int getClipWidthAvatar()	{ return clipWidthAvatar;  };

		int getClipHeightAvatar()	{ return clipHeightAvatar;  };

		string getLinkImgAvatar()	{ return linkImgAvatar;  };

		SDL_Rect getSizeAvatar()	{ return sizeAvatar;  };

		Chess getChess(int id)		{ return chess[id]; };
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