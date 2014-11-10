#include "Boxer.h"

Boxer::Boxer() : Figure() {
	time = 0;
}

void Boxer::setCollisionBox() {
	edge.left = -getWidth() / 2;
	edge.right = getWidth() / 2;
	edge.top = -getHeight() / 2;
	edge.bottom = (getHeight() / 2) - 20;
}

void Boxer::jab(){
			setFrameDelay(0.05);
			setFrames(12,17);
			
}
void Boxer::cross(){
			setFrameDelay(0.15);
			setFrames(18,23);
			if(getCurrentFrame() == 23){
				time = 0;
			}
}
void Boxer::animate(float frameTime) {
	time += getFrameDelay();
	if (isWalking) {

		if(time>15){
			jab();

		}
		else{
		setFrameDelay(0.1);
		setFrames(6, 11);
		}
		flipHorizontal(!facingRight);
		
	} else {
		setFrameDelay(0.075);
		setFrames(0, 5);
		flipHorizontal(!facingRight);
	}
}