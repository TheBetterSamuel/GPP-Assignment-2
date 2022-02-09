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
#include "Player.h"

// class specification
class EnemyState
{
public:
	virtual ~EnemyState() {}
	// abstract functions
	virtual void update(IEnemy* enemy, Player* player, float frameTime) = 0;

	bool playerDetected(Player* player, IEnemy* enemy) {
		if (!player) {
			// throw a warning
			throw(
				GameError(
					gameErrorNS::WARNING,
					"Warning: Player is null")
				);

			// exit
			return false;
		}

		if (abs(player->getCenterX() - enemy->getCenterX()) <= // x distance inbetween
			enemyNS::DETECT_RADIUS &&
			abs(player->getCenterY() - enemy->getCenterY()) <= // y distance inbetween
			enemyNS::DETECT_RADIUS
			) {
			return true;
		}
		else {
			return false;
		}
	}

	void followPlayer(IEnemy* enemy, Player* player, float frameTime) {
		enemy->setVelocity(VECTOR2((-enemy->getCenterX() + player->getCenterX()) * enemyNS::SPEED* frameTime, (-enemy->getCenterY() + player->getCenterY()))*enemyNS::SPEED*frameTime);
	}
};
#endif
