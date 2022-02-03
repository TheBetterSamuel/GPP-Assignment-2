// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment1:		Cheats:Enabled
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// InkdotEngine - Bullet Entity Class Implementation
// ===========================================================================

// include specification
#include "bullet.h"

//============================================================================
// default constructor
//============================================================================
Bullet::Bullet() :

	// base object constructor
	Entity()
{
	edge.left = -(bulletNS::COLLISION_DIST);
	edge.top = -(bulletNS::COLLISION_DIST);
	edge.right = bulletNS::COLLISION_DIST;
	edge.bottom = bulletNS::COLLISION_DIST;
	gravity = bulletNS::G;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	spriteData.width = bulletNS::WIDTH * bulletNS::SCALE;           // size of Ship1
	spriteData.height = bulletNS::HEIGHT * bulletNS::SCALE;
	spriteData.x = bulletNS::X;                   // location on screen
	spriteData.y = bulletNS::Y;
	spriteData.rect.bottom = bulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bulletNS::WIDTH;
	mass = bulletNS::MASS;
}

//============================================================================
// default destructor
//============================================================================
Bullet::~Bullet() {}


// entity methods

//=============================================================================
// initializes the entity - called on scene initialization
//=============================================================================
bool Bullet::initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM) {
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// updates the entity - called each frame before scene update() starts
//=============================================================================
void Bullet::update(float frameTime) {

	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y

	//// kill bullet on hitting wall
	//if (int w = getCollider("sprite")->outsideRect(WindowConstants::BOUNDS))
	//{
	//	setActive(FALSE);
	//}

	//if (this->collidesWithTaggedEntities(
	//	"sprite",
	//	"player",
	//	collisionList
	//)) {

	//	InkdotEntity* e;

	//	// handle each collision in collision list
	//	for (size_t i = 0; i < collisionList.size(); i++) {

	//		e = entityManager->getEntity(std::get<2>(collisionList[i]));
	//		// kill bullet
	//		this->setActive(FALSE);
	//		// kill player
	//		e->setActive(FALSE);

	//		//enemy2.setActive(0);
	//		//enemy2.setVisible(0);
	//	}
	//}
}
