
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 spacewar.h v1.0

#ifndef _LOSESCENE_H             // Prevent multiple definitions if this 
#define _LOSESCENE_H             // file is included in more than one place
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
class LoseScene : public Scene
{
private:
    TextDX* dxFontSmall;       // DirectX fonts
    TextDX* dxFontMedium;
    TextDX* dxFontLarge;


public:
    // Constructor
    LoseScene();

    // Destructor
    virtual ~LoseScene();

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