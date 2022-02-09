// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Scene Class specification
// ===========================================================================
// acts as a state template, so I did not think this needs a CPP

#ifndef _SCENE_H
#define _SCENE_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "graphics.h"
#include "textDX.h"
#include "input.h"
#include "constants.h"
#include "gameError.h"
#include "ISceneManager.h"
#include "IScene.h"
#include <string>
#include "entity.h"
#include <vector>
#include "textDX.h"
#include <unordered_map>
#include "enemy.h"
#include "Player.h"

using namespace std;

// Entity structure to store other values along with the entity pointer
struct EntitySpec {
	Entity* entity;
	string name;
	bool gravity;

	// constructor
	EntitySpec(Entity* e, string n,bool g) :
		entity(e),
		name(n),
		gravity(g)
	{
	}
};

// class specification

class Scene : public IScene
{

protected:
	// pointer to the associated sceneManager (to call transition method)
	ISceneManager* sceneManager;

	// list of the entities along with its other variables
	vector<EntitySpec> entityList;


public:

	// abstract functions

	// initialization
	virtual void initialize()=0;

	// update objects
	virtual void update(float prevFrameTime)=0;

	virtual void render() = 0;

	// handle ai
	virtual void ai() = 0;

	// handle collisions
	virtual void collisions() = 0;

	// releases all memory reserved for graphics objects
	virtual void releaseAll() = 0;

	// resets all graphics objects
	virtual void resetAll() = 0;

	// scene functions

	// ===========================================================================
	// Add Entity to the scene's entity list. Added through an EntitySpec struct
	// ===========================================================================
	void addEntity(Entity* entity, string name,bool gravity) {
		entityList.push_back(EntitySpec(entity, name, gravity));
	};

	// ===========================================================================
	// Updates all entities, applies gravity for those entities specified.
	// ===========================================================================
	void updateAllEntities(float frameTime) {
		for (int i = 0; i < entityList.size(); i++) {
			Entity* entityptr = entityList[i].entity;
			if (entityList[i].gravity) {
				entityptr->setDeltaV(VECTOR2(0, entityptr->getGravity() * frameTime));
				//for now not * mass because gravity is too high
			}
			//if (entityList[i].name == "enemy") {
			//	dynamic_cast<Enemy*>(entityptr)->update(frameTime);
			//}
			//else if (entityList[i].name == "player") {
			//	dynamic_cast<Player*>(entityptr)->update(frameTime);
			//}
			entityptr->update(frameTime);
		}
	}

	// ===========================================================================
	// Renders/draws all entities.
	// ===========================================================================
	void renderAllEntities() {
		for (int i = 0; i < entityList.size(); i++) {
			entityList[i].entity->Image::setScale(SPRITE_SCALE);
			entityList[i].entity->draw();
		}
	}

	// ===========================================================================
	// Set scene manager for a scene. Needed to call transitionToScene method.
	// ===========================================================================
	void setSceneManager(ISceneManager* sceneMgr)
	{
		sceneManager = sceneMgr;
	}

	// IScene function overrides

	// returns the graphics handler for the scene
	Graphics* getGraphics() const
	{
		// ensure sceneManager is bound
		if (!sceneManager) throw(
			GameError(
				gameErrorNS::FATAL_ERROR,
				"Error: SceneManager not bound for this Scene!")
			);

		return sceneManager->getGraphics();
	}

	// returns the input handler for the scene
	Input* getInput() const
	{
		// ensure sceneManager is bound
		if (!sceneManager) throw(
			GameError(
				gameErrorNS::FATAL_ERROR,
				"Error: SceneManager not bound for this Scene!")
			);

		return sceneManager->getInput();
	}

};

#endif