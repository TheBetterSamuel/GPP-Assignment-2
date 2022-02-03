// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment1:		Cheats:Enabled
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// InkdotEngine - Bullet Entity Class Specification
// ===========================================================================

#ifndef _ENTITY_BULLET_H
#define _ENTITY_BULLET_H

// include necessary headers
#include "entity.h"
#include "constants.h"


// related constructs

namespace bulletNS
{
	// texture constants

	const int WIDTH = 880;
	const int HEIGHT = 233;
	const int TEXTURE_COLS = 1;
	const int START_FRAME = 0;
	const int END_FRAME = 0;
	const int ANIM_DELAY = 0;
	const float SCALE = SPRITE_SCALE;       // Scaling up sprites to fit map
	// initial position
	const int COLLISION_DIST = (BOX_SIZE / 4) - 2; // Distance from center of player to edge of player, with 2 pixels of leeway
	const float X = (GAME_WIDTH - WIDTH) / 2.0f;
	const float Y = (GAME_HEIGHT - HEIGHT) / 2.0f;

	// physics constants
	const float G = entityNS::GRAVITY;      // Gravitional constant
	const float ROTATION_RATE = (float)PI / 4;
	const float SPEED = 300;
	const float MASS = 0;
}


// class specification

class Bullet : public Entity
{
private:

	// entity states

public:

	// default constructor
	Bullet();

	// default destructor
	~Bullet();


	// entity methods

	// initializes the entity - called on scene initialization
	virtual bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);

	// prepares the entity for deletion - called before entity is destroyed
	virtual void cleanup() {}

	// updates the entity - called each frame before scene update() starts
	virtual void update(float prevFrameTime);

	// handles artificial intelligence for the entity - called each frame
	virtual void ai() {}

	//get and set velocity.x and velocity.y
	virtual float getVelX() const { return velocity.x; }
	virtual void setVelX(float VelX) { velocity.x = VelX; }
	virtual float getVelY() const { return velocity.y; }
	virtual void setVelY(float VelY) { velocity.y = VelY; }

};

#endif // !_ENTITY_BULLET_H