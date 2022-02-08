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
		if (lifeTime >= 200) {
			//flip
			enemy->setDeltaV(VECTOR2(-50, 0));
			if (lifeTime >= 400) {
				lifeTime = 0;
			}
		}
		else {
			//flip 0
			enemy->setDeltaV(VECTOR2(50, 0));
		}
		if (player && abs(player->getCenter()->x - enemy->getX()) <= 100 && abs(player->getCenter()->y - enemy->getY()) <= 100) {
			enemy->transitionToState("active");
		}
    }
};//end of HeroineState class
#endif