// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy Class implementation
// ===========================================================================

// include specifications
#include "enemy.h"

//============================================================================
// default constructor
//============================================================================
Enemy::Enemy() :
	// parent class constructor
	IEnemy(),
	// state machine
	enemyStates(),
	currentState(NULL),
	currentStateName("")
{
	// initialize sprite data
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
Enemy::~Enemy() {
	/*for (int i = 0; i < enemyStates.size(); i++) {
		delete (enemyStates[i]);
	}*/

}

// entity methods

//============================================================================
// initializes the entity - called on scene initialization
//============================================================================
bool Enemy::initialize(Graphics* graphics, int width, int height, int ncols, TextureManager* textureM, Player* player)
{
	// configure sprite animation
	//this->setFrames(enemyNS::START_FRAME, enemyNS::END_FRAME);
	//this->setCurrentFrame(enemyNS::START_FRAME);
	//this->setFrameDelay(enemyNS::ANIM_DELAY);
	//this->setLoop(1);
	playerptr = player; // needed to follow player real-time

	// register all states
	WalkRight* right = new WalkRight();
	addState(right, "right");

	WalkLeft* left = new WalkLeft();
	addState(left, "left");

	ActiveState* active = new ActiveState();
	addState(active, "active");


	// transition to initial state
	changeState(enemyNS::INITIAL_STATE);

	return(Entity::initialize(graphics, width, height, ncols, textureM));
}

//=============================================================================
// draw the enemy
//=============================================================================
void Enemy::draw()
{
	Image::setScale(SPRITE_SCALE);
	Image::draw();              
}

//============================================================================
// updates the entity
//============================================================================
void Enemy::update(float frameTime)
{
	if (currentState) {
		currentState->update(this, playerptr, frameTime);
	}

	velocity += deltaV;
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y
	Entity::update(frameTime);

}

// ===========================================================================
// add state to  enemy state dictionary
// ===========================================================================
void Enemy::addState(
	EnemyState* state,
	std::string		stateName
) {
	// check if scene is not registered, else throw a warning and exit early
	if (enemyStates.count(stateName) == 0) {
		// if not already registered, register scene
		enemyStates.insert({ stateName, state });
	}
	else {
		// throw a warning
		throw(
			GameError(
				gameErrorNS::WARNING,
				"Warning: State is already registered for name: " + stateName)
			);
		return;
	}

}

// ===========================================================================
// change state based on string. This helps prevent circular dependency
// ===========================================================================
bool Enemy::changeState(
	std::string	stateName
) {
	if (stateName == "") {
		// if empty, issue warning
		throw(
			GameError(
				gameErrorNS::WARNING,
				"Warning: Change State is empty!")
			);

		// exit early
		return false;
	}

	// ensure sceneName is registered
	if (enemyStates.count(stateName) == 0) {
		throw(
			GameError(
				gameErrorNS::WARNING,
				"Warning: State not found!")
			);

		// exit early
		return false;
	}

	// find state based on string input
	EnemyState* nextState = enemyStates.at(stateName);

	if (nextState) {
		// update current state
		currentState = nextState;
		currentStateName = stateName;
		return true;
	}
	else {
		return false;
	}
}