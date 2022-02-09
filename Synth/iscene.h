// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// IScene Class implementation
// ===========================================================================

#ifndef _ISCENE_H
#define _ISCENE_H

#include "graphics.h"
#include "input.h"


// class specification

class IScene
{
public:

	// abstract methods

	// return a pointer to the current graphics
	virtual Graphics* getGraphics() const = 0;

	// return a pointer to the current input
	virtual Input* getInput() const = 0;

};

#endif