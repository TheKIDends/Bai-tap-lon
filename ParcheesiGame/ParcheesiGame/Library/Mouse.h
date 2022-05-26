#ifndef __MOUSE__
#define __MOUSE__

#include "Painter.h"
#include "GameComponents.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

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


#endif // __MOUSE__
