#include "Animations.h"

ChessAnimations::ChessAnimations() {
	animationsChess = false;
	animationsArrow = false;

	maxStateChess = 4;
	maxStateArrow = 2;
}

ChessAnimations::ChessAnimations(int maxStateChess, int maxStateArrow) {
	animationsChess = false;
	animationsArrow = false;

	this->maxStateChess = maxStateChess;
	this->maxStateArrow = maxStateChess;
}