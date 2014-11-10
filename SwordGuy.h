#ifndef __SWORD_
#define __SWORD_
#include "Figure.h"

class SwordGuy : public Figure {
public:
	SwordGuy();
	void animate(float frameTime);
	void soundHit(Audio* a);
	void soundMiss(Audio* a);
private:
	void setCollisionBox();
};
#endif