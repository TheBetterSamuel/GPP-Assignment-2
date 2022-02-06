// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy Class implementation
// ===========================================================================

// include specification
#include "sceneManager.h"

namespace sceneNS {
	const std::string	NO_SCENE = "NO_SCENE";
	const std::string	EXIT_GAME = "EXIT_GAME";
	const std::string	STARTUP = "STARTUP";
	const std::string	MAIN_MENU = "MAIN_MENU";
	const std::string	LEVELCREATOR = "LEVEL_CREATOR";
	const std::string	LEVELSELECT = "LEVEL_SELECT";
}
// ===========================================================================
// default constructor
// ===========================================================================
SceneManager::SceneManager() :

	// members
	sceneRegistry(),
	currentScene(NULL),
	currentSceneName(""),

	// handlers
	graphics(NULL),
	input(NULL)
{}

// ===========================================================================
// default destructor
// ===========================================================================
SceneManager::~SceneManager()
{
	// safely delete all registered scenes

	// setup scene registry iterator
	std::unordered_map<std::string, Scene*>::iterator it =
		sceneRegistry.begin();

	// loop through iterator until all elements traversed
	while (it != sceneRegistry.end()) {

		// delete mapped scene object at scene pointer
		SAFE_DELETE(it->second);

		// increment iterator
		it++;
	}
}


// methods

// ===========================================================================
// initializes the SceneManager instance
// ===========================================================================
void SceneManager::initialize(
	Graphics* g,
	Input* i
) {
	// store argument info into instance state
	graphics = g;
	input = i;
}

// ===========================================================================
// registers a scene to the registry for easy retrieval and later use
// ===========================================================================
void SceneManager::registerScene(
	Scene* scene,
	std::string		sceneName
) {
	// check if scene is not registered, else throw a warning and exit early
	if (sceneRegistry.count(sceneName) > 0) {

		// throw a warning
		throw(
			GameError(
				gameErrorNS::WARNING,
				"Warning: Scene is already registered for id: " + sceneName
			)
			);

		// exit early
		return;
	}

	// if not already registered, register scene
	sceneRegistry.insert({ sceneName, scene });

	// set scene manager for scene to this instance
	scene->setSceneManager(this);
}

// ===========================================================================
// transitions to the scene with the specified scene name as was
// registered within the scene registry.
// ===========================================================================
bool SceneManager::transitionToScene(
	std::string	sceneName
) {
	// handle remove scene (transition to no scene)
	if (sceneName == sceneNS::NO_SCENE){

		// run cleanup on current scene
		if (currentScene) currentScene->cleanup();
		if (currentScene) currentScene->deleteAll();

		// update current scene states
		currentScene = NULL;
		currentSceneName = sceneNS::NO_SCENE;

		// exit early
		return true;
	}

	// handle exiting game
	else if (sceneName == sceneNS::EXIT_GAME) {

		// run cleanup on current scene
		if (currentScene) currentScene->cleanup();
		if (currentScene) currentScene->deleteAll();

		// quit main message loop
		PostQuitMessage(0);
	}

	// ensure sceneName is registered
	if (sceneRegistry.count(sceneName) == 0) {

		// throw a warning
		throw(
			GameError(
				gameErrorNS::WARNING,
				"Warning: Scene is not registered for id: " + sceneName
			)
			);

		// exit early
		return false;
	}

	// retrieve scene from registry
	Scene* nextScene = sceneRegistry.at(sceneName);

	// ensure scene is retrieved successfully
	if (nextScene == NULL) {

		// throw a warning
		throw(
			GameError(
				gameErrorNS::WARNING,
				"Warning: Transitioned scene is null!"
			)
			);

		// exit early
		return false;
	}

	// run cleanup on current scene
	if (currentScene) currentScene->cleanup();
	if (currentScene) currentScene->deleteAll();

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
void SceneManager::runCurrentScene(
	float prevFrameTime
) {
	// run scene handlers in sequence

	// update

	if (currentScene) currentScene->update(prevFrameTime);

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

	currentScene->renderBackground();
	currentScene->renderForeground();

	getGraphics()->spriteEnd();
}

// ===========================================================================
// release all graphics objects from memory for current scene
// ===========================================================================
void SceneManager::releaseGraphicsForCurrentScene()
{
	if (currentScene) currentScene->releaseAllGraphics();
}

// ===========================================================================
// reset and restore all graphics objects for current scene
// ===========================================================================
void SceneManager::resetGraphicsForCurrentScene()
{
	if (currentScene) currentScene->resetAllGraphics();
}
