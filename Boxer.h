#ifndef __BOXER_
#define __BOXER_
#include "Figure.h"

class Boxer : public Figure {
public:
	Boxer();
	void readInput();
private:
	void setCollisionBox();
};
#endif