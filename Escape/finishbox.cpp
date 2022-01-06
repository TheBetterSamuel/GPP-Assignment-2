// Assignment 1
// Player Entity

#include "finishbox.h"

//=============================================================================
// default constructor
//=============================================================================
Finishbox::Finishbox() : Entity()
{
    edge.left = -(finishboxNS::COLLISION_DIST);
    edge.top = -(finishboxNS::COLLISION_DIST);
    edge.right = finishboxNS::COLLISION_DIST;
    edge.bottom = finishboxNS::COLLISION_DIST;
    gravity = finishboxNS::G;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    spriteData.width = finishboxNS::WIDTH * finishboxNS::SCALE;           // size of Ship1
    spriteData.height = finishboxNS::HEIGHT * finishboxNS::SCALE;
    spriteData.x = finishboxNS::X;                   // location on screen
    spriteData.y = finishboxNS::Y;
    spriteData.rect.bottom = finishboxNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = finishboxNS::WIDTH;
    mass = finishboxNS::MASS;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Finishbox::initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the player
//=============================================================================
void Finishbox::draw()
{
    Image::setScale(SPRITE_SCALE);
    Image::draw();              // draw killbox
}

//=============================================================================
// update player
//=============================================================================
void Finishbox::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
}