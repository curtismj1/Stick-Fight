#ifndef __BOXER_
#define __BOXER_
#include "Figure.h"

class Boxer : public Figure {
public:
	Boxer();
	void animate(float frameTime);
private:
	void setCollisionBox();
};
#endif