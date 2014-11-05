#include "Figure.h"
#include "StickFight.h"

const float maxHorizontalSpeed = 2.0;

Figure::Figure() {
	collisionType = entityNS::CIRCLE;
	onGround = false;
}

void Figure::readInput() {
	if (input->isKeyDown(VK_LEFT) && velocity.x > -maxHorizontalSpeed) velocity.x += -0.2;
	if (input->isKeyDown(VK_RIGHT) && velocity.x < maxHorizontalSpeed) velocity.x += 0.2;
	if (input->isKeyDown(VK_UP) && onGround) {
		velocity.y = -5;
		onGround = false;
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