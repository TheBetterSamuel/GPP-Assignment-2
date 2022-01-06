// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	// main game textures
	if (!groundTexture.initialize(graphics, GROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground textures"));
	
	for (int i = 0; i < _countof(groundList); i++) {
		Ground ground = Ground();
		if (!ground.initialize(this, groundNS::WIDTH, groundNS::HEIGHT, 0, &groundTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground"));
		ground.setX(i * BOX_SIZE);
		ground.setY(GAME_HEIGHT - BOX_SIZE);
		groundList[i] = ground;
	}
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	for (int i = 0; i < _countof(groundList); i++) {
		groundList[i].setVelocity(VECTOR2(-MOVESPEED,0));
		if (groundList[i].getX() <= -BOX_SIZE) {
			groundList[i].setX(GAME_WIDTH);
			distance++;
		}
		groundList[i].update(frameTime);
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
	/*VECTOR2 cV;

	bool collidedWithGround = false;

	for (size_t i = 0; i < groundList.size(); i++) {
		if (player.collidesWith(groundList.at(i), cV))
		{
			// cV is computed by collidesWith
			

			 if (cV.y > 0) {
				 player.setVelY(0);
				 collidedWithGround = true;

			 }
			 else {
				 player.bounce(VECTOR2(0.0f, cV.y), groundList.at(i), 1.0f);
			 }
			 if (cV.x != 0) {
				 player.bounce(VECTOR2(cV.x, 0.0f), groundList.at(i), 1.000001f);
			 }
			// else {
			 

				 if(cV.y >= 0)
				 player.setOnGround(TRUE);
			// }
		}
	}

	if(!collidedWithGround)
	player.setVelY(player.getVelY() + playerNS::G * frameTime);*/
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites


	for (int g = 0; g < _countof(groundList); g++) {
		groundList[g].draw();
	}
	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	groundTexture.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
	groundTexture.onResetDevice();
	Game::resetAll();
	return;
}
