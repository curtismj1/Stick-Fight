#include "SwordGuy.h"

SwordGuy::SwordGuy() : Figure() {

}

void SwordGuy::setCollisionBox() {
	edge.left = -90 / 2;
	edge.right = 90 / 2;
	edge.top = -200 / 2;
	edge.bottom = (200 / 2);
}

void SwordGuy::animate(float frameTime) {
	if (isAttacking) {
		setFrameDelay(0.01);
		setFrames(8, 27);
		if (currentFrame == endFrame) isAttacking = false;
		else return;
	}
	if (isWalking) {
		setFrameDelay(0.1);
		setFrames(4, 7);
		flipHorizontal(!facingRight);
	} else {
		setFrameDelay(0.5);
		setFrames(0, 3);
		flipHorizontal(!facingRight);
	}
}