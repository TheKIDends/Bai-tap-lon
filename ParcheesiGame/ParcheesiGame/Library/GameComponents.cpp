#include "GameComponents.h"

void Button::setButton(SDL_Rect size, int clipWidth, int clipHeight, string linkImg) {
	clipWidthButton		= clipWidth;
	clipHeightButton	= clipHeight;
	sizeButton			= size;
	linkImgButton		= linkImg;
}