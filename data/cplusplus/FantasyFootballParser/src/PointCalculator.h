/*
 * PointCalculator.h
 *
 *  Created on: Dec 6, 2014
 *      Author: marekbejda
 */

#ifndef SRC_POINTCALCULATOR_H_
#define SRC_POINTCALCULATOR_H_
#include "string"
#include <iostream>

using namespace std;

class PlayPoints;

class PointCalculator {

public:

	void playType(string *, PlayPoints *);
	double play(string *);
	PointCalculator();
	virtual ~PointCalculator();
};

#endif /* SRC_POINTCALCULATOR_H_ */
