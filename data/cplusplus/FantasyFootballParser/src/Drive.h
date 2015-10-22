/*
 * Drive.h
 *
 *  Created on: Dec 1, 2014
 *      Author: marekbejda
 */

#ifndef DRIVE_H_
#define DRIVE_H_
//#include "Play.h"
#include "list"
#include "string"
#include "Play.h"

using namespace std;

class Drive {
public:
	list<Play *> plays;
	string result;
	int penyds;
	int numplays;
	string posteam;

	int getDriveCount();
	void parseDrive(string);
	Drive();
	virtual ~Drive();
};


#endif /* DRIVE_H_ */
