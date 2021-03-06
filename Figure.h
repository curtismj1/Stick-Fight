#ifndef __FIGURE_H_
#define __FIGURE_H_

#include "entity.h"
class Figure : public Entity {
public:
	Figure();
	virtual void readInput(bool p2);
	virtual void update(float);
	void collisions(Entity* walls, int nWalls);
	Entity* getHitbox() { if (isAttacking) return &hitbox; else return 0; }
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	int getHealth() { return health; }
	void damage(int d);
	int getInvincible() { return invincible; }
	void Ai(Figure*);
	virtual void animate(float frameTime) = 0;
	virtual void soundHit(Audio* a) = 0;
	virtual void soundMiss(Audio* a) = 0;
	int stunned;
protected:
	virtual void setCollisionBox() = 0;

	bool onGround;
	bool facingRight;
	bool isAttacking;
	bool isBlocking;
	bool isWalking;
	Entity hitbox;
	int health;
	int invincible;
	
	int attackCounter;
};
#endif