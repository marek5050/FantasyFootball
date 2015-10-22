/*
 * PlayPoints.h
 *
 *  Created on: Dec 6, 2014
 *      Author: marekbejda
 */

#ifndef SRC_PLAYPOINTS_H_
#define SRC_PLAYPOINTS_H_
#include "string"
#include "iostream"

#include "enums.h"
using namespace std;

class Players;

class PlayPoints {
public:

	Players *player;
	double pts;
	STAT type;
	string *info;

	PlayPoints(Players *, double, string*);
	virtual ~PlayPoints();
};

#endif /* SRC_PLAYPOINTS_H_ */
