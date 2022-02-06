// Assignment 2
// Player Entity

#include "nportal.h"

//=============================================================================
// default constructor
//=============================================================================
nPortal::nPortal() : Entity()
{
    edge.left = -(PORTAL_WIDTH / 2);
    edge.top = -(PORTAL_HEIGHT / 2);
    edge.right = PORTAL_WIDTH / 2;
    edge.bottom = PORTAL_HEIGHT / 2;
    gravity = npNS::G;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    spriteData.width = npNS::WIDTH * npNS::SCALE;           // size of Killbox
    spriteData.height = npNS::HEIGHT * npNS::SCALE;
    spriteData.x = npNS::X;                   // location on screen
    spriteData.y = npNS::Y;
    spriteData.rect.bottom = npNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = npNS::WIDTH;
    mass = npNS::MASS;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool nPortal::initialize(Graphics* graphics, int width, int height, int ncols, TextureManager* textureM)
{
    return(Entity::initialize(graphics, width, height, ncols, textureM));
}

//=============================================================================
// draw the player
//=============================================================================
void nPortal::draw()
{
    Image::setScale(SPRITE_SCALE);
    Image::draw();              // draw player
}

//=============================================================================
// update player
//=============================================================================
void nPortal::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
}