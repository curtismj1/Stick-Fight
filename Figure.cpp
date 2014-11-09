#include "Figure.h"
#include "StickFight.h"

const float maxHorizontalSpeed = 2.0;

Figure::Figure() {
	collisionType = entityNS::BOX;
	onGround = false;
	facingRight = true;
}

bool Figure::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	hitbox.initialize(gamePtr, 0, 0, 0, textureM + 1);
	hitbox.setScale(10);
	bool r = Entity::initialize(gamePtr, width, height, ncols, textureM);
	return r;
}

void Figure::readInput() {
	isWalking = false;
	if (GetAsyncKeyState('A') && velocity.x > -maxHorizontalSpeed) {
		velocity.x += -0.2;
		facingRight = false;
		isWalking = true;
	}
	if (GetAsyncKeyState('D') && velocity.x < maxHorizontalSpeed) {
		velocity.x += 0.2;
		facingRight = true;
		isWalking = true;
	}
	if (GetAsyncKeyState('W') && onGround) {
		velocity.y = -5;
		onGround = false;
	}

	if (input->isKeyDown(VK_SPACE)) {
		isAttacking = true;
		if (facingRight) {
			hitbox.setX(spriteData.x + spriteData.width * spriteData.scale);
			hitbox.setY(spriteData.y + spriteData.height * spriteData.scale / 2);
		} else {
			hitbox.setX(spriteData.x - hitbox.getWidth() * hitbox.getScale());
			hitbox.setY(spriteData.y + spriteData.height * spriteData.scale / 2);
		}

	} else isAttacking = false;

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