// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy Class implementation
// ===========================================================================

#ifndef _SCENEMANAGERINTERFACE_H
#define _SCENEMANAGERINTERFACE_H

// import necessary headers
#include "graphics.h"
#include "input.h"
#include <string>


// class specification

class ISceneManager
{
public:

	// abstract methods to be implemented by child classes

	// should transition to the scene with the specified scene name as
	// was registered within the scene registry.
	virtual bool transitionToScene(std::string sceneName) = 0;


	// abstract getters to be implemented by child classes

	// should return a pointer to the current graphics handler
	virtual Graphics* getGraphics() const = 0;

	// should return a pointer to the current input handler
	virtual Input* getInput() const = 0;

};

#endif