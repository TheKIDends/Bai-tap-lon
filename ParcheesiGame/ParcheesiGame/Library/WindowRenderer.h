#ifndef __WINDOWRENDERER__
#define __WINDOWRENDERER__

#include "Painter.h"
#include "GameComponents.h"

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

		void loadBackGround(string linkImgBackGround);

		void loadButton(Button* button);

		void loadChess(int chessPosition_x, int chessPosition_y, Chess chess);

		void loadAvatar(Player* player);

		void loadChessBoard(int numLayer);

		void displayImage();
};

#endif // __WINDOWRENDERER__