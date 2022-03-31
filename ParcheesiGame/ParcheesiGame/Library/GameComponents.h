#ifndef __GAMECOMPONENTS__
#define __GAMECOMPONENTS__

#include <iostream>
#include <SDL.h>

using namespace std;

class Button {
	private:
		int clipWidthButton, clipHeightButton;

		string linkImgButton;

		SDL_Rect sizeButton;

	public:
		void setButton(SDL_Rect size, int clipWidth, int clipHeight, string linkImg);

		SDL_Rect getSizeButton()	{ return sizeButton; }

		string getLinkImgButton()	{ return linkImgButton;  }

		int getClipWidthButton()	{ return clipWidthButton; }
		
		int getClipHeightButton()	{ return clipHeightButton; }
};

class Dice {
	private:


	public:

};

class Player {
	private:


	public:
};

#endif // __GAMECOMPONENTS__