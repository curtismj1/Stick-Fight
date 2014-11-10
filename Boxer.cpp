#include "Boxer.h"

Boxer::Boxer() : Figure() {

}

void Boxer::setCollisionBox() {
	edge.left = -getWidth() / 2;
	edge.right = getWidth() / 2;
	edge.top = -getHeight() / 2;
	edge.bottom = (getHeight() / 2) - 20;
}

void Boxer::animate(float frameTime) {
	if (isWalking) {
		setFrameDelay(0.1);
		setFrames(0, 5);
		flipHorizontal(!facingRight);
	} else {
		setFrameDelay(0.2);
		setFrames(6, 11);
		flipHorizontal(!facingRight);
	}
}