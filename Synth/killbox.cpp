// Assignment 2
// Player Entity

#include "killbox.h"

//=============================================================================
// default constructor
//=============================================================================
Killbox::Killbox() : Entity()
{
    edge.left = -(kboxNS::COLLISION_DIST);
    edge.top = -(kboxNS::COLLISION_DIST);
    edge.right = kboxNS::COLLISION_DIST;
    edge.bottom = kboxNS::COLLISION_DIST;
    gravity = kboxNS::G;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    spriteData.width = kboxNS::WIDTH * kboxNS::SCALE;           // size of Killbox
    spriteData.height = kboxNS::HEIGHT * kboxNS::SCALE;
    spriteData.x = kboxNS::X;                   // location on screen
    spriteData.y = kboxNS::Y;
    spriteData.rect.bottom = kboxNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = kboxNS::WIDTH;
    mass = kboxNS::MASS;
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
    Image::draw();              // draw player
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