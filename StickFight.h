// Programming 2D Games
// Copyright (c) 2011,2012 by: 
// Charles Kelly
// StickFight.h v1.0

#ifndef _COLLISION_TYPES_H      // Prevent multiple definitions if this 
#define _COLLISION_TYPES_H      // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class StickFight;

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "Figure.h"
#include "textDX.h"
#include "SwordGuy.h"
#include "Boxer.h"
#include <cmath>

//=============================================================================
// This class is the core of the game
//=============================================================================
class StickFight : public Game
{
public:
    // Constructor
    StickFight();

    // Destructor
    virtual ~StickFight();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
private:
	TextureManager* textures;
	Image* staticImages;
	TextDX text;

	Figure** one;
	int oneChar;
	Entity oneHealth;

	Figure** two;
	int twoChar;
	Entity twoHealth;

	Entity* walls;
	int nWalls;
	Menu* mainMenu;
	bool activeMenu;
	bool SFXon;
	GameStates gameStates;
	float timeInState;
	void gameStateUpdate();

	bool multiplayer;
};

#endif
