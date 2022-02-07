// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy State Class implementation
// ===========================================================================


#ifndef _ENEMYSTATE_H            // Prevent multiple definitions if this 
#define _ENEMYSTATE_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "constants.h"
#include "ienemy.h"

// class specification
class EnemyState
{
public:
	virtual ~EnemyState() {}
	virtual void update(IEnemy* enemy, float frameTime) = 0;
};
#endif
