// Assignment 1
// Player Entity

#include "ground.h"

//=============================================================================
// default constructor
//=============================================================================
Ground::Ground() : Entity()
{
    edge.left = -(groundNS::COLLISION_DIST);
    edge.top = -(groundNS::COLLISION_DIST);
    edge.right = groundNS::COLLISION_DIST;
    edge.bottom = groundNS::COLLISION_DIST;
    gravity = groundNS::G;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    spriteData.width = groundNS::WIDTH * groundNS::SCALE;           // size of Ship1
    spriteData.height = groundNS::HEIGHT * groundNS::SCALE;
    spriteData.x = groundNS::X;                   // location on screen
    spriteData.y = groundNS::Y;
    spriteData.rect.bottom = groundNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = groundNS::WIDTH;
    mass = groundNS::MASS;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Ground::initialize(Graphics* graphics, int width, int height, int ncols, TextureManager* textureM)
{
    return(Entity::initialize(graphics, width, height, ncols, textureM));
}

//=============================================================================
// draw the player
//=============================================================================
void Ground::draw()
{
    Image::setScale(SPRITE_SCALE);
    Image::draw();              // draw player
}

//=============================================================================
// update player
//=============================================================================
void Ground::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
}