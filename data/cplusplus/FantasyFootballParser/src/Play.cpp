/*
 * Play.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: marekbejda
 */

#include "Play.h"

#include <string>
#include <sstream>
#include <iostream>
#include "map"

using namespace std;


Play::Play() {
	// TODO Auto-generated constructor stub
	sp=0;
	qtr=0;
	down=0;
	fds=0;
	time="";
	yrdln="";
	ydstogo="";
	ydsnet="";
	posteam="";
	desc="";
	note="";
}

Play::~Play() {
	// TODO Auto-generated destructor stub
}

void Play::parsePlay(string s){

//	cout<< "PLAY: ";
//	cout << "Play::parsePlay::"<<s<<endl;

	int i = 1;
	int exit = 0;
	int loc  = 0 , next = 0;
	int start = 0 , end = 0;

	string posteam;

//	Players *p;
	string *p;
	int count = 0;

	start = s.find("\"posteam\":")+11;
	end = s.find("\",",start);
	posteam = s.substr(start,end - start);

	start = s.find("\"desc\":")+8;
	end = s.find("\"",start);
	this->desc = s.substr(start, end - start);
	int print = 0 ;
//	cout << posteam <<  " : " << desc << endl;
	string pl;
	while(exit == 0){
		count ++ ;
		loc = s.find("\"clubcode\":");
		next = s.find("}", loc);

		if(loc != -1 && next != -1){
//			p = &_players[i];
//			p->parsePlayer(s.substr(loc,next-loc));
			pl = string(s.substr(loc,next-loc));

			_players.push_back(pl);
		}else{
//			_players.push_back( s.substr(loc));
			exit = 1;
//			cout << "Finished" << endl;
		}
		s = s.substr(next+1);
	}

}

/*
// {"36":
//	{
//	"sp":0,
//	"qtr":1,
//	"down":0,
//	"time":"15:00",
//	"yrdln":"SEA 35",
//	"ydstogo":0,
//	"ydsnet":0,
//	"posteam":"SEA",
//	"desc":"S.Hauschka kicks 71 yards from SEA 35 to GB -6. D.Harris to GB 13 for 19 yards (M.Morgan).",
//	"note":"KICKOFF",
//	"players":{
//			"00-0028443":[{"sequence":4,"clubcode":"SEA","playerName":"M.Morgan","statId":79,"yards":0}],
//			"00-0028409":[{"sequence":2,"clubcode":"GB","playerName":"D.Harris","statId":45,"yards":19}],
//	 		"00-0025944":[
//	 					 {"sequence":1,"clubcode":"SEA","playerName":"S.Hauschka","statId":43,"yards":71},
//	 					 {"sequence":3,"clubcode":"SEA","playerName":"S.Hauschka","statId":42,"yards":0}]
//	 		}
//	}
*/
