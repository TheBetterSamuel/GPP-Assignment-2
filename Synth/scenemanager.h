// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy Class implementation
// ===========================================================================

#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "graphics.h"
#include "input.h"
#include "constants.h"
#include "gameerror.h"
#include "iscenemanager.h"
#include "scene.h"
#include <string>
#include <unordered_map>
#include <vector>


// class specification

class SceneManager : ISceneManager
{
private:

	// members

	// contains all scenes registered with this instance.
	std::unordered_map<std::string, Scene*> sceneRegistry;

	// pointer to the currently displayed scene (NULL if no scene displayed)
	Scene* currentScene;

	// string identifier for the currently displayed scene
	std::string	currentSceneName;


	// handlers

	// pointer to graphics handler
	Graphics* graphics;

	// pointer to input handler
	Input* input;

public:

	// default constructor
	SceneManager();

	// default destructor
	~SceneManager();


	// methods

	/// <summary>
	/// Initializes the SceneManager instance
	/// </summary>
	/// <param name="g">
	/// : A pointer to the Graphics handler instance to be used for all scenes
	/// </param>
	/// <param name="i">
	/// : A pointer to the Input handler instance to be used for all scenes
	/// </param>
	void initialize(
		Graphics* g,
		Input* i
	);

	/// <summary>
	/// Registers a scene to the registry for easy retrieval and later use
	/// </summary>
	/// <param name="scene">
	/// : A pointer to the scene that is to be registered
	/// </param>
	/// <param name="identifier">
	/// : The identifier for the registered scene
	/// </param>
	void registerScene(
		Scene* scene,
		std::string		sceneName
	);


	// ISceneManager methods

	// transitions to the scene with the specified scene name as was
	// registered within the scene registry.
	virtual bool transitionToScene(std::string sceneName);

	// returns a pointer to the current graphics handler
	virtual Graphics* getGraphics() const
	{
		return graphics;
	};

	// returns a pointer to the current input handler
	virtual Input* getInput() const
	{
		return input;
	};


	// scene-delegating methods

	// runs the currently displayed scene
	void runCurrentScene(float prevFrameTime);

	// renders the currently displayed scene
	void renderCurrentScene();

	// release all graphics objects from memory for current scene
	void releaseGraphicsForCurrentScene();

	// reset and restore all graphics objects for current scene
	void resetGraphicsForCurrentScene();

};

#endif