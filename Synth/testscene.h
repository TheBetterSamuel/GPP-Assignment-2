// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 spacewar.h v1.0

#ifndef _TESTSCENE_H             // Prevent multiple definitions if this 
#define _TESTSCENE_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "player.h"
#include "ground.h"
#include "killbox.h"
#include "nportal.h"
#include "dsportal.h"
#include "hsportal.h"
#include "speedPowerup.h"
#include "enemy.h"
#include "heart.h"
#include "scene.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class TestScene : public Scene
{
private:
    // game itemsWS
    TextureManager groundTexture;
    TextureManager playerTexture;
    TextureManager enemyTexture;
    TextureManager killboxTexture;
    TextureManager nPortalTexture;
    TextureManager dsPortalTexture;
    TextureManager hsPortalTexture;
    TextureManager speedPowerupTexture;
    TextureManager heartTexture;
    std::vector<Ground> activeGroundList;
    std::vector<Killbox> activeKillboxList;
    std::vector<nPortal> activenPortalList;
    std::vector<dsPortal> activedsPortalList;
    std::vector<hsPortal> activehsPortalList;
    std::vector<SpeedPowerup> activeSpeedPowerupList;
    Ground groundList[MAP_WIDTH + 2];       // the ground
    Player player;
    Enemy enemy;
    Heart heartList[MAX_HEART_NO];          // max hearts
    int numOfHits;
    UINT distance = 0;                      // distance in number of blocks
    UINT speedState = 0;                    // State of the game speed
    UINT playerState = ONGROUND;                   // State of the player


public:
    // Constructor
    TestScene();

    // Destructor
    virtual ~TestScene();

    // Initialize the game
    void initialize();
    void update(float frameTime);      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    // clean up scene objects and prepare to transit out of scene
    void cleanup();
    void releaseAll();
    void resetAll();
    void renderObject(char type, UINT position); //rendering object
    void playerStateManager(float frameTime);
};

#endif
