// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment1:		Cheats:Enabled
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// InkdotEngine - Load Scene Specification
// ===========================================================================

#ifndef _LOADSCENE_H
#define _LOADSCENE_H

// import necessary headers
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "ground.h"
#include "graphics.h"
#include "fileutils.h"
#include <string>
#include "scene.h"

// class specification

class LoadScene : public Scene
{
private:

	// text states

	TextDX HUDText;
	TextDX pauseText;

	// texture states

	TextureManager hud1Texture;
	TextureManager hud2Texture;

	// game logic states

	int		coinCount;
	float	playerVelocity;

	// timer states

	float	seconds;
	int		minutes;

	Player* playerptr;


	// win
	bool win;


public:

	// default constructor
	LoadScene();

	// default destructor
	~LoadScene();


	// methods

	// scene methods

	// Initialize the game
	void initialize(string fileName);
	void update(float frameTime);      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	// clean up scene objects and prepare to transit out of scene
	void cleanup();
	void releaseAll();
	void resetAll();

	// convert level to string
	static std::string convertLevelToString();

	// convert level to string
	static void convertStringToLevel(std::string s, Player* player);

	static std::vector<std::string> split_string_by(const std::string& str, char delim);
};

#endif // !_SCENE_LOAD_H