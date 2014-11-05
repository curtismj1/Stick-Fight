#ifndef __FIGURE_H_
#define __FIGURE_H_

#include "entity.h"
class Figure : public Entity {
public:
	Figure();
	void update(float);
	void collisions(Entity* walls, int nWalls);
private:

};
#endif