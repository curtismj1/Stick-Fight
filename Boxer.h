#ifndef __BOXER_
#define __BOXER_
#include "Figure.h"

class Boxer : public Figure {
public:
	Boxer();
	void animate(float frameTime);
	void soundHit(Audio* a);
	void soundMiss(Audio* a);
	void setHealth(float h);
private:
	void setCollisionBox();
};
#endif