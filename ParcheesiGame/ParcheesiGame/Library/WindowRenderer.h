#ifndef __WINDOWRENDERER__
#define __WINDOWRENDERER__

#include "Painter.h"
#include "GameComponents.h"
#include "Animations.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

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

		// Load Image

		void loadButton(Button button);

		void loadArrow(int position_x, int position_y);

		void loadChess(int chessPosition_x, int chessPosition_y, Chess chess, int statusChess);

		void loadAvatar(Player player);

		void loadChessboard(Chessboard chessboard);

		void loadBackground(Background background);

		void loadDice(Dice dice);
		
		void loadDiceAnimations(Dice dice, int status);

		void loadBackDice(BackDice backDice, int idPlayer);
	
		void displayImage();

		// Renderer texture
		template <class obj>
		void rendererTexture(obj* object) {
			object->loadTexture(renderer, object->getPathImg());
		}
};

#endif // __WINDOWRENDERER__