// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Scene Class implementation
// ===========================================================================

// include specification
#include "scene.h"

// ===========================================================================
// default constructor
// ===========================================================================
Scene::Scene() :

	// handlers
	sceneManager(NULL)
{

}

// ===========================================================================
// default destructor
// ===========================================================================
Scene::~Scene()
{
	// deallocate all manually allocated scene objects
	deleteAll();

}


// extensible scene methods

// ===========================================================================
// initializes the Scene object instance
// ===========================================================================
void Scene::initialize()
{

	// setup scene objects
	initialize();
}
void Scene::update(float frameTime) {
}
// ===========================================================================
// deallocate all manually allocated scene objects and reset object to the
// pre-initialized state. will be called on instance destruction.
// ===========================================================================
void Scene::deleteAll()
{
	// release memory for all graphics objects and textures
	releaseAll();
}
