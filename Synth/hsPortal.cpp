// Assignment 2
// dsPortal Entity

#include "hsportal.h"

//=============================================================================
// default constructor
//=============================================================================
hsPortal::hsPortal() : Entity()
{
    edge.left = -(PORTAL_WIDTH / 2);
    edge.top = -(PORTAL_HEIGHT / 2);
    edge.right = PORTAL_WIDTH / 2;
    edge.bottom = PORTAL_HEIGHT / 2;
    gravity = hspNS::G;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    spriteData.width = hspNS::WIDTH * hspNS::SCALE;           // size of Killbox
    spriteData.height = hspNS::HEIGHT * hspNS::SCALE;
    spriteData.x = hspNS::X;                   // location on screen
    spriteData.y = hspNS::Y;
    spriteData.rect.bottom = hspNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = hspNS::WIDTH;
    mass = hspNS::MASS;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool hsPortal::initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the player
//=============================================================================
void hsPortal::draw()
{
    Image::setScale(SPRITE_SCALE);
    Image::draw();              // draw player
}

//=============================================================================
// update player
//=============================================================================
void hsPortal::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
}