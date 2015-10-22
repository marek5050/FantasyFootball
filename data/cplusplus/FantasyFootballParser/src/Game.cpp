/*
 * Game.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: marekbejda
 */
#include "Game.h"
#include <iostream>
#include <sstream>
//
using namespace std;

Game::Game() {
	// TODO Auto-generated constructor stub
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

string make_string( int i)
{
    ostringstream result;
    result << "\"" << i <<  "\"";
    return result.str();
}
//void Game::configurePlays(){
//
//	int i =0 ;
//	string team="";
//	for (list<Drive *>::iterator it=drives.begin(); it!=drives.end(); ++it){
//		cout << (*it)->posteam << endl;
//		team = (*it)->posteam;
//
////		if(team == home->name){
////			cout<< "Home: "<< team << " " << home << endl;
////		}else{
////			cout<< "AWAY: "<< team << " " << away << endl;
////		}
//
//
//	}
//}

void Game::parseDrives(string s){
//	cout << "Game::parseDrives" << s << endl;
	string str = s;
	string search="";
	int i = 1;
	int exit =0;
	int loc = 0,next = 0;
	Drive *d;
	while(exit == 0){
		d = new Drive();
		loc = str.find(make_string(i++));
		if(loc != -1){
			next = str.find(make_string(i));
			if(next !=-1){
				d->parseDrive(str.substr(loc,next-loc));
			}else{
				d->parseDrive(str.substr(loc));
				exit =1;
			}
			drives.push_back(d);
			//cout << "FOUND: " << make_string(i) << ": " << loc << endl;
		}
	}
}
//"1":{"posteam":"GB","qtr":1,"redzone":true,"plays":
//{"36":
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
//	},
//"58":{"sp":0,"qtr":1,"down":1,"time":"14:56","yrdln":"GB 13","ydstogo":10,"ydsnet":6,"posteam":"GB","desc":"(14:56) E.Lacy right tackle to GB 19 for 6 yards (K.Williams).","note":null,"players":{"00-0022073":[{"sequence":2,"clubcode":"SEA","playerName":"K.Williams","statId":79,"yards":0}],"00-0030485":[{"sequence":1,"clubcode":"GB","playerName":"E.Lacy","statId":10,"yards":6}]}},"79":{"sp":0,"qtr":1,"down":2,"time":"14:30","yrdln":"GB 19","ydstogo":4,"ydsnet":11,"posteam":"GB","desc":"(14:30) E.Lacy left tackle to GB 22 for 3 yards (C.Avril, K.Wright). PENALTY on SEA-M.Bennett, Defensive Offside, 5 yards, enforced at GB 19 - No Play.","note":"PENALTY","players":{"0":[{"sequence":1,"clubcode":"GB","playerName":"","statId":5,"yards":0}],"00-0026618":[{"sequence":2,"clubcode":"SEA","playerName":"M.Bennett","statId":93,"yards":5}]}},"111":{"sp":0,"qtr":1,"down":1,"time":"14:11","yrdln":"GB 24","ydstogo":10,"ydsnet":26,"posteam":"GB","desc":"(14:11) (Shotgun) E.Lacy up the middle to GB 39 for 15 yards (B.Wagner).","note":null,"players":{"00-0030485":[{"sequence":2,"clubcode":"GB","playerName":"E.Lacy","statId":10,"yards":15}],"0":[{"sequence":1,"clubcode":"GB","playerName":"","statId":3,"yards":0}],"00-0029255":[{"sequence":3,"clubcode":"SEA","playerName":"B.Wagner","statId":79,"yards":0}]}},"132":{"sp":0,"qtr":1,"down":1,"time":"13:32","yrdln":"GB 39","ydstogo":10,"ydsnet":28,"posteam":"GB","desc":"(13:32) (No Huddle) J.Starks right guard to GB 41 for 2 yards (K.Chancellor, K.Wright).","note":null,"players":{"00-0027733":[{"sequence":2,"clubcode":"SEA","playerName":"K.Chancellor","statId":80,"yards":0}],"00-0027791":[{"sequence":1,"clubcode":"GB","playerName":"J.Starks","statId":10,"yards":2}],"00-0028037":[{"sequence":3,"clubcode":"SEA","playerName":"K.Wright","statId":82,"yards":0}]}},"153":{"sp":0,"qtr":1,"down":2,"time":"13:06","yrdln":"GB 41","ydstogo":8,"ydsnet":26,"posteam":"GB","desc":"(13:06) (Shotgun) A.Rodgers pass short left to J.Nelson to GB 39 for -2 yards (K.Wright).","note":null,"players":{"00-0028037":[{"sequence":6,"clubcode":"SEA","playerName":"K.Wright","statId":79,"yards":0},{"sequence":7,"clubcode":"SEA","playerName":"K.Wright","statId":120,"yards":0},{"sequence":8,"clubcode":"SEA","playerName":"K.Wright","statId":402,"yards":2}],"00-0023459":[{"sequence":1,"clubcode":"GB","playerName":"A.Rodgers","statId":15,"yards":-2},{"sequence":2,"clubcode":"GB","playerName":"A.Rodgers","statId":111,"yards":-2}],"00-0026176":[{"sequence":3,"clubcode":"GB","playerName":"J.Nelson","statId":21,"yards":-2},{"sequence":4,"clubcode":"GB","playerName":"J.Nelson","statId":115,"yards":0},{"sequence":5,"clubcode":"GB","playerName":"J.Nelson","statId":113,"yards":0}]}},"177":{"sp":0,"qtr":1,"down":3,"time":"12:30","yrdln":"GB 39","ydstogo":10,"ydsnet":26,"posteam":"GB","desc":"(12:30) (Shotgun) A.Rodgers sacked at GB 39 for 0 yards (O.Schofield).","note":null,"players":{"0":[{"sequence":1,"clubcode":"GB","playerName":"","statId":7,"yards":0}],"00-0027730":[{"sequence":3,"clubcode":"SEA","playerName":"O.Schofield","statId":83,"yards":0},{"sequence":4,"clubcode":"SEA","playerName":"O.Schofield","statId":110,"yards":0},{"sequence":5,"clubcode":"SEA","playerName":"O.Schofield","statId":79,"yards":0}],"00-0023459":[{"sequence":2,"clubcode":"GB","playerName":"A.Rodgers","statId":20,"yards":0}]}},
//"196":{
//	"sp":0,
//	"qtr":1,
//	"down":4,
//	"time":"11:57",
//	"yrdln":"GB 39",
//	"ydstogo":10,
//	"ydsnet":26,
//	"posteam":"GB",
//	"desc":"(11:57) T.Masthay punts 29 yards to SEA 32, Center-B.Goode. E.Thomas to SEA 35 for 3 yards (S.Richardson).",
//	"note":"PUNT",
//	"players":{
//		"00-0029201":[{"sequence":3,"clubcode":"GB","playerName":"S.Richardson","statId":79,"yards":0}],
//		"00-0026664":[{"sequence":1,"clubcode":"GB","playerName":"T.Masthay","statId":29,"yards":29}],
//		"00-0027866":[{"sequence":2,"clubcode":"SEA","playerName":"E.Thomas","statId":33,"yards":3}]}}}
//	,"fds":2,"result":"Punt","penyds":5,"ydsgained":21,"numplays":8,"postime":"3:07",
//"start":{"qtr":1,"time":"15:00","yrdln":"GB 13","team":"GB"},"end":{"qtr":1,"time":"11:53","yrdln":"GB 39","team":"GB"}
//}
