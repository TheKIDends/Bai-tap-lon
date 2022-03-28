#ifndef __GAMECOMPONENTS__
#define __GAMECOMPONENTS__

#include <iostream>

using namespace std;

class Button {
	private:
		int buttonPosition_x;
		int buttonPosition_y;
		int buttonWidth;
		int buttonHeight;
		string linkFolderButton;
		
	public:
		void setButton(int x, int y, int w, int h, string linkFolder);

		int getButtonPosition_x()	 { return buttonPosition_x; }

		int getButtonPosition_y()	 { return buttonPosition_y; }

		int getButtonWidth()		 { return buttonWidth; }

		int getButtonHeight()		 { return buttonHeight; }

		string getLinkFolderButton() { return linkFolderButton;  }
};

class Dice {
	private:


	public:

};

#endif // __GAMECOMPONENTS__