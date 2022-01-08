// GPP Assignment 2


#ifndef _DSPORTAL_H                 // Prevent multiple definitions if this 
#define _DSPORTAL_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace dspNS
{
    const int WIDTH = PORTAL_WIDTH;             // image width
    const int HEIGHT = PORTAL_HEIGHT;            // image height
    const float SPEED = MOVESPEED;          // Move based on move speed from constants.h
    const float SCALE = SPRITE_SCALE;       // Scaling up sprites to fit map
    const float G = entityNS::GRAVITY;      // Gravitional constant
    const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
    const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
    const float MASS = 3000000.0f;              // mass
}

// inherits from Entity class
class dsPortal : public Entity
{
public:
    // constructor
    dsPortal();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);
    void update(float frameTime);
};
#endif

