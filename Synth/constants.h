// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "Synth";
const char GAME_TITLE[] = "Synth";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1280;               // width of game in pixels
const UINT GAME_HEIGHT = 720;               // height of game in pixels


const float MOVESPEED = 300;  //movement speed of the player
const float JUMP_DY = 800;   //starting dy of player when he jumps(decreases y g per second)
const float ROTATION_SPEED = 500; // how fast the [;ayer rotates while jumping

// height and width o the grid map
const UINT MAP_HEIGHT = 14;
const UINT MAP_WIDTH = 24;
const UINT SPRITE_SIZE = 16;
const UINT PORTAL_HEIGHT = 32;
const UINT PORTAL_WIDTH = 8;
const float BOX_SIZE = (float)GAME_WIDTH / MAP_WIDTH;
const float SPRITE_SCALE = (float)BOX_SIZE / SPRITE_SIZE;

// game
const double PI = 3.14159265;
const float FRAME_RATE = 120.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float GRAVITY = 9.81;                     // gravitational constant
const float MASS_PLANET = 1.0e14f;
const float MASS_SHIP = 5.0f;

// graphic images
const char GROUND_IMAGE[] = "pictures\\Ground.png";
const char PLAYER_IMAGE[] = "pictures\\Player.png";
const char NPORTAL_IMAGE[] = "pictures\\nPortal.png";
const char DSPORTAL_IMAGE[] = "pictures\\dsPortal.png";
const char HSPORTAL_IMAGE[] = "pictures\\hsPortal.png";

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key
const UCHAR A_KEY = 'A';
const UCHAR D_KEY = 'D';
const UCHAR S_KEY = 'S';
const UCHAR W_KEY = 'W';



// weapon types
enum WEAPON {TORPEDO, SHIP, PLANET};

#endif
