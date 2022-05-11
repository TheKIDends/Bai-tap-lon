#ifndef __ANIMATIONS__
#define __ANIMATIONS__

#include "GameComponents.h"

#include <iostream>
#include <vector>

using namespace std;

class ArrowAnimations {
	private:
		int maxStatus, status;

	public:
		ArrowAnimations(int maxStatus) { this->maxStatus = maxStatus; }

		int getMaxStatus() { return maxStatus; }

		void nextStatus() { status = (status + 1) % maxStatus; }
		int  getStatus() { return status; }

		void finishAnimations() { status = 0; }
};

class ChessAnimations {
	private:
		bool animations;

		int idPosition;
		int endIdPosition;

		int maxStatus, status;

		int chess;

	public:
		ChessAnimations() { animations = false; }
		ChessAnimations(int maxStatus) { animations = false; this->maxStatus = maxStatus; }

		int getMaxStatus() { return maxStatus; }

		void setChessAnimations(bool animations, int chess, int endIdPosition) {
			this->animations = animations;
			this->endIdPosition = endIdPosition;
			setChess(chess);
		}

		bool getAnimations() { return animations; }

		int getEndIdPosition() { return endIdPosition; }

		void setIdPosition(int idPosition) { this->idPosition = idPosition; }
		int  getIdPosition() { return idPosition; }

		void nextStatus() { status = (status + 1) % maxStatus; }
		int  getStatus() { return status; }
		
		void setChess(int chess) { this->chess = chess; }
		int  getChess() { return chess; }

		void finishAnimations() { animations = false; status = 0; }
};

class DiceAnimations {
	private:
		bool animations;

		int maxStatus, status;

	public:
		DiceAnimations() { animations = false; }
		DiceAnimations(int maxStatus) { animations = false; this->maxStatus = maxStatus; }

		int getMaxStatus() { return maxStatus; }

		void setDiceAnimations(bool animations) {
			this->animations = animations;
		}

		bool getAnimations() { return animations; }

		void nextStatus() { status = (status + 1) % maxStatus; }
		int  getStatus() { return status; }

		void finishAnimations() { animations = false; status = 0; }
};

#endif // __ANIMATIONS__
