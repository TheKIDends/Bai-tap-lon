#ifndef __ANIMATIONS__
#define __ANIMATIONS__

#include <iostream>

using namespace std;

class ChessAnimations {
	private:

		// Chess
		bool animationsChess;

		int idPositionChess;
		int endIdPositionChess;

		int maxStateChess, stateChess;

		int chess;

		// Arrow
		bool animationsArrow;

		int maxStateArrow, stateArrow;

	public:
		ChessAnimations();
		ChessAnimations(int maxStateChess, int maxStateArrow);

		// Chess
		int getMaxStateChess() { return maxStateChess; }

		void setChessAnimations(bool animationsChess, int chess, int endIdPositionChess) {
			this->animationsChess = animationsChess;
			this->endIdPositionChess = endIdPositionChess;
			setChess(chess);
		}

		bool getAnimationsChess() { return animationsChess; }

		int getEndIdPositionChess() { return endIdPositionChess; }

		void setIdPositionChess(int idPositionChess) { this->idPositionChess = idPositionChess; }
		int  getIdPositionChess() { return idPositionChess; }

		void nextStateChess() { stateChess = (stateChess + 1) % maxStateChess; }
		int  getStateChess() { return stateChess; }
		
		void setChess(int chess) { this->chess = chess; }
		int  getChess() { return chess; }

		void finishAnimationsChess() { animationsChess = false; stateChess = 0; }

		// Arrow
		int getMaxStateArrow() { return maxStateArrow; }

		void setArrowAnimations(bool animationsArrow) { this->animationsArrow = animationsArrow; }

		bool getAnimationsArrow() { return animationsArrow; }

		void nextStateArrow() { stateArrow = (stateArrow + 1) % maxStateArrow; }
		int  getStateArrow() { return stateArrow; }

		void finishAnimationsArrow() { animationsArrow = false; stateArrow = 0; }
};

class BackgroundAnimations {
	private:
		int maxState, state;

	public:
		BackgroundAnimations() { maxState = 2; }
		BackgroundAnimations(int maxState) { this->maxState = maxState; }

		int getMaxState() { return maxState; }

		void nextState() { state = (state + 1) % maxState; }
		int  getState() { return state; }

		void finishChessAnimations() { state = 0; }
};

#endif // __ANIMATIONS__
