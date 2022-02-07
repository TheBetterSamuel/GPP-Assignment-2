// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment1:		Cheats:Enabled
// Student Name:	Tang Ming Feng
// Student No.:		S10185023E
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// InkdotEngine -  Load Scene Class Implementation
// ===========================================================================

// include specification
#include "loadscene.h"

// ===========================================================================
// default constructor
// ===========================================================================
LoadScene::LoadScene() :

	// text states
	HUDText(),

	// texture states

	hud1Texture(),
	hud2Texture(),
	win(),



	// game logic
	coinCount(0),
	playerVelocity(100),

	// timer
	seconds(0),
	minutes(0),

	// player pointer
	playerptr(NULL)
{}

// ===========================================================================
// default destructor
// ===========================================================================
LoadScene::~LoadScene() {}


// scene methods

// ===========================================================================
// set up scene objects during scene initialization
// ===========================================================================
void LoadScene::initialize(string fileName)
{
	// configure scene
	getGraphics()->setBackColor(graphicsNS::YELLOW);

	// initialize text fonts

	if (!HUDText.initialize(
		getGraphics(),
		13,
		true,
		false,
		"Terminal"
	)) throw (
		GameError(
			gameErrorNS::FATAL_ERROR,
			"Error initializing hud font!"
		)
		);

	if (!pauseText.initialize(
		getGraphics(),
		13,
		true,
		false,
		"Terminal"
	)) throw (
		GameError(
			gameErrorNS::FATAL_ERROR,
			"Error initializing pause font!"
		)
		);

	// initialize textures


	// hud's
	if (!hud1Texture.initialize(
		getGraphics(),
		"./assets/HUD.png"
	))
		throw(
			GameError(
				gameErrorNS::FATAL_ERROR,
				"Error initializing HUD texture!"
			));

	if (!hud2Texture.initialize(
		getGraphics(),
		"./assets/HUD.png"
	))
		throw(
			GameError(
				gameErrorNS::FATAL_ERROR,
				"Error initializing HUD texture!"
			));

	// initialize objects

	Player* player = new Player();
	TextureManager* playerTexture = new TextureManager();
	playerTexture->initialize(getGraphics(),
		"player.jpg");
	player->initialize(getGraphics(), playerNS::WIDTH, playerNS::HEIGHT, 0, playerTexture);
	/*player->setScale(0.5);*/
	player->setX(3 * BOX_SIZE);
	player->setY(GAME_HEIGHT - (2 * BOX_SIZE));
	std::string level = FileUtils::readFromFile(fileName);
	//convertStringToLevel(entityManager, "WALL,500,150,320,10\nWALL,0,330,320,10\nSPAWN_PLAYER,500,100,10,10\nTURRET_SPAWNL,550,400,5,5\nCOIN,200,200,5,5\nSPAWN_HUNTER,400,300,5,5\nSPIKES,300,300,5,5\nGOAL,50,450,10,10", player);
	//convertStringToLevel(entityManager, "WALL,500,150,320,10\nWALL,0,330,320,10\nSPAWN_PLAYER,500,100,10,10\nCOIN,200,200,5,5\nSPAWN_HUNTER,400,300,5,5\nGOAL,50,450,10,10", player);
	convertStringToLevel(level, player);
	playerptr = player;

}

// ===========================================================================
// clean up scene objects and prepare to transit out of scene
// ===========================================================================
void LoadScene::cleanup()
{
	// reset bg color
	getGraphics()->setBackColor(graphicsNS::BACK_COLOR);
}

// ===========================================================================
// update objects for each frame
// ===========================================================================
void LoadScene::update(
	float	prevFrameTime
) {


	// timer
	seconds += prevFrameTime;
	if (seconds >= 60) {

		// increment minutes
		minutes++;
		seconds = 0;
	}

	//entityManager.updateAllEntities(prevFrameTime);
}
//=============================================================================
// Artificial Intelligence
//=============================================================================
void LoadScene::ai() {}
// ===========================================================================
// handle collisions for objects on each frame
// ===========================================================================
void LoadScene::collisions()
{
	VECTOR2 collisionVector;

	//if (player.getCollider("sprite")->collidesWith(
	//	*coin1.getCollider("sprite"),
	//	collisionVector
	//)) {
	//	coinCount += 1;
	//	coin1.setActive(0);
	//}

	//if (player.getCollider("sprite")->collidesWith(
	//	*enemy1.getCollider("sprite"),
	//	collisionVector
	//)) {
	//	player.bounce(collisionVector, enemy1);
	//}

	//if (player.getCollider("sprite")->collidesWith(
	//	*turret1.getCollider("sprite"),
	//	collisionVector
	//)) {
	//	player.bounce(collisionVector, enemy1);
	//}

	//if (player.collidesWithTaggedEntities(
	//	"sprite",
	//	"bullet",
	//	collisionList
	//)) {

	//	InkdotEntity* e;

		// handle each collision in collision list
		//for (size_t i = 0; i < collisionList.size(); i++) {

		//	e = entityManager.getEntity(std::get<2>(collisionList[i]));

		//	// bounce off collision vector
		//	player.bounce(
		//		std::get<0>(collisionList[i]),
		//		*e
		//	);

		//	// kill bullet
		//	e->setActive(FALSE);

		//	//enemy2.setActive(0);
		//	//enemy2.setVisible(0);
		//}
	//}
}

// ===========================================================================
// render sprites for scene foreground: draws over entity sprites
// ===========================================================================
void LoadScene::render()
{
	// draw HUD
	HUDText.print(
		"Time: " +
		std::to_string(int(minutes)) +
		":" +
		std::to_string(int(seconds)),
		10, 30);


}

// ===========================================================================
// releases all memory reserved for graphics objects so that the bound
// graphics device can be reset. called when the graphics device is lost.
// ===========================================================================
void LoadScene::releaseAll()
{

}

// ===========================================================================
// recreates and restores all graphics objects. called after a lost
// graphics device is restored.
// ===========================================================================
void LoadScene::resetAll()
{

}


void LoadScene::convertStringToLevel(std::string s, Player* player) {

	/*std::vector<std::string> rows = LoadScene::split_string_by(s, '\n');
	for (int i = 0; i < rows.size(); i++) {
		std::vector<std::string> cols = LoadScene::split_string_by(rows[i], ',');
		if (cols[0] == "WALL") {
			Wall* wall = new Wall();
			wall->initialize(std::stof(cols[1]), std::stof(cols[2]), std::stof(cols[3]), std::stof(cols[4]));
			entityManager.getGraphics()->drawPrimitiveRect(
				std::stof(cols[1]),
				std::stof(cols[2]),
				std::stof(cols[3]) * 2,
				std::stof(cols[4]) * 2,
				CommonColors::WHITE,
				CommonColors::WHITE,
				0);
			wall->setCenter(VECTOR2(std::stof(cols[1]), std::stof(cols[2])));
			entityManager.addEntity(wall, 0);
		}
		else if (cols[0] == "SPAWN_PLAYER") {
			player->setCenter(VECTOR2(
				std::stof(cols[1]),
				std::stof(cols[2])
			));

		}

	}*/
}

//std::vector<std::string> LoadScene::split_string_by(const std::string& str, char delim)
//{
//	auto result = std::vector<std::string>{};
//	auto ss = std::stringstream{ str };
//
//	for (std::string line; std::getline(ss, line, delim);)
//		result.push_back(line);
//
//	return result;
//}
