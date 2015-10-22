/*
 * Team.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: marekbejda
 */

#include "Team.h"
#include "string"
#include <iostream>


Team::Team() {
	// TODO Auto-generated constructor stub

}

Team::~Team() {
	// TODO Auto-generated destructor stub
}

void Team::addGame(Game *g){
	games.push_front(g);
}

void Team::addPlayer(Players *p){
	players.push_front(p);
}
