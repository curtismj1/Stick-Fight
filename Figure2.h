#ifndef __FIGURE2_H_
#define __FIGURE2_H_

#include "entity.h"
class Figure2 : public Entity {
public:
	Figure2();
	void readInput();
	void update(float);
	void collisions(Entity* walls, int nWalls);
	Entity* getHitbox() { if (isAttacking) return &hitbox; else return 0; }
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
private:
	bool onGround;

	bool facingRight;
	bool isAttacking;
	bool isWalking;
	Entity hitbox;
};
#endif