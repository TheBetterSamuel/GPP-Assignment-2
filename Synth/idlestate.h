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
#include "ienemy.h"
#include "EnemyState.h"

class IdleState : public EnemyState
{
private:
    float lifeTime;
public:

    virtual ~IdleState() {}
    virtual void update(IEnemy* enemy, Player* player, float frameTime) {
        lifeTime++;
        enemy->setVelocity(VECTOR2(-100, 0));
        if (player) {
            enemy->setVelocity(VECTOR2(0, 100));
        }
        if (lifeTime>=500)
        {
            enemy->transitionToState("active");
        }
    }
};//end of HeroineState class
#endif