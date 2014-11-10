#include "Figure.h"
#include "StickFight.h"

const float maxHorizontalSpeed = 1.0;
const float maxAIHorizontalSpeed = .75;

Figure::Figure() {
	collisionType = entityNS::BOX;
	onGround = false;
	facingRight = true;
	isAttacking = false;
	health = 100;
	invincible = 0;
	stunned = 0;
	attackCounter = 0;
}

void Figure::damage(int d) {
	health -= d; 
	if (health < 0) 
		health = 0;
	invincible = 100;
}

bool Figure::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	hitbox.initialize(gamePtr, 0, 0, 0, textureM + 1);
	hitbox.setScaleX(70);
	hitbox.setScaleY(100);
	bool r = Entity::initialize(gamePtr, width, height, ncols, textureM);
	setCollisionBox();
	return r;
}

void Figure::readInput(bool p2) {
	if (stunned > 0) {
		stunned--;
		return;
	}
	if (isAttacking) return;
	isWalking = false;
	if (((input->isKeyDown(VK_LEFT) && !p2) || (input->isKeyDown(0x41) && p2)) && velocity.x > -maxHorizontalSpeed) {
		velocity.x += -0.2;
		facingRight = false;
		isWalking = true;
	}
	if (((input->isKeyDown(VK_RIGHT) && !p2) || (input->isKeyDown(0x44) && p2)) && velocity.x < maxHorizontalSpeed) {
		velocity.x += 0.2;
		facingRight = true;
		isWalking = true;
	}
	if (((input->isKeyDown(VK_UP) && !p2) || (input->isKeyDown(0x57) && p2)) && onGround) {
		velocity.y = -4;
		onGround = false;
	}

	if (((input->isKeyDown(VK_SPACE) && !p2) || (input->isKeyDown(VK_TAB) && p2))) {
		isAttacking = true;
		if (facingRight) {
			hitbox.setX(getCenterX());
		} else {
			hitbox.setX(getCenterX() - hitbox.getScaleX());
		}
		hitbox.setY(getCenterY() - hitbox.getScaleY() / 2);
	}
}

void Figure::update(float frameTime) {
	if (!onGround) deltaV.y = 0.1;
	if (velocity.x > 0) deltaV.x = -0.1;
	if (velocity.x < 0) deltaV.x = 0.1;
	if (velocity.x < 0.1 && velocity.x > -0.1) deltaV.x = -velocity.x;
	Entity::update(frameTime);

	if (getCenterX() + edge.left < 0) {
		velocity.x *= -1;
	}

	if (getCenterX() + edge.right > GAME_WIDTH) {
		velocity.x *= -1;
	}

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
}

bool attackPattern = false;
int attackTimer = 0;
int backupTimer = 0;

void Figure::Ai(Figure* enemy) {
	if (stunned > 0)  {
		stunned--;
		return;
	}
	isWalking = false;
	if (backupTimer > 200) {
		attackPattern = true;
		attackTimer = 200;
		backupTimer = 0;
	}
	if (rand() % 1000 > 900) attackPattern = true;

	if (enemy->getCenterX() > getCenterX()) {
		if (attackPattern) {
			if (abs(enemy->getCenterX() - getCenterX()) < 50) {
				isAttacking = true;
				if (facingRight) {
					hitbox.setX(getCenterX());
				} else {
					hitbox.setX(getCenterX() - hitbox.getScaleX());
				}
				hitbox.setY(getCenterY() - hitbox.getScaleY() / 2);
				attackPattern = false;
			} else if (velocity.x < maxAIHorizontalSpeed) {
				velocity.x += 0.2;
			}
			attackTimer--;
			if (attackTimer <= 0) {
				attackPattern = false;
			}
			return;
		}

		if(abs(enemy->getCenterX()) - abs(getCenterX()) < 200) {
			if (abs(enemy->getCenterX()) - abs(getCenterX()) > 190)
				return;
			if (velocity.x > -maxAIHorizontalSpeed / 2){
				velocity.x += -0.2;
				backupTimer++;
				return;
			}
		} else {
			if (velocity.x < maxAIHorizontalSpeed) {
				velocity.x += 0.2;
			}
		}
		isWalking = true;
		facingRight = true;
	} else if(enemy->getCenterX() < getCenterX()){
		if (attackPattern) {
			if (abs(enemy->getCenterX() - getCenterX()) < 50) {
				isAttacking = true;
				if (facingRight) {
					hitbox.setX(getCenterX());
				} else {
					hitbox.setX(getCenterX() - hitbox.getScaleX());
				}
				hitbox.setY(getCenterY() - hitbox.getScaleY() / 2);
				attackPattern = false;
			} else if (velocity.x > -maxAIHorizontalSpeed){
				velocity.x += -0.2;
			}
			attackTimer--;
			if (attackTimer <= 0) {
				attackPattern = false;
			}
			return;
		}

		if(abs(enemy->getCenterX() - getCenterX()) < 200) {
			if (abs(enemy->getCenterX() - getCenterX()) > 190)
				return;
			if (velocity.x < maxAIHorizontalSpeed / 2){
				velocity.x += 0.2;
				backupTimer++;
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