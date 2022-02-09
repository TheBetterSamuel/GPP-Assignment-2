// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy Active State Class implementation
// ===========================================================================

#ifndef _ACTIVESTATE_H            // Prevent multiple definitions if this 
#define _ACTIVESTATE_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <windows.h>
#include "constants.h"
#include "ienemy.h"
#include "EnemyState.h"

class ActiveState : public EnemyState
{
public:

    virtual ~ActiveState() {}
    virtual void update(IEnemy* enemy, Player* player, float frameTime) {
        followPlayer(enemy, player, frameTime);
        if (!playerDetected(player, enemy)) {
            enemy->changeState(enemyNS::INITIAL_STATE);
        }
    }

};
#endif
