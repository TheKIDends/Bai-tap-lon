#ifndef __WINDOWRENDERER__
#define __WINDOWRENDERER__

#include "Painter.h"
#include "GameComponents.h"
#include "Animations.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "FPS.h"

using namespace std;

class WindowRenderer {
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;

		Painter* painter;

		SDL_Texture* texture;

		void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);

		void deleteTexture() { SDL_DestroyTexture(texture); texture = NULL; }

	public:
		void createWindow(int screenWidth, int screenHeight, string windowTitle);

		void deleteWindow();

		// renderer Image

		void rendererButton(Button* button);

		void rendererArrow(int position_x, int position_y, Arrow* arrow);

		void rendererChess(int chessPosition_x, int chessPosition_y, Chess* chess);

		void rendererAvatar(Player player);

		void rendererChessboard(Chessboard chessboard);

		void rendererBackground(Background* background);

		void rendererDice(Dice dice);
		
		void rendererDiceAnimations(Dice dice, int status);

		void rendererBackDice(BackDice backDice, int idPlayer);

		void rendererMenuBoard(MenuBoard* menuBoard);
	
		void rendererAlert(Board* board);

		void rendererMouse(Mouse* mouse);

		void displayImage();

		// Renderer texture
		template <class obj>
		void loadTexture(obj* object) {
			object->loadTexture(renderer, object->getPathImg());
		}
};

#endif // __WINDOWRENDERER__