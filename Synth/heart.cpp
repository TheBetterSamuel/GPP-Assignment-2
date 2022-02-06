// Assignment 2
// Player Entity

#include "heart.h"

//=============================================================================
// default constructor
//=============================================================================
Heart::Heart() : Entity()
{
    spriteData.width = heartNS::WIDTH * heartNS::SCALE;           // size of Killbox
    spriteData.height = heartNS::HEIGHT * heartNS::SCALE;
    spriteData.x = heartNS::X;                   // location on screen
    spriteData.y = heartNS::Y;
    spriteData.rect.bottom = heartNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = heartNS::WIDTH;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Heart::initialize(Scene* sceneptr, int width, int height, int ncols, TextureManager* textureM)
{
    return(Entity::initialize(sceneptr, width, height, ncols, textureM));
}

//=============================================================================
// draw the player
//=============================================================================
void Heart::draw()
{
    Image::setScale(SPRITE_SCALE);
    if (getActive())
        Image::draw();              // draw player
}

//=============================================================================
// update player
//=============================================================================
void Heart::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
}