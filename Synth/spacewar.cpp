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

	if (!playerTexture.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player textures"));
	
	for (int i = 0; i < _countof(groundList); i++) {
		Ground ground = Ground();
		if (!ground.initialize(this, groundNS::WIDTH, groundNS::HEIGHT, 0, &groundTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground"));
		ground.setX(i * BOX_SIZE);
		ground.setY(GAME_HEIGHT - BOX_SIZE);
		groundList[i] = ground;
	}

	if (!player.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, 0, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	player.setX(3 * BOX_SIZE);
	player.setY(GAME_HEIGHT - (2 * BOX_SIZE));
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

	player.update(frameTime);
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
	VECTOR2 cV;

	bool collidedWithGround = false;

	for (size_t i = 0; i < _countof(groundList); i++) {
		if (player.collidesWith(groundList[i], cV))
		{
			// cV is computed by collidesWith
			

			 if (cV.y > 0) {
				 player.setVelY(0);
				 collidedWithGround = true;
			 }
			 else {
				 collidedWithGround = false;
			 }
		}
		if(collidedWithGround){
			if (!input->isKeyDown(W_KEY)) {
				if ((player.getDegrees() == 0) || (player.getDegrees() == 90)) {
					if (((player.getY() + BOX_SIZE) - groundList[i].getY()) < -20)
						player.setY(groundList[i].getY() - BOX_SIZE);
				}
				else {
					if ((player.getY() - groundList[i].getY()) < -20)
						player.setY(groundList[i].getY() - BOX_SIZE);
				}
			}
		}
	}

	//jumping
	if (input->isKeyDown(W_KEY))            // if W is pressed
	{
		if (collidedWithGround) {
			collidedWithGround = false;
			player.setVelY(-JUMP_DY);
		}
	}
	//correct angle
	if (player.getDegrees() >= 360) {
		player.setDegrees(player.getDegrees() - 360);
	}

	if (collidedWithGround) {
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
	else {
		player.setDegrees(player.getDegrees() + (ROTATION_SPEED * frameTime));
	}

	if(!collidedWithGround)
	player.setVelY(player.getVelY() + playerNS::G * frameTime);
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

	player.draw();

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	groundTexture.onLostDevice();
	playerTexture.onLostDevice();
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
	playerTexture.onResetDevice();
	Game::resetAll();
	return;
}
