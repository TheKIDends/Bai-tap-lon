#ifndef __ANIMATIONS__
#define __ANIMATIONS__

#include "FPS.h"

#include <iostream>

using namespace std;

class Animations {
	private:
		
	protected:
		FPS fpsTime;

		bool animations;

		int maxStatus, status;

	public:
		Animations() { animations = false; status = 0; }

		int getMaxStatus() { return maxStatus; }

		bool getAnimations() { return animations; }
		void setAnimations(bool animations) { this->animations = animations; }

		int  getStatus() { return status; }
		void setStatus(int status) { this->status = status; }
		void nextStatus() { status = (status + 1) % maxStatus; }

		void finishAnimations() { animations = false; status = 0; }

		// FPS animations

		FPS* getFpsTime() { return &fpsTime; }

		void setFps(int time) {
			if (fpsTime.getTicks() > time) {
				nextStatus();
				fpsTime.start();
			}
		}
};

#endif // __ANIMATIONS__
