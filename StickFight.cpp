#include "StickFight.h"

const std::string images[] = { "img/figure.bmp", "img/wall.bmp"};
const int nTextures = 2;

//=============================================================================
// Constructor
//=============================================================================
StickFight::StickFight() {
	textures = new TextureManager[nTextures];

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
	for (int i = 0; i < nTextures; i++)
		if (!textures[i].initialize(graphics, images[i].c_str())) 
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	for (int i = 0; i < nWalls; i++) {
		if (!walls[i].initialize(this, 40, 2, 0, &textures[1]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
		walls[i].setCollisionType(entityNS::BOX);
		RECT r;
		r.left =-walls[i].getWidth() / 2;
		r.right = walls[i].getWidth() / 2;
		r.top = -walls[i].getHeight() / 2;
		r.bottom = walls[i].getHeight() / 2;
		walls[i].setEdge(r);
	}

	if (!one.initialize(this, 0, 0, 0, &textures[0]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player one"));

	text.initialize(graphics, 12, false, false, "Cambria");

	walls[0].setX(50);
	walls[0].setY(400);
	walls[0].setScale(13);

	one.setX(60);
	one.setY(350);
	one.setScale(25);
	one.setCollisionRadius(1);
}

//=============================================================================
// Update all game items
//=============================================================================
void StickFight::update()
{
	one.readInput();
	one.update(frameTime);
	for (int i = 0; i < nWalls; i++) walls[i].update(frameTime);
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

#include <string>
//=============================================================================
// Render game items
//=============================================================================
void StickFight::render()
{
	graphics->spriteBegin();
	one.draw();
	if (one.getHitbox() != 0) {
		one.getHitbox()->draw();
	}
	for (int i = 0; i < nWalls; i++) walls[i].draw();
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
