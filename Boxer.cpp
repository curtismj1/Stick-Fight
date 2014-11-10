#include "Boxer.h"

Boxer::Boxer() : Figure() {

}

void Boxer::setCollisionBox() {
	edge.left = -90 / 2;
	edge.right = 90 / 2;
	edge.top = -200 / 2;
	edge.bottom = (200 / 2) - 60;
}

void Boxer::animate(float frameTime) {
	if (isAttacking) {
		setFrameDelay(0.05);
		setFrames(12, 23);
		if (currentFrame == endFrame) isAttacking = false;
		else return;
	}
	if (isWalking) {
		setFrameDelay(0.1);
		setFrames(6, 11);
		flipHorizontal(!facingRight);
	} else {
		setFrameDelay(0.075);
		setFrames(0, 5);
		flipHorizontal(!facingRight);
	}
}

void Boxer::soundHit(Audio* a) {
	a->playCue(PUNCH_HIT);
}

void Boxer::soundMiss(Audio* a) {
	a->playCue(PUNCH_MISS);
}

void Boxer::setHealth(float h) { health = h; }