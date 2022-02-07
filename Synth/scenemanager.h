// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Scene manager Class Specification
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
	// variables
	
	// "dictionary" for all scenes and their sceneName
	std::unordered_map<std::string, Scene*> sceneDictionary;

	// pointer to the currently displayed scene (NULL if no scene displayed)
	Scene* currentScene;

	// string identifier for the currently displayed scene
	std::string	currentSceneName;

	// handlers

	// pointer to graphics handler
	Graphics* graphicsptr;

	// pointer to input handler
	Input* inputptr;

public:

	// default constructor
	SceneManager();

	// default destructor
	~SceneManager();


	// methods

	// initalize
	void initialize(Graphics* graphics,Input* input);

	// register scene state along with scene name as identifier
	void registerScene(Scene* scene,std::string sceneName);

	// runs the currently displayed scene
	void runCurrentScene(float prevFrameTime);

	// renders the currently displayed scene
	void renderCurrentScene();

	// release all graphics objects from memory for current scene
	void releaseGraphicsForCurrentScene();

	// reset and restore all graphics objects for current scene
	void resetGraphicsForCurrentScene();

	// ISceneManager methods

	// transitions to the scene with the sceneName
	bool transitionToScene(std::string sceneName);

	// returns a pointer to the current graphics handler
	Graphics* getGraphics() const
	{
		return graphicsptr;
	};

	// returns a pointer to the current input handler
	Input* getInput() const
	{
		return inputptr;
	};

};

#endif