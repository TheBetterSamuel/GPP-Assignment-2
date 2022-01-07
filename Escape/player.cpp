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
    onGround = playerNS::ONGROUND;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
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
    //check if player is inside the map
    /*
    if (!input || !graphics) return;
    if (spriteData.x >= 0)
    {
        if (spriteData.x <= (GAME_WIDTH - BOX_SIZE)) {
            // checks kep presses for movement left and right
            if (input->isKeyDown(A_KEY))            // if move right
            {
                velocity.x = -playerNS::SPEED;
            }
            else if (input->isKeyDown(D_KEY))            // if move right
            {
                velocity.x = playerNS::SPEED;
            }
            else {
                velocity.x = 0;
            }
        }
        else {
            spriteData.x = (GAME_WIDTH - BOX_SIZE - 2);
        }
    }
    else {
        spriteData.x = 2;
    }
    */

    //jumping

    //correct angle
    if (spriteData.angle >= 360) {
        spriteData.angle -= 360;
    }

    if (onGround) {
        if ((spriteData.angle >= 0) && (spriteData.angle < 90)) {
            spriteData.angle = 0;
        }
        if ((spriteData.angle >= 90) && (spriteData.angle < 180)) {
            spriteData.angle = 90;
        }
        if ((spriteData.angle >= 180) && (spriteData.angle < 270)) {
            spriteData.angle = 180;
        }
        if ((spriteData.angle >= 270) && (spriteData.angle < 360)) {
            spriteData.angle = 270;
        }
    }
    
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
}