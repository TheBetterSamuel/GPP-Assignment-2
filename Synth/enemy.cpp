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
	// base object constructor
	IEnemy(),

	stateRegistry(),
	currentState(NULL),
	currentStateName(""),
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
Enemy::~Enemy() {
	// safely delete all registered states

	// setup scene registry iterator
	std::unordered_map<std::string, EnemyState*>::iterator it =
		stateRegistry.begin();

	// loop through iterator until all elements traversed
	while (it != stateRegistry.end()) {

		// delete mapped scene object at scene pointer
		SAFE_DELETE(it->second);

		// increment iterator
		it++;
	}

}

// entity methods

//============================================================================
// initializes the entity - called on scene initialization
//============================================================================
bool Enemy::initialize(Scene* sceneptr, int width, int height, int ncols, TextureManager* textureM, Player* player)
{
	// configure sprite animation
	this->setFrames(enemyNS::START_FRAME, enemyNS::END_FRAME);
	this->setCurrentFrame(enemyNS::START_FRAME);
	this->setFrameDelay(enemyNS::ANIM_DELAY);
	this->setLoop(1);
	playerptr = player;

	IdleState* idle = new IdleState();
	registerState(idle, "idle");

	ActiveState* active = new ActiveState();
	registerState(active, "active");

	transitionToState("idle");

	return(Entity::initialize(sceneptr, width, height, ncols, textureM));
}

//=============================================================================
// draw the enemy
//=============================================================================
void Enemy::draw()
{
	Image::setScale(SPRITE_SCALE);
	Image::draw();              // draw player
}

//============================================================================
// updates the entity - called each frame before scene update() starts
//============================================================================
void Enemy::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y

	if (currentState) {
		setState(currentState->update(this, frameTime));
	}

	if (currentStateName == "idle") {
		setVisible(0);
	}

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

// ===========================================================================
// registers a state to the registry for easy retrieval and later use
// ===========================================================================
void Enemy::registerState(
	EnemyState* state,
	std::string		stateName
) {
	// check if scene is not registered, else throw a warning and exit early
	if (stateRegistry.count(stateName) > 0) {

		// throw a warning
		throw(
			GameError(
				gameErrorNS::WARNING,
				"Warning: State is already registered for name: " + stateName
			)
			);

		// exit early
		return;
	}

	// if not already registered, register scene
	stateRegistry.insert({ stateName, state });

	//// set enemy for enemystate to this instance
	state->setEnemy(this);
}

// ===========================================================================
// transitions to the state with the specified state name as was
// registered within the state registry.
// ===========================================================================
bool Enemy::transitionToState(
	std::string	stateName
) {
	// handle remove scene (transition to no scene)
	if (stateName == "") {

		// run cleanup on current scene
		//if (currentState) currentState->cleanup();
		//if (currentState) currentState->deleteAll();

		// update current scene states
		currentState = NULL;
		currentStateName = "";

		// exit early
		return true;
	}


	// ensure sceneName is registered
	if (stateRegistry.count(stateName) == 0) {

		// throw a warning
		throw(
			GameError(
				gameErrorNS::WARNING,
				"Warning: Scene is not registered for id: " + stateName
			)
			);

		// exit early
		return false;
	}

	// retrieve scene from registry
	EnemyState* nextState = stateRegistry.at(stateName);

	// ensure scene is retrieved successfully
	if (nextState == NULL) {

		// throw a warning
		throw(
			GameError(
				gameErrorNS::WARNING,
				"Warning: Transitioned state is null!"
			)
			);

		// exit early
		return false;
	}

	// run cleanup on current scene
	//if (currentState) currentState->cleanup();
	//if (currentState) currentState->deleteAll();

	// update scene states appropriately
	currentState = nextState;
	currentStateName = stateName;

	// initialize new scene
	//currentState->initialize();

	return true;
}