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
#include "constants.h"
#include "entity.h"
#include "player.h"
#include "bullet.h"
#include <vector>
#include "enemystate.h"


// related constructs

namespace enemyNS
{
	const int WIDTH = 26;             // image width
	const int HEIGHT = 26;            // image height

	const int	TEXTURE_COLS = 3;
	const int	START_FRAME = 0;
	const int	END_FRAME = 2;
	const float ANIM_DELAY = 0.2f;

	const float SPEED = MOVESPEED;          // Move based on move speed from constants.h
	const float SCALE = SPRITE_SCALE;       // Scaling up sprites to fit map
	const float G = entityNS::GRAVITY;      // Gravitional constant
	const int COLLISION_DIST = (BOX_SIZE / 4) - 2; // Distance from center of player to edge of player, with 2 pixels of leeway
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float MASS = 3000.0f;              // mass
}

// class specification

class Enemy : public Entity
{
private:
	EnemyState* state_;

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
	virtual bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM, Player* playerptr);
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

	//setstate
	// if (currentState)
	// setState(currentState->update(this, deltaTime));
	//currentstate
	//
	// setState(EnemyState* newState): if(newState) { delete currentState; currentState = newState; }
};

#endif // !_ENTITY_ENEMY_H