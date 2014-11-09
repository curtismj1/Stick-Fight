#include "SwordGuy.h"

SwordGuy::SwordGuy() : Figure() {

}

void SwordGuy::setCollisionBox() {
	edge.left = -getWidth() / 2;
	edge.right = getWidth() / 2;
	edge.top = -getHeight() / 2;
	edge.bottom = (getHeight() / 2) - 20;
}

void SwordGuy::animate() {
	if (isWalking) {
		setFrameDelay(0.1);
		if (facingRight)
			setFrames(4, 7);
		else
			setFrames(12, 15);
	} else {
		setFrameDelay(0.5);
		if (facingRight)
			setFrames(0, 3);
		else
			setFrames(8, 11);
	}
}