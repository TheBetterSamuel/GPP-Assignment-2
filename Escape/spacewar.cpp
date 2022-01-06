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
	if (!playerTexture.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player textures"));
	if (!groundTexture.initialize(graphics, GROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground textures"));
	if (!finishboxTexture.initialize(graphics, FINISHBOX_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing finishbox textures"));
	if (!killboxTexture.initialize(graphics, KILLBOX_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing killbox textures"));

	//clears list of sprites before drawing
	playerList.clear();
	groundList.clear();
	kBoxList.clear();
	fBoxList.clear();
	
	//drawing the map
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			//ground
			if (MAP[i][j] == 'G') {
				Ground ground;
				if (!ground.initialize(this, groundNS::WIDTH, groundNS::HEIGHT, 0, &groundTexture))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground"));
				ground.setX(j * BOX_SIZE);
				ground.setY(i * BOX_SIZE);
				groundList.push_back(ground);
			}
			//killbox
			 else if (MAP[i][j] == 'D') {
				Killbox killbox;
				if (!killbox.initialize(this, killboxNS::WIDTH, killboxNS::HEIGHT, 0, &killboxTexture))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing killbox"));
				killbox.setX(j * BOX_SIZE);
				killbox.setY(i * BOX_SIZE);
				kBoxList.push_back(killbox);
			}
			//finishbox
			else if (MAP[i][j] == 'F') {
				Finishbox finishbox;
				if (!finishbox.initialize(this, finishboxNS::WIDTH, finishboxNS::HEIGHT, 0, &finishboxTexture))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing finishbox"));
				finishbox.setX(j * BOX_SIZE);
				finishbox.setY(i * BOX_SIZE);
				fBoxList.push_back(finishbox);
			}
			//player
			else if (MAP[i][j] == 'P') {
				if (!player.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, 0, &playerTexture))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
				player.setX(j * BOX_SIZE);
				player.setY(i * BOX_SIZE);
				playerList.push_back(player);
			}
		}
	}
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	if (player.getOnGround() == true) {

		if (input->isKeyDown(W_KEY)) {
			player.setOnGround(false);
			player.setVelY(player.getVelY() - JUMP_DY);
		}
		else {
			//player.setVelY(0);
		}
	}

	


	for (int g = 0; g < groundList.size(); g++) {
		groundList[g].update(frameTime);
	}
	for (int k = 0; k < kBoxList.size(); k++) {
		kBoxList[k].update(frameTime);
	}
	for (int f = 0; f < fBoxList.size(); f++) {
		fBoxList[f].update(frameTime);
	}
	for (int p = 0; p < playerList.size(); p++) {
		player.update(frameTime);
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
	VECTOR2 cV;

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
	player.setVelY(player.getVelY() + playerNS::G * frameTime);
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites


	for (int g = 0; g < groundList.size(); g++) {
		groundList[g].draw();
	}
	for (int k = 0; k < kBoxList.size(); k++) {
		kBoxList[k].draw();
	}
	for (int f = 0; f < fBoxList.size(); f++) {
		fBoxList[f].draw();
	}
	for (int p = 0; p < playerList.size(); p++) {
	   player.draw();
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
	playerTexture.onLostDevice();
	killboxTexture.onLostDevice();
	finishboxTexture.onLostDevice();
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
	killboxTexture.onResetDevice();
	finishboxTexture.onResetDevice();
	Game::resetAll();
	return;
}
