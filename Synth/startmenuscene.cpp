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
	if (getInput()->wasKeyPressed(0x57)) //keypress "W"
	{
		if (menuSelected == 0) {
			menuSelected = 1;
		}
		else {
			menuSelected--;
		}
	}
	if (getInput()->wasKeyPressed(0x53)) //keypress "S"
	{
		if (menuSelected == 1) {
			menuSelected = 0;
		}
		else {
			menuSelected++;
		}
	}
	if (getInput()->wasKeyPressed(VK_RETURN)) //keypress ENTER
	{
		switch (menuSelected) {
		case 0:
			sceneManager->transitionToScene("LEVEL_SELECT_SCENE");
			break;
		case 1:
			sceneManager->transitionToScene("EXIT_GAME");
			break;
		default:
			sceneManager->transitionToScene("LEVEL_SELECT_SCENE");
			break;
		}
	}
	if (getInput()->wasKeyPressed(0x41)) //keypress "A"
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
	for (int i = 0; i < _countof(texts); i++) {
		int lineHeight = 62 * 1.5;
		int posX = (GAME_WIDTH / 2);
		int posY = (GAME_HEIGHT / 3) + (i * lineHeight);
		if (menuSelected == i) {
			dxFontMedium->setFontColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else {
			dxFontMedium->setFontColor(D3DCOLOR_ARGB(150, 255, 255, 255));
		}
		dxFontMedium->print(texts[i], posX, posY);
	}
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