#ifndef __ANIMATIONS__
#define __ANIMATIONS__

#include <iostream>

using namespace std;

class ArrowAnimations {
	private:
		int maxState, state;

	public:
		ArrowAnimations(int maxState) { this->maxState = maxState; }

		int getMaxState() { return maxState; }

		void nextState() { state = (state + 1) % maxState; }
		int  getState() { return state; }

		void finishAnimations() { state = 0; }
};

class ChessAnimations {
	private:
		bool animations;

		int idPosition;
		int endIdPosition;

		int maxState, state;

		int chess;

	public:
		ChessAnimations(int maxState) { animations = false; this->maxState = maxState; }

		int getMaxState() { return maxState; }

		void setChessAnimations(bool animations, int chess, int endIdPosition) {
			this->animations = animations;
			this->endIdPosition = endIdPosition;
			setChess(chess);
		}

		bool getAnimations() { return animations; }

		int getEndIdPosition() { return endIdPosition; }

		void setIdPosition(int idPosition) { this->idPosition = idPosition; }
		int  getIdPosition() { return idPosition; }

		void nextState() { state = (state + 1) % maxState; }
		int  getState() { return state; }
		
		void setChess(int chess) { this->chess = chess; }
		int  getChess() { return chess; }

		void finishAnimations() { animations = false; state = 0; }
};

class BackgroundAnimations {
	private:
		int maxState, state;

	public:
		BackgroundAnimations(int maxState) { this->maxState = maxState; }

		int getMaxState() { return maxState; }

		void nextState() { state = (state + 1) % maxState; }
		int  getState() { return state; }

		void finishChessAnimations() { state = 0; }
};

#endif // __ANIMATIONS__
