#include "StickFight.h"

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
	activeMenu = false;
	timeInState = 0.0;
	gameStates = SPLASH_SCREEN;
    Game::initialize(hwnd); // throws GameError
	for (int i = 0; i < nTextures; i++){
		if (!textures[i].initialize(graphics, images[i].c_str())) 
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	}

	if (!splashScreen.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &textures[6]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash screen"));

	for (int i = 0; i < nWalls; i++) {
		if (!walls[i].initialize(this, 2, 2, 0, &textures[2]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
		walls[i].setCollisionType(entityNS::BOX);
		RECT r;
		r.left =-walls[i].getWidth() / 2;
		r.right = walls[i].getWidth() / 2;
		r.top = -walls[i].getHeight() / 2;
		r.bottom = walls[i].getHeight() / 2;
		walls[i].setEdge(r);
	}

	if (!one.initialize(this, 180, 260, 6, &textures[3]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player one"));

	if (!oneHealth.initialize(this, 0, 0, 0, &textures[5]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player one health"));

	if (!two.initialize(this, 512, 512, 4, &textures[0]))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player two"));

	text.initialize(graphics, 30, false, false, "Cambria");
	text.setFontColor(graphicsNS::RED);

	walls[0].setX(0);
	walls[0].setY(400);
	walls[0].setScaleX(GAME_WIDTH / 2);
	walls[0].setScaleY(10);
	
	one.setX(100);
	one.setY(300);
	one.setScale(.5);

	oneHealth.setX(0);
	oneHealth.setY(0);
	oneHealth.setScaleY(20);


	two.setX(500);
	two.setY(250);
	two.setScale(0.5);

	// Menu
	activeMenu = false;
	mainMenu = new Menu();
	mainMenu->initialize(graphics, input, NULL);

	mainMenu->setMenuHeading("Options");

	std::vector<std::string> menuItems;
	menuItems.push_back("New Game >");	// Menu 1
	menuItems.push_back("SoundFX >");	// Menu 2
	menuItems.push_back("I'm Feeling Lucky");
	menuItems.push_back("Credits");
	mainMenu->setMenuItems(menuItems);

	std::vector<Menu*> children = mainMenu->getChildren();

	// menu1
	Menu* menu1 = new Menu();
	menu1->initialize(graphics, input, mainMenu);
	menuItems.resize(2);
	menuItems[0] = "1 Player";	// Index 11
	menuItems[1] = "2 Player";	// Index 12
	children[0] = menu1;

	menu1->setMenuItems(menuItems);
	menu1->setMenuHeading("Characters");

	// menu2
	Menu* menu2 = new Menu();
	menu2->initialize(graphics, input, mainMenu);
	menuItems.resize(2);
	menuItems[0] = "On";	// Index 21
	menuItems[1] = "Off";	// Index 22
	children[1] = menu2;

	menu2->setMenuItems(menuItems);
	menu2->setMenuHeading("Effects");
	

	mainMenu->setChildren(children);
	
}

//=============================================================================
// Update all game items
//=============================================================================
void StickFight::update()
{
	gameStateUpdate();
	if(activeMenu || gameStates == MENU) {
		mainMenu->getActiveMenu()->update();
		// Handle an action
	} else {
		//one.readInput();
		one.update(frameTime);
		two.readInput();
		two.update(frameTime);
		for (int i = 0; i < nWalls; i++) walls[i].update(frameTime);
	}
	if(input->wasKeyPressed(VK_ESCAPE)) activeMenu = !activeMenu;

	oneHealth.setScaleX(one.getHealth() * 2);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void StickFight::ai()
{
	one.Ai(&two);
}

//=============================================================================
// Handle collisions
//=============================================================================
void StickFight::collisions()
{
	one.collisions(walls, nWalls);
	two.collisions(walls, nWalls);

	VECTOR2 cv;
	Entity* hb = one.getHitbox();
	if (hb != 0 && two.collidesWith(*hb, cv) && two.getInvincible() == 0) {
		if (cv.x > 0)
			two.setVelocity(VECTOR2(-2, 0.5));
		else
			two.setVelocity(VECTOR2(-2, 0.5));
		two.damage(10);
		two.stunned = 10;
	}
	hb = two.getHitbox();
	if (hb != 0 && one.collidesWith(*hb, cv) && one.getInvincible() == 0) {
		if (cv.x > 0)
			one.setVelocity(VECTOR2(-2, 0.5));
		else
			one.setVelocity(VECTOR2(-2, 0.5));
		one.damage(10);
		one.stunned = 10;
	}
}

//=============================================================================
// Render game items
//=============================================================================
void StickFight::render()
{
	graphics->spriteBegin();
	if(activeMenu) {
		mainMenu->getActiveMenu()->displayMenu(frameTime);
	} else {	// All other cases
		switch(gameStates) {
		case SPLASH_SCREEN:
			splashScreen.draw();
			if(timeInState<.75) {
				text.print("PRESS SPACE TO CONTINUE",GAME_WIDTH/2-160,GAME_HEIGHT-40);
			} else if(timeInState>1.5) {
				timeInState = 0.0;
			}

			// Render splash screen
			break;
		case MENU:
			// Render menu
			mainMenu->getActiveMenu()->displayMenu(frameTime);
			break;
		case LEVEL1:
			if (one.getInvincible() > 0)
				one.draw(SETCOLOR_ARGB(100, 255, 255, 255));
			else
				one.draw();
			if (one.getInvincible() > 0)
				two.draw(SETCOLOR_ARGB(100, 255, 255, 255));
			else
				two.draw();
			/*if (one.getHitbox() != 0) {
				one.getHitbox()->draw();
			}
			if(two.getHitbox() != 0){
				two.getHitbox()->draw();
			}*/
	
			for (int i = 0; i < nWalls; i++) walls[i].draw();
	
			oneHealth.draw();
			
			break;
		case END:
			// You won or lost
			break;
		}

		
	}
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

//=============================================================================
// Update all game items
//=============================================================================

void StickFight::gameStateUpdate()
{
	timeInState += frameTime;
	if (gameStates==SPLASH_SCREEN && input->wasKeyPressed(VK_SPACE))
	{
		gameStates = MENU;
		timeInState = 0;
	}
	if (gameStates==MENU) {
		if(mainMenu->getMenuState() == MODE_1_PLAYER) {
			gameStates = LEVEL1;
			timeInState = 0;
		}
	}
	if (gameStates==LEVEL1)
	{
		timeInState = 0;
	}

	if (gameStates==END)
	{
		PostQuitMessage(0);
		timeInState = 0;
	}
}
