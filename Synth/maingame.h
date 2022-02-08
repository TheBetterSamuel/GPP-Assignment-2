// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment:		2
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// MainGame Class implementation
// ===========================================================================

#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "game.h"
#include "testscene.h"
#include "xwtestscene.h"
#include "startmenuscene.h"
#include "levelselectscene.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class MainGame : public Game
{
private:
    

public:
    // Constructor
    MainGame();

    // Destructor
    virtual ~MainGame();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
