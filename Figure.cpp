#include "Figure.h"
#include "StickFight.h"

const float maxHorizontalSpeed = 2.0;


namespace playerNS{
	float ANIMATION_DELAY = 0.2f;

}


Figure::Figure() {
	collisionType = entityNS::CIRCLE;
	lastFrame = 0;
	onGround = false;
	facingRight = true;
	key_down_last_frame = false;
}
int Figure::getLastFrame(){
	return lastFrame;
}
bool Figure::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	hitbox.initialize(gamePtr, width, height, ncols, textureM);
	hitbox.setScale(10);
	return Entity::initialize(gamePtr, width, height, ncols, textureM);
}

void Figure::readInput() {
	
	flipHorizontal(!facingRight);
	if (input->isKeyDown(VK_LEFT) && velocity.x > -maxHorizontalSpeed) {
		velocity.x += -0.2;
		facingRight = false;
		setFrames(0,5);
		setFrameDelay(0.05f);
		key_down_last_frame = true;
		
	}
	if (input->isKeyDown(VK_RIGHT) && velocity.x < maxHorizontalSpeed) {
		velocity.x += 0.2;
		facingRight = true;
		setFrames(0,5);
		setFrameDelay(0.05f);
		flipHorizontal(!facingRight);
		key_down_last_frame = true;
	}
	if (input->isKeyDown(VK_UP) && onGround) {
		velocity.y = -5;
		onGround = false;
		key_down_last_frame = true;
	}

	if (input->isKeyDown(VK_SPACE)) {
		key_down_last_frame = true;
		isAttacking = true;
		if (facingRight) {
			hitbox.setX(spriteData.x + spriteData.width * spriteData.scaleX);
			hitbox.setY(spriteData.y + spriteData.height * spriteData.scaleY / 2);
		} else {
			hitbox.setX(spriteData.x - hitbox.getWidth() * hitbox.getScaleX());
			hitbox.setY(spriteData.y + spriteData.height * spriteData.scaleY / 2);
		}

	} else{
		isAttacking = false;
	}
}

void Figure::update(float frameTime) {
	if (!onGround) deltaV.y = 0.1;

	if (velocity.x > 0) deltaV.x = -0.1;
	if (velocity.x < 0) deltaV.x = 0.1;
	if (velocity.x < 0.1 && velocity.x > -0.1) deltaV.x = -velocity.x;
	Entity::update(frameTime);

	spriteData.x += velocity.x;
	spriteData.y += velocity.y;
	
}

void Figure::collisions(Entity* walls, int nWalls) {
	VECTOR2 collisionVector;
	onGround = false;
	for(int i = 0; i < nWalls; i++)
		if (collidesWith(walls[i], collisionVector)) {
			velocity.y = 0;
			onGround = true;
		}
}