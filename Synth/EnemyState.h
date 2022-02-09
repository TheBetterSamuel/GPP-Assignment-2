// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// Enemy State Class implementation
// ===========================================================================
// template for all enemy states. Does not need a cpp.


#ifndef _ENEMYSTATE_H            // Prevent multiple definitions if this 
#define _ENEMYSTATE_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN


#include <windows.h>
#include "constants.h"
#include "ienemy.h"
#include "Player.h"
#include <vector>
#include <D3dx9math.h>

// class specification
class EnemyState
{
public:

	// abstract functions
	virtual void update(IEnemy* enemy, Player* player, float frameTime) = 0;

	// ===========================================================================
	// Returns true if player is in range
	// ===========================================================================
	bool playerDetected(Player* player, IEnemy* enemy) {
		// if there is no player, which is highly unusual, throw warning
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

		// check if distance between enemy and player is lesser than the detect radius
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

	// ===========================================================================
	// Follow player using unit vector
	// ===========================================================================
	void followPlayer(IEnemy* enemy, Player* player, float frameTime) {
		VECTOR2 vector = VECTOR2((-enemy->getCenterX() + player->getCenterX()), (-enemy->getCenterY() + player->getCenterY())); // get vector from enemy to player
		/*float lengthsqr = enemyVector.x * enemyVector.x + enemyVector.y * enemyVector.y;
		VECTOR2 unitVector = enemyVector / sqrt(lengthsqr);*/
		VECTOR2* unitVector = D3DXVec2Normalize(&vector, &vector); // get unit vector from enemy to player
		//unitVector.y = 0;
		if (vector <= 0) {
			enemy->flipHorizontal(1);
		}
		else {
			enemy->flipHorizontal(0);
		}
		enemy->setVelocity(*unitVector * enemyNS::FOLLOWSPEED * frameTime); // follow the player
	}
	
};
#endif
