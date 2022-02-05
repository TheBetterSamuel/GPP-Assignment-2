// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy Idle State Class implementation
// ===========================================================================

#ifndef _IDLESTATE_H            // Prevent multiple definitions if this 
#define _IDLESTATE_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <windows.h>
#include "constants.h"
#include "enemy.h"

class IdleState : public EnemyState
{
public:

    virtual ~IdleState() {}
    virtual EnemyState* update(Enemy* enemy, float frameTime) {
        if (1)
        {
            //enemyptr->setVelocity(VECTOR2(20, 0));
            //enemy->setVelocity(VECTOR2(20, 0));
            //EnemyState* active = new ActiveState();
            return NULL;
        }
    }
};//end of HeroineState class
#endif