#ifndef __SWORD_
#define __SWORD_
#include "Figure.h"

class SwordGuy : public Figure {
public:
	SwordGuy();
	void animate();
private:
	void setCollisionBox();
};
#endif