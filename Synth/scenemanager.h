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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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
	
	// "dictionary" for all scenes and their sceneName
	std::unordered_map<std::string, Scene*> sceneDictionary;

	// pointer to the currently displayed scene (NULL if no scene displayed)
	Scene* currentScene;

	// string identifier for the currently displayed scene
	std::string	currentSceneName;

	// pointer to graphics handler in game
	Graphics* graphicsptr;

	// pointer to input handler in game
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
	void updateCurrentScene(float prevFrameTime);

	// renders the currently displayed scene
	void renderCurrentScene();

	// release all graphics for current scene
	void releaseGraphicsForCurrentScene();

	// reset all graphics for current scene
	void resetGraphicsForCurrentScene();

	// ISceneManager function overrides

	// transitions to the scene with the sceneName
	bool transitionToScene(std::string sceneName);

	// returns a pointer to the current graphics
	Graphics* getGraphics() const
	{
		return graphicsptr;
	};

	// returns a pointer to the current input
	Input* getInput() const
	{
		return inputptr;
	};

};

#endif