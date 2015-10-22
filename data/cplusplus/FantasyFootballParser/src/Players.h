/*
 * Players.h
 *
 *  Created on: Dec 1, 2014
 *      Author: marekbejda
 */


#ifndef PLAYERS_H_
#define PLAYERS_H_
#include <string>

using namespace std;
#include "PlayPoints.h"
class Team;

class Players {

public:
	string name_hash;
	string clubcode;
	string playerName;
	string position;
	string name;
	string team;
	string id;
	string r;
	string l;

	string idx;
	int seq;
	int FL;
	int Int;
	double PaY;
	double ReY;
	int Re;
	double RuY;
	int ReTD;
	int RuTD;
	int PaTD;
	int other;
	double points;
	int avg;
	int cost;
	int info;
	int starts;

	void parsePlayer(string);
	void updateStats(PlayPoints *);
	Players();
	virtual ~Players();
};

#endif /* PLAYERS_H_ */
