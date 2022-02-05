// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy Class implementation
// ===========================================================================

#ifndef _ENTITY_IENEMY_H
#define _ENTITY_IENEMY_H

// include necessary headers
#include "constants.h"
#include "entity.h"
#include "player.h"
#include "bullet.h"
#include "EnemyState.h"

#include "activestate.h"
#include "idlestate.h"

// class specification

class IEnemy : public Entity
{
private:
	EnemyState* currentState;

public:

	// entity methods
	virtual void draw() = 0;
	// prepares the entity for deletion - called before entity is destroyed
	virtual void cleanup() = 0;

	// updates the entity - called each frame after scene update() ends
	virtual void update(float frameTime) = 0;

	// handles artificial intelligence for the entity - called each frame
	virtual void ai() = 0;

	// Return X position.
	virtual float getX() = 0;

	// Return Y position.
	virtual float getY() = 0;

	// Set X location.
	virtual void setX(float newX) = 0;

	// Set Y location.
	virtual void setY(float newY) = 0;

	// Set rotation angle in degrees.
   // 0 degrees is up. Angles progress clockwise.
	virtual void setDegrees(float deg) = 0;

	// Set rotation angle in radians.
	// 0 radians is up. Angles progress clockwise.
	virtual void setRadians(float rad) = 0;

	virtual void setState(EnemyState* newState) = 0;

	virtual void registerState(
		EnemyState* state,
		std::string		stateName
	) = 0;

	virtual bool transitionToState(std::string stateName) = 0;

	//setstate
	// if (currentState)
	// setState(currentState->update(this, deltaTime));
	//currentstate
	//
	// setState(EnemyState* newState): if(newState) { delete currentState; currentState = newState; }
};

#endif // !_ENTITY_ENEMY_H