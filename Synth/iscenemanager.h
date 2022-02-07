// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// ISceneManager Class implementation
// ===========================================================================

#ifndef _ISCENEMANAGER_H
#define _ISCENEMANAGER_H

// import necessary headers
#include "graphics.h"
#include "input.h"
#include <string>


// class specification

class ISceneManager
{
public:

	// abstract methods

	virtual bool transitionToScene(std::string sceneName) = 0;

	// abstract getters to be implemented by child classes
	virtual Graphics* getGraphics() const = 0;
	virtual Input* getInput() const = 0;

};

#endif