// Assignment 1
// Player Entity

#include "killbox.h"

//=============================================================================
// default constructor
//=============================================================================
Killbox::Killbox() : Entity()
{
    edge.left = -(killboxNS::COLLISION_DIST);
    edge.top = -(killboxNS::COLLISION_DIST);
    edge.right = killboxNS::COLLISION_DIST;
    edge.bottom = killboxNS::COLLISION_DIST;
    gravity = killboxNS::G;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    spriteData.width = killboxNS::WIDTH * killboxNS::SCALE;           // size of Ship1
    spriteData.height = killboxNS::HEIGHT * killboxNS::SCALE;
    spriteData.x = killboxNS::X;                   // location on screen
    spriteData.y = killboxNS::Y;
    spriteData.rect.bottom = killboxNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = killboxNS::WIDTH;
    mass = killboxNS::MASS;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Killbox::initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the player
//=============================================================================
void Killbox::draw()
{
    Image::setScale(SPRITE_SCALE);
    Image::draw();              // draw killbox
}

//=============================================================================
// update player
//=============================================================================
void Killbox::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
}