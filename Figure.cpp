#include "Figure.h"
#include "StickFight.h"

const float maxHorizontalSpeed = 2.0;

Figure::Figure() {
	collisionType = entityNS::CIRCLE;
	onGround = false;
	facingRight = true;
}

bool Figure::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	hitbox.initialize(gamePtr, width, height, ncols, textureM);
	hitbox.setScale(10);
	return Entity::initialize(gamePtr, width, height, ncols, textureM);
}

void Figure::readInput() {
	if (input->isKeyDown(VK_LEFT) && velocity.x > -maxHorizontalSpeed) {
		velocity.x += -0.2;
		facingRight = false;
	}
	if (input->isKeyDown(VK_RIGHT) && velocity.x < maxHorizontalSpeed) {
		velocity.x += 0.2;
		facingRight = true;
	}
	if (input->isKeyDown(VK_UP) && onGround) {
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