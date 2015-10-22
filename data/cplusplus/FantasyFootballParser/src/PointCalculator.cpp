/*
 * PointCalculator.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: marekbejda
 */

#include "PointCalculator.h"

PointCalculator::PointCalculator() {
	// TODO Auto-generated constructor stub

}

PointCalculator::~PointCalculator() {
	// TODO Auto-generated destructor stub
}

void passingYards (){

}

void rushingYards(){

}

void receptionYards(){

}

void touchdown(){

}

double PointCalculator::play(string *play){
	int start = play->find("\"statId\":");
	int end = play->find(",",start);
	double pts = 0.0;
	int yards = 0;

	int statId= 0 ;
	if(start != - 1 &&  end != -1 ){
		statId = stoi(play->substr(start+9,end - start));
	}

	start = play->find("\"yards\":");

	if(start!=-1)
		yards = stoi(play->substr(start+8));

	//	Offense:
	//	Rushing yards made = 0.1pts
	//	Rushing touchdowns = 6pts
	//	Passing yards = 0.04pts
	//	Passing touchdowns = 4pts
	//	Interceptions = -1pt
	//	Receiving yards = 0.1pts
	//	Receiving touchdowns = 6pts
	//	Receptions = 0.5pts

	  switch(statId){
	  case 7:
	  case 6:
	  case 5:
	  case 4:
	  case 3:
	  case 8:
	  case 9:
		  	  break;
	  case 11:
	  case 13: pts = 6;
	  case 10:
	  case 12: pts += yards * 0.1;
	  	  	  break;

	  case 24:
	  case 26:
	  case 28:
	  case 58:
	  case 60:
	  case 62:
	  case 64:
	  case 108:
  	  	  	  break;
	  case 18:
	  case 16: pts = 4;
	  case 17:
	  case 15: pts += yards * 0.04;
	  	  	   break;

	  case 19: pts = -1;
	  	  	   break;

	  case 22: pts = 6;
	  case 21:
		  	   pts += yards * 0.1;
 		  	   break;

	  case 106: pts = -2;
	  	  	    break;
	  case 70:
		  	  if(yards >= 50) pts = 5;
		  	  else if(yards >= 40) pts = 4;
		  	  else pts = 3;
		  	  break;

	  case 72:
	  case 96:
		  	  pts = 1;
		  	  break;

	  case 113:
		  	  pts = 0.5;
		  	  break;

	  default:
		  	  ;
//		cout << "DID NOT MATCH: "<< statId << " in " << *play << endl;
	  }

	//	Kickoff return touchdowns = 6pts
	//	Punt return touchdowns = 6pts
	//	Fumbles lost = -2pts
	//	Own fumbles recovered touchdowns = 6pts
	//	Two-point conversions scored = 2pts
	//	Two-point conversion passes = 2pts
	//	Field-goals from 0-19 yards = 3pts
	//	Field-goals from 20-29 yards = 3pts
	//	Field-goals from 30-39 yards = 3pts
	//	Field-goals from 40-49 yards = 4pts
	//	Field-goals from 50+ yards = 5pts
	//	Extra-point conversions = 1ptDefense:
	//	Sacks = 1pt
	//	Opponent-fumbles recovered = 2pts
	//	Return touchdowns = 6pts
	//	Fumble return touchdowns = 6pts
	//	Safeties = 2pts
	//	Blocked kicks = 2pts
	//	Interceptions made = 2pts
	//	0 points allowed = 10pts
	//	1-6 points allowed = 7pts
	//	7-13 points allowed = 4pts
	//	14-20 points allowed = 1pt
	//	28-34 points allowed = -1pt
	//	35+ points allowed = -4pts
	//	Notes: For purposes of FanDuel defensive scoring, points allowed are calculated as: 6 * (Rushing TD + Receiving TD + Own fumbles recovered for TD ) + 2 * (Two point conversions) + Extra points + 3 * (Field Goals). Blocked punt return touchdowns are excluded from defensive scoring.

return pts;

}



