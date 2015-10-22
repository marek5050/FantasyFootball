/*
 * Play.h
 *
 *  Created on: Dec 1, 2014
 *      Author: marekbejda
 */

#ifndef PLAY_H_
#define PLAY_H_
#include "string"
#include "list"

using namespace std;
//#include "Players.h"
//class Players;

class Drive;

using namespace std;
class PlayPoints;

class Play {
public:
	int sp;
	int qtr;
	int down;
	string time;
	string yrdln;
	string ydstogo;
	string ydsnet;
	string posteam;
	string desc;
	string note;
	list<string> _players;
	list <PlayPoints *> playPoints;
	int fds;

	void parsePlay(string);
	Play();
	virtual ~Play();
};


#endif /* PLAY_H_ */
