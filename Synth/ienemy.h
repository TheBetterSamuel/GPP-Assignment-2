// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy Interface Class implementation
// ===========================================================================

#ifndef _ENTITY_IENEMY_H
#define _ENTITY_IENEMY_H

#include "entity.h"

// put here since enemy class imports this file anyways
namespace enemyNS
{
	// sprite constatnts
	const int WIDTH = 26;             // image width
	const int HEIGHT = 26;            // image height

	// animation constants
	const int	TEXTURE_COLS = 3;
	const int	START_FRAME = 0;
	const int	END_FRAME = 2;
	const float ANIM_DELAY = 0.2f;

	// state machine constants
	const std::string INITIAL_STATE = "right";
	const float DETECT_RADIUS = 1000;
	const float INTERVAL = 3.0f; // interval for changing directions when idling

	// speed constants
	const float SPEED = 100;          // Move based on move speed from constants.h
	const float FOLLOWSPEED = 20000;

	// other constants
	const float SCALE = SPRITE_SCALE;       // Scaling up sprites to fit map
	const float G = entityNS::GRAVITY;      // Gravitional constant
	const int COLLISION_DIST = (BOX_SIZE / 4) - 2; // Distance from center of player to edge of player, with 2 pixels of leeway
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float MASS = 3000.0f;              // mass
}
// class specification

class IEnemy
{
public:

	// enemy methods

	virtual void draw() = 0;
	// prepares the entity for deletion
	virtual void cleanup() = 0;

	// updates the entity
	virtual void update(float frameTime) = 0;

	// handles artificial intelligence for the entity - called each frame
	virtual void ai() = 0;

	// Return X position
	virtual float getX() = 0;

	// Return Y position
	virtual float getY() = 0;

	// Set X location
	virtual void setX(float newX) = 0;

	// Set Y location
	virtual void setY(float newY) = 0;

	// Set rotation angle in degrees
   // 0 degrees is up. Angles progress clockwise.
	virtual void setDegrees(float deg) = 0;

	// Set rotation angle in radians
	// 0 radians is up. Angles progress clockwise.
	virtual void setRadians(float rad) = 0;


	// Methods from entity and image class that is used in state machine

	virtual void  setVelocity(VECTOR2 v) = 0;

	virtual void  setDeltaV(VECTOR2 dv) = 0;

	virtual void  setActive(bool a) = 0;

	virtual void setVisible(bool v) = 0;

	virtual float getScale() = 0;

	virtual float getCenterX() = 0;

	virtual float getCenterY() = 0;

	virtual bool changeState(std::string stateName)=0;

	virtual void flipHorizontal(bool flip) = 0;
};

#endif