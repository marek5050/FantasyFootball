/*
 * Players.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: marekbejda
 */

#include "Players.h"

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

Players::Players() {
	// TODO Auto-generated constructor stub
	idx="";
	seq=0;
	FL=0;
	Int=0;
	PaY=0;
	ReY=0;
	Re=0;
	RuY=0;
	 ReTD=0;
	 RuTD=0;
	 PaTD=0;
	 other=0;
	 points=0;
	 avg=0;
	 cost=0;
	 info=0;
	 starts=0;
}

Players::~Players() {
	// TODO Auto-generated destructor stub
}

void Players::updateStats(PlayPoints *ptps){
	string *play = ptps->info;
//	cout << "Player: " << this->name_hash << " desc: " << *play << endl;

	int start = play->find("\"statId\":");
	int end = play->find(",",start);
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
//
//	int FL;
//	int Int;
//	int PaY;
//	int ReY;
//	int Re;
//	int RuY;
//	int ReTD;
//	int RuTD;
//	int PaTD;

	  switch(statId){
	  case 7:
	  case 6:
	  case 5:
	  case 4:
	  case 3:
	  case 20:
	  case 8:
	  case 9:
		  	  break;

	  case 11:
	  case 13: RuTD++;
	  case 10:
	  case 12: RuY+=yards;
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
	  case 16: PaTD++;
	  case 17:
	  case 15: PaY+=yards;
	  	  	   break;

	  case 19: Int++;
	  	  	   break;

	  case 22: ReTD++;
	  case 21: ReY+=yards;
 		  	   break;

	  case 106: FL++;
	  	  	    break;

	  case 70:
		  	  if(yards >= 50) other = 5;
		  	  else if(yards >= 40) other = 4;
		  	  else other = 3;
		  	  break;

	  default:
		  ;
//		  PaTD++;
//		  cout << "DID NOT MATCH: "<< statId << " in " << *play << endl;
	  }
}

void Players::parsePlayer(string s){
	//cout << "Players::parsePlayer:: "  << s << endl;
//	string str = s.substr(s.find("\"plays\":"));
//	string search="";
	int start = 0, end = 0;

	start = s.find("\"clubcode\"")+11;
	end = s.find("\"",start);
	clubcode = s.substr(start,end-start);
//	cout << clubcode << endl;


	start = s.find("null");
	end = s.find("\"\"");

	if(start != -1 || end != -1){
			return;
	}
//	cout << "SEQ,";

	start = s.find("\"playerName\"")+13;
	end = s.find("\"",start);
	playerName = s.substr(start, end - start);
//	cout <<"1 "<< playerName << endl;

	start = s.find("\"statId\"")+9;
	end = s.find(",",start);
//	cout<<"2 "<< statId << endl;

	start = s.find("\"yards\"")+8;
	string _yards = s.substr(start);

//	cout << this-> clubcode << "," << this->playerName << "," << this->statId << "," << this->yards << endl;
}

/*
// {"sequence":4,"clubcode":"SEA","playerName":"M.Morgan","statId":79,"yards":0}
//	"players":{
//			"00-0028443":[],
//			"00-0028409":[{"sequence":2,"clubcode":"GB","playerName":"D.Harris","statId":45,"yards":19}],
//	 		"00-0025944":[
//	 					 {"sequence":1,"clubcode":"SEA","playerName":"S.Hauschka","statId":43,"yards":71},
//	 					 {"sequence":3,"clubcode":"SEA","playerName":"S.Hauschka","statId":42,"yards":0}]
//	 		}
//	}
*/
