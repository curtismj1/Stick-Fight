#ifndef __FIGURE_H_
#define __FIGURE_H_

#include "entity.h"
class Figure : public Entity {
public:
	Figure();
	virtual void readInput();
	virtual void update(float);
	void collisions(Entity* walls, int nWalls);
	Entity* getHitbox() { if (isAttacking) return &hitbox; else return 0; }
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	int getHealth() { return health; }
	void damage(int d);
	int getInvincible() { return invincible; }
	void Ai(Figure*);
	virtual void animate() = 0;
protected:
	virtual void setCollisionBox();

	bool onGround;
	bool facingRight;
	bool isAttacking;
	bool isBlocking;
	bool isWalking;
	Entity hitbox;
	int health;
	int invincible;
	
};
#endif