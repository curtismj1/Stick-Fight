#include "StickFight.h"

//=============================================================================
// Constructor
//=============================================================================
StickFight::StickFight() {
	nWalls = 1;
	walls = new Entity[nWalls];
}

//=============================================================================
// Destructor
//=============================================================================
StickFight::~StickFight()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void StickFight::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

}

//=============================================================================
// Update all game items
//=============================================================================
void StickFight::update()
{
	one.update(frameTime);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void StickFight::ai()
{

}

//=============================================================================
// Handle collisions
//=============================================================================
void StickFight::collisions()
{
	one.collisions(walls, nWalls);
}

//=============================================================================
// Render game items
//=============================================================================
void StickFight::render()
{
	graphics->spriteBegin();
	one.draw();
	graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void StickFight::releaseAll()
{
    Game::releaseAll();
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void StickFight::resetAll()
{
    Game::resetAll();
}
