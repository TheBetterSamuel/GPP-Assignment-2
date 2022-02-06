// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "startmenuscene.h"


//=============================================================================
// Constructor
//=============================================================================
StartMenuScene::StartMenuScene()
{
	dxFontSmall = new TextDX();     // DirectX fonts
	dxFontMedium = new TextDX();
	dxFontLarge = new TextDX();
}

//=============================================================================
// Destructor
//=============================================================================
StartMenuScene::~StartMenuScene()
{
	//releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void StartMenuScene::initialize()
{

	Graphics* graphics = getGraphics();

	if (dxFontSmall->initialize(graphics, 15, true, false, "Arial") == false)
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
void StartMenuScene::update(float frameTime)
{
	if (getInput()->isKeyDown(0x41)) //keypress "A"
	{
		sceneManager->transitionToScene("TEST_SCENE");
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void StartMenuScene::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void StartMenuScene::collisions()
{
	
}

//=============================================================================
// Render game items
//=============================================================================
void StartMenuScene::render()
{
	getGraphics()->spriteBegin();                // begin drawing sprites
	dxFontSmall->setFontColor(graphicsNS::WHITE);
	dxFontMedium->setFontColor(graphicsNS::WHITE);
	dxFontLarge->setFontColor(graphicsNS::WHITE);
	dxFontLarge->print("Cdasdasdadadasdadasdasdasd", GAME_WIDTH/2, GAME_HEIGHT/2);
	dxFontMedium->print("C", GAME_WIDTH / 2, 148);
	dxFontSmall->print("C", GAME_WIDTH / 2, 184);
	getGraphics()->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void StartMenuScene::releaseAll()
{
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void StartMenuScene::resetAll()
{
	//Scene::resetAll();
	return;
}

// ===========================================================================
// clean up scene objects and prepare to transit out of scene
// ===========================================================================
void StartMenuScene::cleanup()
{
	// reset bg color
	getGraphics()->setBackColor(BLACKNESS);

}