// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "losescene.h"


//=============================================================================
// Constructor
//=============================================================================
LoseScene::LoseScene()
{
	dxFontSmall = new TextDX();     // DirectX fonts
	dxFontMedium = new TextDX();
	dxFontLarge = new TextDX();
}

//=============================================================================
// Destructor
//=============================================================================
LoseScene::~LoseScene()
{
	//releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void LoseScene::initialize()
{

	Graphics* graphics = getGraphics();

	if (dxFontSmall->initialize(graphics, 45, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	// 62 pixel high Arial
	if (dxFontMedium->initialize(graphics, 62, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	// 124 pixel high Arial
	if (dxFontLarge->initialize(graphics, 124, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void LoseScene::update(float frameTime)
{

	if (getInput()->wasKeyPressed(VK_RETURN))
	{
		sceneManager->transitionToScene("START_MENU_SCENE");
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void LoseScene::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void LoseScene::collisions()
{

}

//=============================================================================
// Render game items
//=============================================================================
void LoseScene::render()

{
	getGraphics()->spriteBegin();                // begin drawing sprites
	dxFontSmall->setFontColor(graphicsNS::WHITE);
	dxFontMedium->setFontColor(graphicsNS::RED);
	dxFontLarge->setFontColor(graphicsNS::WHITE);
	dxFontMedium->print("You DIED", (GAME_WIDTH / 2) - (GAME_WIDTH / 12), (GAME_HEIGHT / 2) - (GAME_HEIGHT / 8));
	dxFontSmall->print("Press <Enter> to return to the main menu", (GAME_WIDTH / 2) - (GAME_WIDTH / 4), (GAME_HEIGHT / 2) + (GAME_HEIGHT / 8));
	getGraphics()->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void LoseScene::releaseAll()
{
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void LoseScene::resetAll()
{
	//Scene::resetAll();
	return;
}

// ===========================================================================
// clean up scene objects and prepare to transit out of scene
// ===========================================================================
void LoseScene::cleanup()
{
	// reset bg color
	getGraphics()->setBackColor(BLACKNESS);

}