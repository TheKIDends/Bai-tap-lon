#include "GameComponents.h"

void Button::setButton(int x, int y, int w, int h, string linkFolder) {
	buttonPosition_x	= x;
	buttonPosition_y	= y;
	buttonWidth			= w;
	buttonHeight		= h;
	linkFolderButton	= linkFolder;
}