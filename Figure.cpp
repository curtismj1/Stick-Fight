#include "Figure.h"

Figure::Figure() {

}

void Figure::update(float frameTime) {
	Entity::update(frameTime);
}

void Figure::collisions(Entity* walls, int nWalls) {
	VECTOR2 collisionVector;
	for(int i = 0; i < nWalls; i++)
		if (collidesWith(walls[i], collisionVector)) {

		}
}