/*
 * Game.h
 *
 *  Created on: Dec 1, 2014
 *      Author: marekbejda
 */

#ifndef GAME_H_
#define GAME_H_
//#include "Drive.h"
#include "list"
#include "Drive.h"
using namespace std;

//#include "Team.h"
//class Team;
//class Drive;
//struct Team;

class Game {
public:
	string home;
	string away;
	list<Drive *> drives;
	void parseDrives(string);
	void configurePlays();

	Game();
	virtual ~Game();
};

#endif /* GAME_H_ */
