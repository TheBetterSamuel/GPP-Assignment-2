// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy Idle State Class implementation
// ===========================================================================

#ifndef _WALKRIGHT_H            // Prevent multiple definitions if this 
#define _WALKRIGHT_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <windows.h>
#include "constants.h"
#include "ienemy.h"
#include "EnemyState.h"

class WalkRight : public EnemyState
{
private:
    float lifeTime;
public:

    virtual ~WalkRight() {}
    virtual void update(IEnemy* enemy, Player* player, float frameTime) {
        lifeTime+=frameTime;
        enemy->flipHorizontal(0);
        enemy->setDeltaV(VECTOR2(enemyNS::SPEED*frameTime,0));
		if (player && abs(player->getCenter()->x - enemy->getX()) <= enemyNS::DETECT_RADIUS && abs(player->getCenter()->y - enemy->getY()) <= enemyNS::DETECT_RADIUS) {
			enemy->changeState("active");
		}
        else if (lifeTime >= enemyNS::INTERVAL) {
            lifeTime = 0;
            enemy->setVelocity(VECTOR2(0, 0));
            enemy->changeState("left");
        }
    }
};
#endif