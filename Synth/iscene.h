// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy Class implementation
// ===========================================================================

#ifndef _ISCENE_H
#define _ISCENE_H

// import necessary headers
#include "graphics.h"
#include "input.h"


// class specification

class IScene
{
public:

	// abstract getters to be implemented by child classes

	// should return a pointer to the current graphics handler
	virtual Graphics* getGraphics() const = 0;

	// should return a pointer to the current input handler
	virtual Input* getInput() const = 0;

};

#endif