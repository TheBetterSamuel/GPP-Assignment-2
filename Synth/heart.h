// GPP Assignment 1


#ifndef _HEART_H                 // Prevent multiple definitions if this 
#define _HEART_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace heartNS
{
    const int WIDTH = SPRITE_SIZE;             // image width
    const int HEIGHT = SPRITE_SIZE;            // image height          
    const float SCALE = SPRITE_SCALE;       // Scaling up sprites to fit map
    const int X = GAME_WIDTH / 2 - WIDTH / 2;    // location on screen
    const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
    const int MAX_HEART_SCALE = 0.2;
}

// inherits from Entity class
class Heart : public Entity
{
public:
    // constructor
    Heart();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Scene* sceneptr, int width, int height, int ncols, TextureManager* textureM);
    void update(float frameTime);
};
#endif
