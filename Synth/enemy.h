// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy Class implementation
// ===========================================================================

#ifndef _ENTITY_ENEMY_H
#define _ENTITY_ENEMY_H

#include <string>
#include <unordered_map>

#include "constants.h"
#include "entity.h"
#include "player.h"
#include "bullet.h"
#include <vector>
#include "EnemyState.h"
#include "ienemy.h"
#include "activestate.h"
#include "walkleft.h"
#include "walkright.h"

// class specification

class Enemy : public IEnemy, public Entity
{
private:

	// dictionary of enemy states
	std::unordered_map<std::string, EnemyState*> enemyStates;

	// pointer to the current state (so we can call the methods from it)
	EnemyState* currentState;

	// string identifier for the current state
	std::string	currentStateName;


public:

	// pointer to player. Enemy cannot function without player as it needs to access
	// player's location to follow it.
	Player* playerptr;

	// default constructor
	Enemy();

	// default destructor
	~Enemy();


	// entity methods

	// initializes the entity. Player pointer needed to be able to track player's location
	virtual bool initialize(Graphics* graphics, int width, int height, int ncols, TextureManager* textureM, Player* playerptr);
	
	//renders enemy
	virtual void draw();

	// prepares the entity for deletion 
	virtual void cleanup() {}

	// updates the entity
	virtual void update(float frameTime);

	// handles ai 
	virtual void ai() {}

	// Return X position
	virtual float getX() { return spriteData.x; }

	// Return Y position
	virtual float getY() { return spriteData.y; }

	// Return scale factor
	virtual float getScale() { return spriteData.scale; }

	// Set X location
	virtual void setX(float newX) { spriteData.x = newX; }

	// Set Y location
	virtual void setY(float newY) { spriteData.y = newY; }

	// Set rotation angle in degrees.
   // 0 degrees is up. Angles progress clockwise.
	virtual void setDegrees(float deg) { spriteData.angle = deg * ((float)PI / 180.0f); }

	// Set rotation angle in radians.
	// 0 radians is up. Angles progress clockwise.
	virtual void setRadians(float rad) { spriteData.angle = rad; }

	// Set velocity.
	virtual void  setVelocity(VECTOR2 v) { velocity = v; }

	// Set delta velocity. Added to velocity in update().
	virtual void  setDeltaV(VECTOR2 dv) { deltaV = dv; }

	// Set active.
	virtual void  setActive(bool a) { active = a; }

	// Set visible.
	virtual void setVisible(bool v) { visible = v; }

	// Set scale.
	virtual void setScale(float s) { spriteData.scale = s; }

	// Return center X.
	virtual float getCenterX() { return spriteData.x + spriteData.width / 2 * getScale(); }

	// Return center Y.
	virtual float getCenterY() { return spriteData.y + spriteData.height / 2 * getScale(); }

	// Flip horizontal
	virtual void flipHorizontal(bool flip) { spriteData.flipHorizontal = flip; }

	// state machine functions

	// add state to enemy state dictionary
	void addState(
		EnemyState* state,
		std::string		stateName
	);

	// change enemy state
	virtual bool changeState(std::string stateName);
};

#endif // !_ENTITY_ENEMY_H