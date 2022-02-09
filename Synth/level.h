#ifndef _LEVEL_H            // Prevent multiple definitions if this 
#define _LEVEL_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//-----------------------------------------------
//                  Level Class
//	- Stores the data fpr loading levels into the game
//-----------------------------------------------
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream> 
#include <sstream>
#include "player.h"
#include "ground.h"
#include "killbox.h"
#include "nportal.h"
#include "dsportal.h"
#include "hsportal.h"
#include "speedPowerup.h"
#include "enemy.h"

using namespace std;

//defining what each character in the csv data file represents
namespace levelDictionary {
	const string GROUND = "G";
	const string KILLBOX = "K";
	const string PLAYER = "P";
	const string FINISH = "F";
	const string ENEMY = "E";
	const string SPEEDPOWERUP = "S";
}
class Level
{
protected:
	vector <vector<string>> map;
	vector <Ground> groundList;
	vector <Killbox> killboxList;
	vector <Enemy> enemyList;
	vector <SpeedPowerup> speedpowerupList;

public:
	// constructor
	Level();
	// Destructor
	virtual ~Level();

	//get map
	virtual const vector <vector<string>> getMap() {
		return map;
	}

	//load data
	virtual const void loadData(string filePath);

	//clear map
	virtual const void clearMap();

	// get for all vectors
	virtual const vector <Ground> getGroundList() {
		return groundList;
	}
	virtual const vector <Killbox> getKillboxList() {
		return killboxList;
	}
	virtual const vector <Enemy> getEnemyList() {
		return enemyList;
	}
	virtual const vector <SpeedPowerup> getSpeedpowerupList() {
		return speedpowerupList;
	}

	//set for all vectors
	virtual const void setGroundList(vector <Ground> v) {
		groundList = v;
		return;
	}
	virtual const void setKillboxList(vector <Killbox> v) {
		killboxList = v;
		return;
	}
	virtual const void setEnemyList(vector <Enemy> v) {
		enemyList = v;
		return;
	}
	virtual const void setGroundList(vector <SpeedPowerup> v) {
		speedpowerupList = v;
		return;
	}
};

#endif

