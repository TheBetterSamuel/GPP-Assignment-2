// GPP Assignment 1


#ifndef _HEART_H                 // Prevent multiple definitions if this 
#define _HEART_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace heartNS
{
    const int WIDTH = 347;             // image width
    const int HEIGHT = 347;            // image height          
    const float SCALE = 0.2;       // Scaling up sprites to fit map
    const int X = GAME_WIDTH - ((WIDTH * SCALE)/2);    // location on screen
    const int Y = GAME_HEIGHT - HEIGHT;
}

// inherits from Entity class
class Heart : public Entity
{
public:
    // constructor
    Heart();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Graphics* graphics, int width, int height, int ncols, TextureManager* textureM);
    void update(float frameTime);
};
#endif
