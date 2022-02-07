// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Scene Class implementation
// ===========================================================================

#ifndef _SCENE_H
#define _SCENE_H

// import necessary headers
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


// class specification

class Scene : public IScene
{

private:
	

protected:
	// pointer to the associated sceneManager handler
	ISceneManager* sceneManager;


public:

	// default constructor
	Scene();

	// default destructor
	~Scene();

	// scene initialization
	virtual void initialize();

	// delete/deallocate all scene objects
	virtual void deleteAll();

	// abstract scene methods

	// clean up scene objects and prepare to transit out of scene
	virtual void cleanup() = 0;

	// update objects for each frame
	virtual void update(float prevFrameTime) = 0;

	virtual void render() = 0;

	// handle artificial intelligence on each frame
	virtual void ai() = 0;

	// handle collisions for objects on each frame
	virtual void collisions() = 0;

	// releases all memory reserved for graphics objects
	virtual void releaseAll() = 0;

	// recreates and restores all graphics objects
	virtual void resetAll() = 0;


	// IScene getters

	// returns the graphics handler for the scene
	Graphics* getGraphics() const
	{
		// ensure sceneManager is bound
		if (!sceneManager) throw(
			GameError(
				gameErrorNS::FATAL_ERROR,
				"Error: SceneManager not bound for this Scene!"
			)
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
				"Error: SceneManager not bound for this Scene!"
			)
			);

		return sceneManager->getInput();
	}

	//// returns the entity manager for the scene
	//EntityManager* getEntityManager()
	//{
	//	return &entityManager;
	//}


	// setters

	// sets the sceneManager for the scene
	void setSceneManager(ISceneManager* sceneMgr)
	{
		sceneManager = sceneMgr;
	}

};

#endif