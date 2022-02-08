// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "startmenuscene.h"

using namespace graphicsNS;


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

	// main game textures
	if (!groundTexture.initialize(graphics, GROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground textures"));

	if (!playerTexture.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player textures"));

	//render fonts
	//45 pixel high arial
	if (dxFontSmall->initialize(graphics, 45, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	// 62 pixel high Arial
	if (dxFontMedium->initialize(graphics, 62, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	// 124 pixel high Arial
	if (dxFontLarge->initialize(graphics, 124, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	//game objects
	for (int i = 0; i < _countof(groundList); i++) {
		Ground ground = Ground();
		if (!ground.initialize(graphics, groundNS::WIDTH, groundNS::HEIGHT, 0, &groundTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground"));
		ground.setX(i * BOX_SIZE);
		ground.setY(GAME_HEIGHT - BOX_SIZE);
		groundList[i] = ground;
	}

	if (!player.initialize(graphics, playerNS::WIDTH, playerNS::HEIGHT, 0, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	player.setX(3 * BOX_SIZE);
	player.setY(GAME_HEIGHT - (2 * BOX_SIZE));

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
	if (getInput()->wasKeyPressed(0x42))
		sceneManager->transitionToScene("TEST_SCENE2");

	//updates ground
	for (size_t i = 0; i < _countof(groundList); i++) {
		if (speedState == 0) {
			groundList[i].setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			groundList[i].setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			groundList[i].setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (groundList[i].getX() <= -BOX_SIZE) {
			groundList[i].setX((_countof(groundList) - 1) * BOX_SIZE);
			distance++;
		}
		groundList[i].update(frameTime);
	}
	player.update(frameTime);
	playerStateManager(frameTime);

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void StartMenuScene::ai()
{}

//=============================================================================
// Render game items
//=============================================================================
void StartMenuScene::render()
{
	getGraphics()->spriteBegin();                // begin drawing sprites
	dxFontSmall->setFontColor(WHITE);
	dxFontMedium->setFontColor(CYAN);
	dxFontLarge->setFontColor(WHITE);
	for (int i = 0; i < _countof(texts); i++) {
		int lineHeight = 45 * 1.5;
		int posX = textMargin;
		int posY = (GAME_HEIGHT / 3) + (i * lineHeight);
		if (menuSelected == i) {
			dxFontSmall->setFontColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else {
			dxFontSmall->setFontColor(D3DCOLOR_ARGB(150, 255, 255, 255));
		}
		dxFontSmall->print(texts[i], posX, posY);
	}
	dxFontMedium->print("Synth", textMargin, textMargin);

	for (int g = 0; g < _countof(groundList); g++)
	{
		groundList[g].draw();
	}

	player.draw();
	getGraphics()->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// Handle collisions
//=============================================================================
void StartMenuScene::collisions()
{
	VECTOR2 cV;

	for (size_t i = 0; i < _countof(groundList); i++) {
		if (player.collidesWith(groundList[i], cV))
		{
			// cV is computed by collidesWith

			if (cV.y > 0) {
				if (player.getVelY() > 0)
					playerState = ONGROUND;
			}
			else {
				playerState = ONAIR;
			}
		}
		if (!getInput()->isKeyDown(VK_SPACE)) {
			if (playerState == ONGROUND)
				if ((groundList[i].getY() - player.getY()) != 0)
					if ((groundList[i].getY() - player.getY()) < (1.5 * BOX_SIZE))
						player.setY(groundList[i].getY() - BOX_SIZE);
		}
	}

	//jumping
	if (getInput()->isKeyDown(VK_SPACE))            // if SPACE is pressed
	{
		if (playerState == ONGROUND)
			playerState = ONJUMP;
	}
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void StartMenuScene::releaseAll()
{
	groundTexture.onLostDevice();
	playerTexture.onLostDevice();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void StartMenuScene::resetAll()
{
	groundTexture.onResetDevice();
	playerTexture.onResetDevice();
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

//=============================================================================
// Player State Manager
//=============================================================================
void StartMenuScene::playerStateManager(float frameTime) {
	if (playerState == ONGROUND) {
		player.setVelY(0);
		if ((player.getDegrees() > 0) && (player.getDegrees() < 90)) {
			player.setDegrees(0);
		}
		if ((player.getDegrees() > 90) && (player.getDegrees() < 180)) {
			player.setDegrees(90);
		}
		if ((player.getDegrees() > 180) && (player.getDegrees() < 270)) {
			player.setDegrees(180);
		}
		if ((player.getDegrees() > 270) && (player.getDegrees() < 360)) {
			player.setDegrees(270);
		}
	}
	if (playerState == ONJUMP) {
		player.setVelY(-JUMP_DY);
		playerState = ONAIR;
	}
	if (playerState == ONAIR) {
		player.setVelY(player.getVelY() + (playerNS::G * frameTime));
		if (player.getDegrees() >= 360) {
			player.setDegrees(player.getDegrees() - 360);
		}
		player.setDegrees(player.getDegrees() + (ROTATION_SPEED * frameTime));
	}
}