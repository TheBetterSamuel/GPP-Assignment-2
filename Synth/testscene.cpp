// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "testscene.h"

//=============================================================================
// Constructor
//=============================================================================
TestScene::TestScene()
{
}

//=============================================================================
// Destructor
//=============================================================================
TestScene::~TestScene()
{
	//releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void TestScene::initialize()
{
	level = Level();
	level.loadData(LEVELPATH_2);

	Graphics* graphics = getGraphics();

	// main game textures
	if (!groundTexture.initialize(graphics, GROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground textures"));

	if (!playerTexture.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player textures"));

	if (!enemyTexture.initialize(graphics, ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy textures"));

	if (!killboxTexture.initialize(graphics, KILLBOX_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing killbox textures"));

	if (!nPortalTexture.initialize(graphics, NPORTAL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nportal textures"));

	if (!hsPortalTexture.initialize(graphics, HSPORTAL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hsportal textures"));

	if (!dsPortalTexture.initialize(graphics, DSPORTAL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dsportal textures"));

	if (!speedPowerupTexture.initialize(graphics, SPEEDPOWERUP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing speed power up textures"));

	if (!heartTexture.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart textures"));


	for (int i = 0; i < _countof(groundList); i++) {
		Ground ground = Ground();
		if (!ground.initialize(graphics, groundNS::WIDTH, groundNS::HEIGHT, 0, &groundTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground"));
		ground.setX(i * BOX_SIZE);
		ground.setY(GAME_HEIGHT - BOX_SIZE);
		groundList[i] = ground;
	}

	if (!player.initialize(graphics, playerNS::WIDTH, playerNS::HEIGHT, 0, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	player.setX(3 * BOX_SIZE);
	player.setY(GAME_HEIGHT - (2 * BOX_SIZE));

	//test enemy
	if (!enemy.initialize(graphics, enemyNS::WIDTH, enemyNS::HEIGHT, 0, &enemyTexture, &player))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	enemy.setX(100);
	enemy.setY(100);
	vector<Ground> gv = level.getGroundList();
	vector<Killbox> gk = level.getKillboxList();
	vector<Enemy> ge = level.getEnemyList();
	vector<SpeedPowerup> gs = level.getSpeedpowerupList();
	//render from map
	for (int i = 0; i < level.getMap().size(); i++) {
		for (int j = 0; j < level.getMap().at(i).size(); j++) {
			if (level.getMap().at(i).at(j) == levelDictionary::GROUND) {
				Ground ground;
				if (!ground.initialize(graphics, groundNS::WIDTH, groundNS::HEIGHT, 0, &groundTexture))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground"));
				ground.setX(j * BOX_SIZE);
				ground.setY(i * BOX_SIZE);
				gv.push_back(ground);
			}
			if (level.getMap().at(i).at(j) == levelDictionary::ENEMY) {
				Enemy enemy;
				if (!enemy.initialize(graphics, enemyNS::WIDTH, enemyNS::HEIGHT, 0, &enemyTexture, &player))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
				enemy.setX(j * BOX_SIZE);
				enemy.setY(i * BOX_SIZE);
				ge.push_back(enemy);
			}
			if (level.getMap().at(i).at(j) == levelDictionary::KILLBOX) {
				Killbox killbox;
				if (!killbox.initialize(graphics, kboxNS::WIDTH, kboxNS::HEIGHT, 0, &killboxTexture))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing killbox"));
				killbox.setX(j * BOX_SIZE);
				killbox.setY(i * BOX_SIZE);
				ge.push_back(enemy);
			}
			if (level.getMap().at(i).at(j) == levelDictionary::PLAYER) {
				player.setX(j * BOX_SIZE);
				player.setY(i * BOX_SIZE);
			}
		}
	}

	//Init Heart List

	for (int i = 0; i < player.playerhp; i++)
	{

		if (!heartList[i].initialize(graphics, heartNS::WIDTH, heartNS::HEIGHT, 0, &heartTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart" + i));

		heartList[i].setX(heartNS::X - (GAME_WIDTH / 16 * (player.playerhp - i)));
		heartList[i].setY(GAME_HEIGHT / 18);

	}
	addEntity(&player, "player", 1);
	addEntity(&enemy, "enemy",1);
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void TestScene::update(float frameTime)
{
	for (size_t i = 0; i < _countof(groundList); i++) {
		if (speedState == 0) {
			groundList[i].setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			groundList[i].setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			groundList[i].setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (groundList[i].getX() <= -BOX_SIZE) {
			groundList[i].setX((_countof(groundList) - 1) * BOX_SIZE);
			distance++;
		}
		groundList[i].update(frameTime);
	}

	//update ground list
	for (size_t i = 0; i < activeGroundList.size(); i++) {
		if (speedState == 0) {
			activeGroundList.at(i).setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			activeGroundList.at(i).setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			activeGroundList.at(i).setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (activeGroundList.at(i).getX() <= -BOX_SIZE) {
			activeGroundList.erase(activeGroundList.begin() + i);
		}
		activeGroundList.at(i).update(frameTime);
	}

	//update killbox List
	for (size_t i = 0; i < activeKillboxList.size(); i++) {
		if (speedState == 0) {
			activeKillboxList.at(i).setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			activeKillboxList.at(i).setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			activeKillboxList.at(i).setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (activeGroundList.at(i).getX() <= -BOX_SIZE) {
			activeKillboxList.erase(activeKillboxList.begin() + i);
		}
		activeKillboxList.at(i).update(frameTime);
	}

	//update nportal List
	for (size_t i = 0; i < activenPortalList.size(); i++) {
		if (speedState == 0) {
			activenPortalList.at(i).setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			activenPortalList.at(i).setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			activenPortalList.at(i).setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (activenPortalList.at(i).getX() <= -BOX_SIZE) {
			activenPortalList.erase(activenPortalList.begin() + i);
		}
		activenPortalList.at(i).update(frameTime);
	}

	//update dsportal List
	for (size_t i = 0; i < activedsPortalList.size(); i++) {
		if (speedState == 0) {
			activedsPortalList.at(i).setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			activedsPortalList.at(i).setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			activedsPortalList.at(i).setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (activedsPortalList.at(i).getX() <= -BOX_SIZE) {
			activedsPortalList.erase(activedsPortalList.begin() + i);
		}
		activedsPortalList.at(i).update(frameTime);
	}

	//update hsportal List
	for (size_t i = 0; i < activehsPortalList.size(); i++) {
		if (speedState == 0) {
			activehsPortalList.at(i).setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			activehsPortalList.at(i).setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			activehsPortalList.at(i).setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (activehsPortalList.at(i).getX() <= -BOX_SIZE) {
			activehsPortalList.erase(activehsPortalList.begin() + i);
		}
		activehsPortalList.at(i).update(frameTime);
	}
	//update speed power up List
	for (size_t i = 0; i < activeSpeedPowerupList.size(); i++) {
		if (speedState == 0) {
			activeSpeedPowerupList.at(i).setVelocity(VECTOR2(-MOVESPEED, 0));
		}
		if (speedState == 1) {
			activeSpeedPowerupList.at(i).setVelocity(VECTOR2(-(MOVESPEED / 2), 0));
		}
		if (speedState == 2) {
			activeSpeedPowerupList.at(i).setVelocity(VECTOR2(-(MOVESPEED * 2), 0));
		}
		if (activeSpeedPowerupList.at(i).getX() <= -BOX_SIZE) {
			activeSpeedPowerupList.erase(activeSpeedPowerupList.begin() + i);
		}
		activeSpeedPowerupList.at(i).update(frameTime);
	}
	playerStateManager(frameTime);
	updateAllEntities(frameTime);
	//update hearts list
	for (int i = 0; i < player.playerhp; i++)
	{
		heartList[i].update(frameTime);
	}
	if (getInput()->wasKeyPressed(VK_SPACE))  //SPACE
	{
		player.damage();
	}
	
	for (int i = 0; i < level.getGroundList().size(); i++) {
		Ground ground = level.getGroundList().at(i);
		ground.update(frameTime);
	}
	for (int i = 0; i < level.getKillboxList().size(); i++) {
		Killbox killbox = level.getKillboxList().at(i);
		killbox.update(frameTime);
	}
	for (int i = 0; i < level.getEnemyList().size(); i++) {
		Enemy enemy = level.getEnemyList().at(i);
		enemy.update(frameTime);
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void TestScene::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void TestScene::collisions()
{
	VECTOR2 cV;

	bool collidedWithGround = false;

	for (size_t i = 0; i < _countof(groundList); i++) {
		if (player.collidesWith(groundList[i], cV))
		{
			// cV is computed by collidesWith


			if (cV.y > 0) {
				playerState = ONGROUND;
			}
			else {
				playerState = ONAIR;
			}
		}
		if (!getInput()->isKeyDown(W_KEY)) {
			if ((player.getY() - groundList[i].getY()) != 0)
				if ((groundList[i].getY() - player.getY()) < (1.5 * BOX_SIZE))
					player.setY(groundList[i].getY() - BOX_SIZE);
		}
	}

	//jumping
	if (getInput()->isKeyDown(W_KEY))            // if W is pressed
	{
		if (playerState == ONGROUND)
			playerState = ONJUMP;
	}

	//if (playerShip.collidesWith(e*, collisionVector))
	//{
	//		e->setScale(0);
	//		e->setActive(false);
	//		if (numOfHits < MAX_HEART_NO)
	//		{
	//			numOfHits++;
	//		}
	//		for (int i = 0; i < numOfHits; i++)
	//		{
	//			heartList[i].setActive(false);
	//		}
	//}
}

//=============================================================================
// Render game items
//=============================================================================
void TestScene::render()
{
	getGraphics()->spriteBegin();                // begin drawing sprites


	for (int g = 0; g < _countof(groundList); g++)
	{
		groundList[g].draw();
	}

	player.draw();
	enemy.draw();

	for (int i = 0; i < player.playerhp; i++)
	{
		heartList[i].draw();
	}

	if (player.playerhp == 0)
	{
		sceneManager->transitionToScene("EXIT_GAME");
	}

	for (int i = 0; i < level.getGroundList().size(); i++) {
		Ground ground = level.getGroundList().at(i);
		ground.draw();
	}
	for (int i = 0; i < level.getKillboxList().size(); i++) {
		Killbox killbox = level.getKillboxList().at(i);
		killbox.draw();
	}
	for (int i = 0; i < level.getEnemyList().size(); i++) {
		Enemy enemy = level.getEnemyList().at(i);
		enemy.draw();
	}

	getGraphics()->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void TestScene::releaseAll()
{
	groundTexture.onLostDevice();
	playerTexture.onLostDevice();
	killboxTexture.onLostDevice();
	enemyTexture.onLostDevice();
	heartTexture.onLostDevice();
	//Scene::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void TestScene::resetAll()
{
	groundTexture.onResetDevice();
	playerTexture.onResetDevice();
	killboxTexture.onResetDevice();
	enemyTexture.onResetDevice();
	heartTexture.onResetDevice();
	//Scene::resetAll();
	return;
}

//=============================================================================
// Player State Manager
//=============================================================================
void TestScene::playerStateManager(float frameTime) {
	if (playerState == ONGROUND) {
		player.setVelY(0);
		if ((player.getDegrees() > 0) && (player.getDegrees() < 90)) {
			player.setDegrees(0);
		}
		if ((player.getDegrees() > 90) && (player.getDegrees() < 180)) {
			player.setDegrees(90);
		}
		if ((player.getDegrees() > 180) && (player.getDegrees() < 270)) {
			player.setDegrees(180);
		}
		if ((player.getDegrees() > 270) && (player.getDegrees() < 360)) {
			player.setDegrees(270);
		}
	}
	if (playerState == ONJUMP) {
		player.setVelY(-JUMP_DY);
		playerState = ONAIR;
	}
	if (playerState == ONAIR) {
		player.setVelY(player.getVelY() + (playerNS::G * frameTime));
		if (player.getDegrees() >= 360) {
			player.setDegrees(player.getDegrees() - 360);
		}
		player.setDegrees(player.getDegrees() + (ROTATION_SPEED * frameTime));
	}
}

//=============================================================================
// Rendering based on grid and block type
// G = Ground, K = Killbox, N = nPortal, D = dsPortal, H = hsPortal, S = SpeedPowerup
//=============================================================================
void TestScene::renderObject(char type, UINT position) {
	Graphics* graphics = getGraphics();
	if (type == 'G') {
		Ground ground;
		if (!ground.initialize(graphics, groundNS::WIDTH, groundNS::HEIGHT, 0, &groundTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground"));
		ground.setX(GAME_WIDTH);
		ground.setY(GAME_HEIGHT - (position * BOX_SIZE));
		activeGroundList.push_back(ground);
	}
	if (type == 'K') {
		Killbox kbox;
		if (!kbox.initialize(graphics, kboxNS::WIDTH, kboxNS::HEIGHT, 0, &killboxTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing killbox"));
		kbox.setX(GAME_WIDTH);
		kbox.setY(GAME_HEIGHT - (position * BOX_SIZE));
		activeKillboxList.push_back(kbox);
	}
	if (type == 'N') {
		nPortal np;
		if (!np.initialize(graphics, npNS::WIDTH, npNS::HEIGHT, 0, &nPortalTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nportal"));
		np.setX(GAME_WIDTH);
		np.setY(GAME_HEIGHT - (position * BOX_SIZE));
		activenPortalList.push_back(np);
	}
	if (type == 'H') {
		hsPortal hsp;
		if (!hsp.initialize(graphics, hspNS::WIDTH, hspNS::HEIGHT, 0, &hsPortalTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hsportal"));
		hsp.setX(GAME_WIDTH);
		hsp.setY(GAME_HEIGHT - (position * BOX_SIZE));
		activehsPortalList.push_back(hsp);
	}
	if (type == 'D') {
		dsPortal dsp;
		if (!dsp.initialize(graphics, dspNS::WIDTH, dspNS::HEIGHT, 0, &dsPortalTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hsportal"));
		dsp.setX(GAME_WIDTH);
		dsp.setY(GAME_HEIGHT - (position * BOX_SIZE));
		activedsPortalList.push_back(dsp);
	}
	if (type == 'S') {
		SpeedPowerup spu;
		if (!spu.initialize(graphics, spuNS::WIDTH, spuNS::HEIGHT, 0, &speedPowerupTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing speed power up"));
		spu.setX(GAME_WIDTH);
		spu.setY(GAME_HEIGHT - (position * BOX_SIZE));
		activeSpeedPowerupList.push_back(spu);
	}
	return;
}

// ===========================================================================
// clean up scene objects and prepare to transit out of scene
// ===========================================================================
void TestScene::cleanup()
{
	// reset bg color
	getGraphics()->setBackColor(BLACKNESS);

}