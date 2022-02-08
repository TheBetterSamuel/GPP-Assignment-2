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

// include necessary headers
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
#include "idlestate.h"

// related constructs



// class specification

class Enemy : public IEnemy, public Entity
{
private:
	bool    active;         // only active entities may collide
	VECTOR2 velocity;       // velocity
	VECTOR2 deltaV;         // added to velocity during next call to update()
	// contains all scenes registered with this instance.
	std::unordered_map<std::string, EnemyState*> stateRegistry;

	EnemyState* currentState;

	// string identifier for the current state
	std::string	currentStateName;

	// entity states
	float shotTimer;
	float cooldownTime;
	float lifetime;

	TextureManager bulletTexture;
	std::vector<Bullet*> bulletList;

public:
	Player* playerptr;
	bool playerDetect;

	// default constructor
	Enemy();

	// default destructor
	~Enemy();


	// entity methods
	// shoots a bullet
	void shoot(Bullet* bullet, float x, float y, bool flip);
	// initializes the entity - called on scene initialization
	virtual bool initialize(Graphics* graphics, int width, int height, int ncols, TextureManager* textureM, Player* playerptr);
	virtual void draw();
	// prepares the entity for deletion - called before entity is destroyed
	virtual void cleanup() {}

	// updates the entity - called each frame after scene update() ends
	virtual void update(float frameTime);

	// handles artificial intelligence for the entity - called each frame
	virtual void ai() {}

	// Return X position.
	virtual float getX() { return spriteData.x; }

	// Return Y position.
	virtual float getY() { return spriteData.y; }

	// Set X location.
	virtual void setX(float newX) { spriteData.x = newX; }

	// Set Y location.
	virtual void setY(float newY) { spriteData.y = newY; }

	// Set rotation angle in degrees.
   // 0 degrees is up. Angles progress clockwise.
	virtual void setDegrees(float deg) { spriteData.angle = deg * ((float)PI / 180.0f); }

	// Set rotation angle in radians.
	// 0 radians is up. Angles progress clockwise.
	virtual void setRadians(float rad) { spriteData.angle = rad; }

	virtual void setState(EnemyState* newState)
	{
		if (newState) { delete currentState; currentState = newState; }
	}

	void registerState(
		EnemyState* state,
		std::string		stateName
	);

	virtual bool transitionToState(std::string stateName);

	// Set velocity.
	virtual void  setVelocity(VECTOR2 v) { velocity = v; }

	// Set delta velocity. Added to velocity in update().
	virtual void  setDeltaV(VECTOR2 dv) { deltaV = dv; }

	// Set active.
	virtual void  setActive(bool a) { active = a; }

	//setstate
	// if (currentState)
	// setState(currentState->update(this, deltaTime));
	//currentstate
	//
	// setState(EnemyState* newState): if(newState) { delete currentState; currentState = newState; }
};

#endif // !_ENTITY_ENEMY_H