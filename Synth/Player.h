// GPP Assignment 1


#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace playerNS
{
    const int WIDTH = SPRITE_SIZE;             // image width
    const int HEIGHT = SPRITE_SIZE;            // image height
    const float SPEED = MOVESPEED;          // Move based on move speed from constants.h
    const float SCALE = SPRITE_SCALE;       // Scaling up sprites to fit map
    const float G = entityNS::GRAVITY;      // Gravitional constant
    const int COLLISION_DIST = (BOX_SIZE / 4) - 2; // Distance from center of player to edge of player, with 2 pixels of leeway
    const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
    const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
    const float MASS = 3000.0f;              // mass

}

// inherits from Entity class
class Player : public Entity
{

public:
    // constructor
    Player();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Graphics* graphics, int width, int height, int ncols, TextureManager* textureM);
    void update(float frameTime);
    void damage();
    void power();
    int playerSpd = 500;
    int playerhp = 3;
    float cooldown = 1.0f;
    float lifeTime = 5.0f;
    bool cancollide = false;
    float sinceLast = 5.0f;
    bool canPower = false;

    

    //get and set velocity.x and velocity.y
    virtual float getVelX() const { return velocity.x; }
    virtual void setVelX(float VelX) { velocity.x = VelX; }
    virtual float getVelY() const { return velocity.y; }
    virtual void setVelY(float VelY) { velocity.y = VelY; }
};
#endif