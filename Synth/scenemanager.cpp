// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Scene Manager Class implementation
// ===========================================================================

// include specification
#include "sceneManager.h"

// add all scenes here
namespace sceneNS {
	const std::string	NO_SCENE = "NO_SCENE";
	const std::string	EXIT_GAME = "EXIT_GAME";
	const std::string	MAIN_MENU = "MAIN_MENU";
}
// ===========================================================================
// default constructor
// ===========================================================================
SceneManager::SceneManager() :
	// variables
	sceneDictionary(),
	currentScene(NULL),
	currentSceneName(""),

	// handlers
	graphicsptr(NULL),
	inputptr(NULL)
{}

// ===========================================================================
// default destructor
// ===========================================================================
SceneManager::~SceneManager()
{
}


// methods

// ===========================================================================
// initializes the SceneManager instance
// ===========================================================================
void SceneManager::initialize(Graphics* graphics,Input* input) {
	// store argument info into instance state
	graphicsptr = graphics;
	inputptr = input;
}

// ===========================================================================
// registers a scene to the dictionary for easy retrieval and later use
// ===========================================================================
void SceneManager::registerScene(Scene* scene,std::string sceneName) {
	// check if there is existing sceneName identifier
	if (sceneDictionary.count(sceneName) > 0) {
		// throw a warning
		throw(
			GameError(
				gameErrorNS::WARNING,
				"Warning: Scene is already registered for id: " + sceneName)
			);

		// exit
		return;
	}

	// if doesnt exist yet, register scene
	sceneDictionary.insert({ sceneName, scene });

	// set scene manager for scene to this instance
	scene->setSceneManager(this);
}

// ===========================================================================
// transitions to the scene with the specified scene name as was
// registered within the scene dictionary.
// ===========================================================================
bool SceneManager::transitionToScene(std::string sceneName) {
	// handle remove scene (transition to no scene)
	if (sceneName == sceneNS::NO_SCENE){

		// clear current scene
		if (currentScene) currentScene->releaseAll();

		// update current scene states
		currentScene = NULL;
		currentSceneName = sceneNS::NO_SCENE;

		// exit
		return true;
	}

	// handle exiting game
	else if (sceneName == sceneNS::EXIT_GAME) {


		// quit main message loop
		PostQuitMessage(0);
	}

	// check if sceneName doesnt exist
	if (sceneDictionary.count(sceneName) == 0) {

		// throw a warning
		throw(
			GameError(
				gameErrorNS::WARNING,
				"Warning: Scene is not registered for id: " + sceneName)
			);

		// exit
		return false;
	}

	// retrieve scene
	Scene* nextScene = sceneDictionary.at(sceneName);

	// ensure scene is retrieved successfully
	if (nextScene == NULL) {

		// throw a warning
		throw(
			GameError(
				gameErrorNS::WARNING,
				"Warning: Transitioned scene is null!")
			);

		// exit early
		return false;
	}

	// run cleanup on current scene
	if (currentScene) currentScene->releaseAll();

	// update scene states appropriately
	currentScene = nextScene;
	currentSceneName = sceneName;

	// initialize new scene
	currentScene->initialize();

	return true;
}


// scene-delegating methods

// ===========================================================================
// runs the currently displayed scene
// ===========================================================================
void SceneManager::runCurrentScene(float prevFrameTime) {
	// run scene handlers in sequence

	// This is called in the game class, replacing the game's update,ai and collisions.
	
	// update
	if (currentScene) currentScene->update(prevFrameTime);
	//ai
	if (currentScene) currentScene->ai();
	// collisions
	if (currentScene) currentScene->collisions();
}

// ===========================================================================
// renders the currently displayed scene
// ===========================================================================
void SceneManager::renderCurrentScene()
{
	// sprite drawing
	getGraphics()->spriteBegin();
	// calls the current scene to render
	currentScene->render();
	getGraphics()->spriteEnd();
}

// ===========================================================================
// release all graphics objects from memory for current scene
// ===========================================================================
void SceneManager::releaseGraphicsForCurrentScene()
{
	//release memory of the game object graphics in current scene
	if (currentScene) currentScene->releaseAll();
}

// ===========================================================================
// reset and restore all graphics objects for current scene
// ===========================================================================
void SceneManager::resetGraphicsForCurrentScene()
{
	//recreate grapphics
	if (currentScene) currentScene->resetAll();
}
