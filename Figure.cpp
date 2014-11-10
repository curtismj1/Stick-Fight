#include "Figure.h"
#include "StickFight.h"

const float maxHorizontalSpeed = 1.0;
const float maxAIHorizontalSpeed = .75;

Figure::Figure() {
	collisionType = entityNS::BOX;
	onGround = false;
	facingRight = true;
	health = 100;
	invincible = 0;
	stunned = 0;
}

void Figure::damage(int d) {
	health -= d; 
	if (health < 0) 
		health = 0;
	invincible = 10;
}

bool Figure::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	hitbox.initialize(gamePtr, 0, 0, 0, textureM + 1);
	hitbox.setScale(10);
	bool r = Entity::initialize(gamePtr, width, height, ncols, textureM);
	setCollisionBox();
	return r;
}

void Figure::setCollisionBox() {
	edge.left = -getWidth() / 2;
	edge.right = getWidth() / 2;
	edge.top = -getHeight() / 2;
	edge.bottom = getHeight() / 2;
}

void Figure::readInput() {
	if (stunned > 0) {
		stunned--;
		return;
	}
	isWalking = false;
	if (input->isKeyDown(VK_LEFT) && velocity.x > -maxHorizontalSpeed) {
		velocity.x += -0.2;
		facingRight = false;
		isWalking = true;
	}
	if (input->isKeyDown(VK_RIGHT) && velocity.x < maxHorizontalSpeed) {
		velocity.x += 0.2;
		facingRight = true;
		isWalking = true;
	}
	if (input->isKeyDown(VK_UP) && onGround) {
		velocity.y = -4;
		onGround = false;
	}

	if (input->isKeyDown(VK_SPACE)) {
		isAttacking = true;
		if (facingRight) {
			hitbox.setX(spriteData.x + spriteData.width * spriteData.scaleX);
			hitbox.setY(spriteData.y + spriteData.height * spriteData.scaleY / 2);
		} else {
			hitbox.setX(spriteData.x - hitbox.getWidth() * hitbox.getScaleX());
			hitbox.setY(spriteData.y + spriteData.height * spriteData.scaleY / 2);
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

	if (invincible > 0) invincible--;
	animate(frameTime);
}

void Figure::collisions(Entity* walls, int nWalls) {
	VECTOR2 collisionVector;
	onGround = false;
	for(int i = 0; i < nWalls; i++)
		if (collidesWith(walls[i], collisionVector)) {
			velocity.y = 0;
			onGround = true;
		}

	if (getX() < 0) {
		velocity.x *= -1;
		spriteData.x = 0;
	}
}

void Figure::Ai(Figure* enemy) {
	if (stunned > 0)  {
		stunned--;
		return;
	}
	isWalking = false;
	if (enemy->getX() > getX()) {
		if(abs(enemy->getX() - getX()) < 200) {
			if (abs(enemy->getX() - getX()) > 190)
				return;
			if (velocity.x > -maxAIHorizontalSpeed / 2){
				velocity.x += -0.2;
				return;
			}
		} else {
			if (velocity.x < maxAIHorizontalSpeed){
				velocity.x += 0.2;
			}
		}
		isWalking = true;
		facingRight = true;
	} else if(enemy->getX() < getX()){
		if(abs(enemy->getX() - getX()) > 200) {
			if (abs(enemy->getX() - getX()) < 190)
				return;
			if (velocity.x < maxAIHorizontalSpeed / 2){
				velocity.x += 0.2;
				return;
			}
		} else {
			if (velocity.x > -maxAIHorizontalSpeed){
				velocity.x += -0.2;
			}
		}
		isWalking = true;
		facingRight = false;
	}
}