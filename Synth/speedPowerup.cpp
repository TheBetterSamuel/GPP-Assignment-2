// Assignment 2
// Player Entity

#include "speedPowerup.h"

//=============================================================================
// default constructor
//=============================================================================
SpeedPowerup::SpeedPowerup() : Entity()
{
    edge.left = -(spuNS::COLLISION_DIST);
    edge.top = -(spuNS::COLLISION_DIST);
    edge.right = spuNS::COLLISION_DIST;
    edge.bottom = spuNS::COLLISION_DIST;
    gravity = spuNS::G;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    spriteData.width = spuNS::WIDTH * spuNS::SCALE;           // size of Speed Power Up
    spriteData.height = spuNS::HEIGHT * spuNS::SCALE;
    spriteData.x = spuNS::X;                   // location on screen
    spriteData.y = spuNS::Y;
    spriteData.rect.bottom = spuNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = spuNS::WIDTH;
    mass = spuNS::MASS;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool SpeedPowerup::initialize(Graphics* graphics, int width, int height, int ncols, TextureManager* textureM)
{
    return(Entity::initialize(graphics, width, height, ncols, textureM));
}

//=============================================================================
// draw the player
//=============================================================================
void SpeedPowerup::draw()
{
    Image::setScale(SPRITE_SCALE);
    Image::draw();              // draw player
}

//=============================================================================
// update player
//=============================================================================
void SpeedPowerup::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
}