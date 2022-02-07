// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 spacewar.h v1.0

#ifndef _LEVELSELECTSCENE_H             // Prevent multiple definitions if this 
#define _LEVELSELECTSCENE_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "scene.h"
#include "fileutils.h"

using namespace std;

//=============================================================================
// This class is the core of the game
//=============================================================================
class LevelSelectScene : public Scene
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
   
    TextDX* dxFontSmall;       // DirectX fonts
    TextDX* dxFontMedium;
    TextDX* dxFontLarge;

    int selectedIndex = 1;
    vector<string> options;


public:
    // Constructor
    LevelSelectScene();

    // Destructor
    virtual ~LevelSelectScene();

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
};

#endif
