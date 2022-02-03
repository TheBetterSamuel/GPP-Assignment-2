// Programming 2D Games

#ifndef _ENEMYSTATE_H            // Prevent multiple definitions if this 
#define _ENEMYSTATE_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "constants.h"
#include "enemy.h"

class EnemyState
{
   public:
       virtual ~EnemyState() {}
       virtual void handleInput(Enemy* enemy, Input* input) {}
       virtual void update(Enemy* enemy) {}
};//end of HeroineState class
#endif
