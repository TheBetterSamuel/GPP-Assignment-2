// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment1:		Cheats:Enabled
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// InkdotEngine - Enemy Entity Class Implementation
// ===========================================================================

// include specifications
#include "enemy.h"

//============================================================================
// default constructor
//============================================================================
Enemy::Enemy() :
	playerDetect(),
	player(),

	// base object constructor
	Entity(),
	// entity states
	shotTimer(),
	cooldownTime(2.0f),

	// bullet states
	bulletTexture(),
	bulletList()
{
	edge.left = -(enemyNS::COLLISION_DIST);
	edge.top = -(enemyNS::COLLISION_DIST);
	edge.right = enemyNS::COLLISION_DIST;
	edge.bottom = enemyNS::COLLISION_DIST;
	gravity = enemyNS::G;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	spriteData.width = enemyNS::WIDTH * enemyNS::SCALE;           // size of Ship1
	spriteData.height = enemyNS::HEIGHT * enemyNS::SCALE;
	spriteData.x = enemyNS::X;                   // location on screen
	spriteData.y = enemyNS::Y;
	spriteData.rect.bottom = enemyNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = enemyNS::WIDTH;
	mass = enemyNS::MASS;
}

//============================================================================
// default destructor
//============================================================================
Enemy::~Enemy() {}


// entity methods

//============================================================================
// initializes the entity - called on scene initialization
//============================================================================
bool Enemy::initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM, Player* player)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//============================================================================
// updates the entity - called each frame before scene update() starts
//============================================================================
void Enemy::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y

	
}


//============================================================================
// shoots a bullet
//============================================================================
void Enemy::shoot(
	Bullet* bullet,
	float	x,
	float	y,
	bool	flip
) {

}
