// Assignment 2
// dsPortal Entity

#include "dsportal.h"

//=============================================================================
// default constructor
//=============================================================================
dsPortal::dsPortal() : Entity()
{
    edge.left = -(PORTAL_WIDTH / 2);
    edge.top = -(PORTAL_HEIGHT / 2);
    edge.right = PORTAL_WIDTH / 2;
    edge.bottom = PORTAL_HEIGHT / 2;
    gravity = dspNS::G;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    spriteData.width = dspNS::WIDTH * dspNS::SCALE;           // size of Killbox
    spriteData.height = dspNS::HEIGHT * dspNS::SCALE;
    spriteData.x = dspNS::X;                   // location on screen
    spriteData.y = dspNS::Y;
    spriteData.rect.bottom = dspNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = dspNS::WIDTH;
    mass = dspNS::MASS;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool dsPortal::initialize(Scene* sceneptr, int width, int height, int ncols, TextureManager* textureM)
{
    return(Entity::initialize(sceneptr, width, height, ncols, textureM));
}

//=============================================================================
// draw the player
//=============================================================================
void dsPortal::draw()
{
    Image::setScale(SPRITE_SCALE);
    Image::draw();              // draw player
}

//=============================================================================
// update player
//=============================================================================
void dsPortal::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
}