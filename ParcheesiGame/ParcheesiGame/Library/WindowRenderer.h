#ifndef __WINDOWRENDERER__
#define __WINDOWRENDERER__

#include "Painter.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class WindowRenderer {
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		
		Painter* painter;

		void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);

		void loadChessBoard();

	public:
		void createWindow(int screenWidth, int screenHeight, string windowTitle);

		void deleteWindow();

		void loadImage();
};

#endif // __WINDOWRENDERER__