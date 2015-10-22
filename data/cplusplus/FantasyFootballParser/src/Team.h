/*
 * Team.h
 *
 *  Created on: Dec 4, 2014
 *      Author: marekbejda
 */

#ifndef SRC_TEAM_H_
#define SRC_TEAM_H_
#include "map"
//#include "Game.h"
//#include "Play.h"

#include "string"
#include "list"

class Players;
class Game;

using namespace std;
class Play;

class Team {
public:
	string name;
	string name_hash;

	list<Players *> players;
	list<Game *> games;
	list<Play *> plays;

	Team();
	virtual ~Team();
	void addGame(Game *);
	void addPlayer(Players *);
};

#endif /* SRC_TEAM_H_ */
