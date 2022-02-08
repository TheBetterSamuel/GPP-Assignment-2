// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "maingame.h"

//=============================================================================
// Constructor
//=============================================================================
MainGame::MainGame()
{
	
}

//=============================================================================
// Destructor
//=============================================================================
MainGame::~MainGame()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void MainGame::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	
	TestScene* testScene = new TestScene();
	sceneManager->registerScene(testScene, "TEST_SCENE");

	TestScene2* testScene2 = new TestScene2();
	sceneManager->registerScene(testScene2, "TEST_SCENE2");

	StartMenuScene* startmenuscene = new StartMenuScene();
	sceneManager->registerScene(startmenuscene, "START_MENU_SCENE");

	LevelSelectScene* levelselectscene = new LevelSelectScene();
	sceneManager->registerScene(levelselectscene, "LEVEL_SELECT_SCENE");

	/*LoadLevelScene* loadlevelscene = new LoadLevelScene();
	sceneManager->registerScene(loadlevelscene, "LOAD_LEVEL_SCENE");*/

	sceneManager->transitionToScene("START_MENU_SCENE");
	
}

//=============================================================================
// Update all game items
//=============================================================================
void MainGame::update()
{
	
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void MainGame::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void MainGame::collisions()
{
	
}

//=============================================================================
// Render game items
//=============================================================================
void MainGame::render()
{
	
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void MainGame::releaseAll()
{

	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void MainGame::resetAll()
{

	Game::resetAll();
	return;
}


