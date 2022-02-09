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

using namespace std;

//defining what each character in the csv data file represents
namespace levelDictionary {
	const string GROUND = "G";
	const string KILLBOX = "K";
	const string START = "S";
	const string END = "E";
}
class Level
{
protected:
	vector <vector<string>> map;

public:
	// constructor
	Level();
	// Destructor
	virtual ~Level() {}

	///get map
	virtual const vector <vector<string>> getMap() {
		return map;
	}

	//load data
	virtual const void loadData(string filePath) {}

	//clear map
	virtual const void clearMap() {}
};

#endif

