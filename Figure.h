#ifndef __FIGURE_H_
#define __FIGURE_H_

#include "entity.h"
class Figure : public Entity {
public:
	Figure();
	void readInput();
	void update(float);
	void collisions(Entity* walls, int nWalls);
	Entity* getHitbox() { if (isAttacking) return &hitbox; else return 0; }
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
private:
	bool onGround;

	bool facingRight;
	bool isAttacking;
	Entity hitbox;
};
#endif