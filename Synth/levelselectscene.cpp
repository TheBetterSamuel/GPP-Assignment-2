// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "levelselectscene.h"


//=============================================================================
// Constructor
//=============================================================================
LevelSelectScene::LevelSelectScene():
	selectedIndex(0)
{
	dxFontSmall = new TextDX();     // DirectX fonts
	dxFontMedium = new TextDX();
	dxFontLarge = new TextDX();
}

//=============================================================================
// Destructor
//=============================================================================
LevelSelectScene::~LevelSelectScene()
{
	//releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void LevelSelectScene::initialize()
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

	// register menu options
	vector<string> list = FileUtils::getFiles("Levels");
	OutputDebugStringA("Levels:");
	for (int i = 0; i < list.size(); i++) {
		options.push_back(list[i]);
	}
	OutputDebugStringA("Done printing");

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void LevelSelectScene::update(float frameTime)
{
	if (getInput()->wasKeyPressed(VK_UP)) {
		selectedIndex++;
	}
	else if (getInput()->wasKeyPressed(VK_DOWN)) {
		selectedIndex--;
	}
	else if (getInput()->wasKeyPressed(VK_RETURN)) {

		for (int i = 0; i < options.size(); i++) {
			if (selectedIndex = i) {
				sceneManager->transitionToScene("EXIT_GAME");
			}
		}
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void LevelSelectScene::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void LevelSelectScene::collisions()
{

}

//=============================================================================
// Render game items
//=============================================================================
void LevelSelectScene::render()
{
	getGraphics()->spriteBegin();                // begin drawing sprites
	dxFontSmall->setFontColor(graphicsNS::WHITE);
	dxFontMedium->setFontColor(graphicsNS::WHITE);
	dxFontLarge->setFontColor(graphicsNS::WHITE);
	for (int i = 0; i <options.size(); i++) {
		int lineHeight = 62 * 1.5;
		int posX = (GAME_WIDTH / 2);
		int posY = (GAME_HEIGHT / 3) + (i * lineHeight);
		if (selectedIndex == i) {
			dxFontMedium->setFontColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else {
			dxFontMedium->setFontColor(D3DCOLOR_ARGB(150, 255, 255, 255));
		}
		dxFontMedium->print(options[i], posX, posY);
	}
	getGraphics()->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void LevelSelectScene::releaseAll()
{
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void LevelSelectScene::resetAll()
{
	//Scene::resetAll();
	return;
}

// ===========================================================================
// clean up scene objects and prepare to transit out of scene
// ===========================================================================
void LevelSelectScene::cleanup()
{
	// reset bg color
	getGraphics()->setBackColor(BLACKNESS);

}