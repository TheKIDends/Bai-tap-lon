#ifndef __ANIMATIONS__
#define __ANIMATIONS__

#include <iostream>

using namespace std;

class ChessAnimations {
	private:
		bool animations;

		int idPositionChess;
		int endIdPositionChess;

		int maxState, state;

		int chess;

	public:
		ChessAnimations() { animations = false; maxState = 4; }
		ChessAnimations(int maxState) { animations = false; this->maxState = maxState; }

		int getMaxState() { return maxState; }

		void setChessAnimations(bool animations, int chess, int endIdPositionChess) {
			this->animations = animations;
			this->endIdPositionChess = endIdPositionChess;
			setChess(chess);
		}

		bool getAnimations() { return animations; }

		int getEndIdPositionChess() { return endIdPositionChess; }

		void setIdPositionChess(int idPositionChess) { this->idPositionChess = idPositionChess; }
		int  getIdPositionChess() { return idPositionChess; }

		void nextState() { state = (state + 1) % maxState; }
		int  getState() { return state; }
		
		void setChess(int chess) { this->chess = chess; }
		int  getChess() { return chess; }

		void finishChessAnimations() { animations = false; state = 0; }
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

class ArrowChooseChessAnimations {
	private:
		bool animations;

		int idPositionChess;
		int endIdPositionChess;

		int maxState, state;

		int chess;

	public:
		ArrowChooseChessAnimations() { animations = false; maxState = 4; }
		ArrowChooseChessAnimations(int maxState) { animations = false; this->maxState = maxState; }

		int getMaxState() { return maxState; }

		void setChessAnimations(bool animations, int chess, int endIdPositionChess) {
			this->animations = animations;
			this->endIdPositionChess = endIdPositionChess;
			setChess(chess);
		}

		bool getAnimations() { return animations; }

		int getEndIdPositionChess() { return endIdPositionChess; }

		void setIdPositionChess(int idPositionChess) { this->idPositionChess = idPositionChess; }
		int  getIdPositionChess() { return idPositionChess; }

		void nextState() { state = (state + 1) % maxState; }
		int  getState() { return state; }

		void setChess(int chess) { this->chess = chess; }
		int  getChess() { return chess; }

		void finishChessAnimations() { animations = false; state = 0; }
};

#endif // __ANIMATIONS__
