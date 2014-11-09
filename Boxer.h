#ifndef __BOXER_
#define __BOXER_
#include "Figure.h"

class Boxer : public Figure {
public:
	Boxer();
	void animate();
	void jab();
	void cross();
private:
	float time;
	void setCollisionBox();
	
};
#endif