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

	if (!killboxTexture.initialize(graphics, KILLBOX_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing killbox textures"));

	if (!nPortalTexture.initialize(graphics, NPORTAL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nportal textures"));

	if (!hsPortalTexture.initialize(graphics, HSPORTAL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hsportal textures"));

	if (!dsPortalTexture.initialize(graphics, DSPORTAL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dsportal textures"));
	
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

	//update ground list
	for (size_t i = 0; i < activeGroundList.size(); i++) {
		if (speedState == 0) {
			activeGroundList.at(i).setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			activeGroundList.at(i).setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			activeGroundList.at(i).setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (activeGroundList.at(i).getX() <= -BOX_SIZE) {
			activeGroundList.erase(activeGroundList.begin() + i);
		}
		activeGroundList.at(i).update(frameTime);
	}

	//update killbox List
	for (size_t i = 0; i < activeKillboxList.size(); i++) {
		if (speedState == 0) {
			activeKillboxList.at(i).setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			activeKillboxList.at(i).setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			activeKillboxList.at(i).setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (activeGroundList.at(i).getX() <= -BOX_SIZE) {
			activeKillboxList.erase(activeKillboxList.begin() + i);
		}
		activeKillboxList.at(i).update(frameTime);
	}

	//update nportal List
	for (size_t i = 0; i < activenPortalList.size(); i++) {
		if (speedState == 0) {
			activenPortalList.at(i).setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			activenPortalList.at(i).setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			activenPortalList.at(i).setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (activenPortalList.at(i).getX() <= -BOX_SIZE) {
			activenPortalList.erase(activenPortalList.begin() + i);
		}
		activenPortalList.at(i).update(frameTime);
	}

	//update dsportal List
	for (size_t i = 0; i < activedsPortalList.size(); i++) {
		if (speedState == 0) {
			activedsPortalList.at(i).setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			activedsPortalList.at(i).setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			activedsPortalList.at(i).setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (activedsPortalList.at(i).getX() <= -BOX_SIZE) {
			activedsPortalList.erase(activedsPortalList.begin() + i);
		}
		activedsPortalList.at(i).update(frameTime);
	}

	//update hsportal List
	for (size_t i = 0; i < activehsPortalList.size(); i++) {
		if (speedState == 0) {
			activehsPortalList.at(i).setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			activehsPortalList.at(i).setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			activehsPortalList.at(i).setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (activehsPortalList.at(i).getX() <= -BOX_SIZE) {
			activehsPortalList.erase(activehsPortalList.begin() + i);
		}
		activehsPortalList.at(i).update(frameTime);
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
				if ((player.getY() - groundList[i].getY()) != 0)
					if((groundList[i].getY() - player.getY()) < (1.5 * BOX_SIZE))
						player.setY(groundList[i].getY() - BOX_SIZE);
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
	player.setVelY(player.getVelY() + (playerNS::G * frameTime));
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

//=============================================================================
// Rendering based on grid and block type
// G = Ground, K = Killbox, N = nPortal, D = dsPortal, H = hsPortal
//=============================================================================
void Spacewar::renderObject(char type, UINT position) {
	if (type == 'G') {
		Ground ground;
		if (!ground.initialize(this, groundNS::WIDTH, groundNS::HEIGHT, 0, &groundTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground"));
		ground.setX(GAME_WIDTH);
		ground.setY(GAME_HEIGHT - (position * BOX_SIZE));
		activeGroundList.push_back(ground);
	}
	if (type == 'K') {
		Killbox kbox;
		if (!kbox.initialize(this, kboxNS::WIDTH, kboxNS::HEIGHT, 0, &killboxTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing killbox"));
		kbox.setX(GAME_WIDTH);
		kbox.setY(GAME_HEIGHT - (position * BOX_SIZE));
		activeKillboxList.push_back(kbox);
	}
	if (type == 'N') {
		nPortal np;
		if (!np.initialize(this, npNS::WIDTH, npNS::HEIGHT, 0, &nPortalTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nportal"));
		np.setX(GAME_WIDTH);
		np.setY(GAME_HEIGHT - (position * BOX_SIZE));
		activenPortalList.push_back(np);
	}
	if (type == 'H') {
		hsPortal hsp;
		if (!hsp.initialize(this, hspNS::WIDTH, hspNS::HEIGHT, 0, &hsPortalTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hsportal"));
		hsp.setX(GAME_WIDTH);
		hsp.setY(GAME_HEIGHT - (position * BOX_SIZE));
		activehsPortalList.push_back(hsp);
	}
	if (type == 'D') {
		dsPortal dsp;
		if (!dsp.initialize(this, dspNS::WIDTH, dspNS::HEIGHT, 0, &dsPortalTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hsportal"));
		dsp.setX(GAME_WIDTH);
		dsp.setY(GAME_HEIGHT - (position * BOX_SIZE));
		activedsPortalList.push_back(dsp);
	}
	return;
}
