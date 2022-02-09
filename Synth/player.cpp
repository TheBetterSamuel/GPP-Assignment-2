// Assignment 1
// Player Entity

#include "player.h"

//=============================================================================
// default constructor
//=============================================================================
Player::Player() : Entity()
{
    edge.left = -(playerNS::COLLISION_DIST);
    edge.top = -(playerNS::COLLISION_DIST);
    edge.right = playerNS::COLLISION_DIST;
    edge.bottom = playerNS::COLLISION_DIST;
    gravity = playerNS::G;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    spriteData.width = playerNS::WIDTH * playerNS::SCALE;           // size of Ship1
    spriteData.height = playerNS::HEIGHT * playerNS::SCALE;
    spriteData.x = playerNS::X;                   // location on screen
    spriteData.y = playerNS::Y;
    spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = playerNS::WIDTH;
    mass = playerNS::MASS;
    collisionType = entityNS::BOX;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Graphics* graphics, int width, int height, int ncols, TextureManager* textureM)
{
    return(Entity::initialize(graphics, width, height, ncols, textureM));
}

//=============================================================================
// draw the player
//=============================================================================
void Player::draw()
{
    Image::setScale(SPRITE_SCALE);
    Image::draw();              // draw player
}

//=============================================================================
// update player
//=============================================================================
void Player::update(float frameTime)
{

    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
    if (lifeTime <= 6) {
        lifeTime += frameTime;
    }
    if (lifeTime >= cooldown)
    {
        cancollide = true;
    }
    else
    {
        cancollide = false;
    }

    //powerup stuffs
    if (sinceLast <= 6) {
        sinceLast += frameTime;
    }
    if (sinceLast >= cooldown)
    {
        canPower = true;
        playerSpd = 500;
    }
    else
    {
        canPower = false;
        
    }
}

//player dmg
void Player::damage() 
{
    if (cancollide == true) 
    {
        playerhp--;
        lifeTime = 0.0f;
    }

}

void Player::power()
{
    if (canPower == true)
    {
        playerSpd = 10000;
        sinceLast = 0.0f;
    }
}