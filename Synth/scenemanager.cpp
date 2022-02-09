// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Scene Manager Class implementation
// ===========================================================================

#include "sceneManager.h"

// scene name constants
namespace sceneNS {
	const std::string	EXIT_GAME = "EXIT_GAME";
}

// ===========================================================================
// default constructor
// ===========================================================================
SceneManager::SceneManager() :
	// initial values
	sceneDictionary(),
	currentScene(NULL),
	currentSceneName(""),
	graphicsptr(NULL),
	inputptr(NULL)
{}

// ===========================================================================
// default destructor
// ===========================================================================
SceneManager::~SceneManager()
{}

// ===========================================================================
// initializes a scenemanager instance
// ===========================================================================
void SceneManager::initialize(Graphics* graphics,Input* input) {
	// get graphics and input from game
	graphicsptr = graphics;
	inputptr = input;
}

// ===========================================================================
// register scene to dictionary with string
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

	// set scene manager for the scene to this instance
	scene->setSceneManager(this);
}

// ===========================================================================
// transitions to the scene with the specified scene name as was
// registered within the scene dictionary.
// ===========================================================================
bool SceneManager::transitionToScene(std::string sceneName) {

	// exit game through scene transition
	if (sceneName == sceneNS::EXIT_GAME) {
		// quit game
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

	// retrieve scene based on string
	Scene* nextScene = sceneDictionary.at(sceneName);

	// ensure scene is not null
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

	// update scenemanager states appropriately
	currentScene = nextScene;
	currentSceneName = sceneName;

	// initialize new scene
	currentScene->initialize();

	return true;
}

// ===========================================================================
// update current scene
// ===========================================================================
void SceneManager::updateCurrentScene(float prevFrameTime) {

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
// reset all graphics objects for current scene
// ===========================================================================
void SceneManager::resetGraphicsForCurrentScene()
{
	//recreate grapphics
	if (currentScene) currentScene->resetAll();
}
