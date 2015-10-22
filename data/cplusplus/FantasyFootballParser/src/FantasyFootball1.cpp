#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include "map"
#include "vector"

#include "PointCalculator.h"
#include "enums.h"
#include "Game.h"
#include "Team.h"
#include "Players.h"
#include "PlayPoints.h"


using namespace std;

int gameCount=0;

static list<Game *> games;
static std::map<std::string, Team> teams;
std::map<std::string, Players> players;

ostream& operator<<(ostream& os, const Players& dt) {
	os << dt.position << dt.idx << "," << dt.name << ',' << dt.cost;
	return os;
}

void directory() {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(".")) != nullptr) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != nullptr) {
			printf("%s\n", ent->d_name);
		}
		closedir(dir);
	} else {
		/* could not open directory */
		perror("");
		return;
	}
}

void readInSalaries() {
	string filename = "data/FanDuel_2014_Week_13_Salaries.json";
	string output = "Fantasy_Week13_Salaries.csv";
	ifstream myfile(filename);
	ofstream myout(output);

	string line;

	if (myfile.is_open()) {

		getline(myfile, line);
	}

	string text = "", info = "";

	int exit = 0, count = 0, start=0, end=0;

	// 	POS, NAME, ID, GAMES, S1,PRICE,
	//  "21939":["QB","Andrew Luck","86889","10","1000","10300",26,"10",false,4,"","recent",""]

	Players *hash;
	string position, name, id, l, _initial;
	int cost, avg;

	while (exit == 0) {
		position=name=id=l=_initial="";
		avg=cost=0;

		start = line.find("[");
		end = line.find("]");

		text = line.substr(start + 1, end - (start + 1));
		info = text;
		line = line.substr(end + 1);
		if(info.size() < 10){
			break;

		}

		position = info.substr(1, info.find(",") - 2);
		info = info.substr(info.find(",") + 1);

//		cout << "1: " << s1->position << " INFO: " << info <<endl;

		name = info.substr(1, info.find(",") - 2);
		info = info.substr(info.find(",") + 1);

//		cout << "2: " << name  <<endl;

		id = info.substr(1, info.find(",") - 1);
		info = info.substr(info.find(",") + 1);

//		cout << "3: " << s1->id  << " INFO: " << info <<endl;

//		->l = info.substr(1, info.find(",") - 1);
		info = info.substr(info.find(",") + 1);
		info = info.substr(info.find(",") + 1);

		cost = stoi(info.substr(1, info.find(",") - 1), 0, 10);
		info = info.substr(info.find(",") + 1);
//		cout << "5: " << s1->cost  << " INFO: " << info <<endl;

		avg = stoi(info.substr(0, info.find(",")), 0, 10);
		info = info.substr(info.find(",") + 1);

		//		cout << "6: " << s1->avg  << " INFO: " << info <<endl
		int second = name.find(".", name.find(" "));

		if(second!= -1){
			second = name.find(" ", name.find(" ")+1);
			cout << "Found Period " << name;
			name = name.substr(0,second);
			cout << " : " << name <<endl;
		}
		_initial = name.substr(0,1) +"."+ name.substr(name.find(" ")+1);

//		cout << "INITIAL1 : " << _initial << " NAME:  " << name << endl;

		players[_initial].avg = avg;
		players[_initial].cost = cost;
		players[_initial].name = string(name);
		players[_initial].position = string(position);
		count++;
	}

	myout.close();
	myfile.close();
}

void readRankings(string filename) {
	ifstream myfile(filename);
	string line;
	string previous;
	string info;
	int count = 0;

	string position, name, id, l, _initial, idx;
	int cost, avg;

	string text = "";

	Players *hash;
	string prefix ="";
	if (myfile.is_open()) {

		while (getline(myfile, line)) {
			if (count < 6) {
				int end =line.find(" Rankings");
				int start = line.find("Week")+10;
			//	cout << "RANKINGS: " << start << end << endl;
				if(end!=-1 && end > start && prefix==""){
					prefix = line.substr(start,end-start);
				}
				count++;
				continue;
			}
			info = line;
//			cout <<  " INFO : " << info << endl;

			idx = info.substr(0, info.find(","));
			info = info.substr(info.find(",") + 1);


			name = info.substr(0, info.find(","));
			info = info.substr(info.find(",") + 1);


			int second = name.find(".", name.find(" "));

			if(second!= -1){
				second = name.find(" ", name.find(" ")+1);
				cout << "Found Period " << name;
				name = name.substr(0,second);
				cout << " : " << name <<endl;
			}


			string team =  info.substr(0, info.find(","));
			info = info.substr(info.find(",") + 1);

//			if(teams.find(team)!= teams.end()){
////				s1->team = &(teams[team]);
//			}else{
//				cout << "Did not find a valid team for : "<< team << endl;
//				cout << "LINE: " << info << endl;
//			}

			id = info.substr(0, info.find(","));
			info = info.substr(info.find(",") + 1);

			_initial = name.substr(0,1) +"."+ name.substr(name.find(" ")+1);
//			cout << "INITIAL_RANKING: " << _initial << " NAME: " << name << endl;


			if(players.find(_initial) == players.end()){
				cout << "NOT Found player:" << name <<";"<< _initial << endl;

			}else{
				hash = &players[_initial];
				hash->team = team;
				hash->position = prefix;
				hash->idx = idx;
				hash->name_hash = _initial;
//				cout <<"NAME: " << hash->name_hash  <<" HASHIDX: " << idx << " IDX: " << hash->idx << endl;
		}
		count++;
	}
}

	cout << "Done reading " << endl;

	myfile.close();
}


void createTeams(string filename) {
	ifstream myfile(filename);
	string line, previous, info, text,prefix;

	int count = 0;

	Players *s1 = new Players();
	Players *hash;
	Team *team;

	if (myfile.is_open()) {

		while (getline(myfile, line)) {
			if (count < 6) {
				int end =line.find(" Rankings");
				int start = line.find("Week")+10;
//				cout << "RANKINGS: " << start << end << endl;
				if(end!=-1 && end > start && prefix==""){
					prefix = line.substr(start,end-start);
				}
				count++;
				continue;
			}

			info = line;
			s1->idx = info.substr(0, info.find(","));
			info = info.substr(info.find(",") + 1);
//			cout <<  s1->idx <<" INFO : " << info << endl;

			s1->name = info.substr(0, info.find(","));
			info = info.substr(info.find(",") + 1);

			string _team =  info.substr(0, info.find(","));
			info = info.substr(info.find(",") + 1);

			if(teams.find(_team)== teams.end()){
				team = &teams[_team];
				team->name_hash = _team;
				team->name = s1->name;
//				s1->team = &teams[_team];
			}else{
//				s1->team = &teams[_team];
			}


			s1->id = info.substr(0, info.find(","));
			info = info.substr(info.find(",") + 1);


			s1->name_hash = s1->name.substr(0,1) +"."+ s1->name.substr(s1->name.find(" ")+1);


			if(players.find(s1->name_hash) == players.end()){
				cout << "NOT Found player:" << s1->name <<";"<< s1->name_hash << endl;

			}else{
				hash = &players[s1->name_hash];
				hash->position = prefix;
				hash->idx = s1->idx;
//				cout <<"NAME: " << s1->name_hash  <<" HASHIDX: " << s1->idx << " IDX: " << hash->idx << endl;
		}
		count++;
	}
}

	cout << "Done reading " << endl;

	myfile.close();
}


void readInRankings() {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("data")) != nullptr) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != nullptr) {
			printf("%s\n", ent->d_name);
			string file = "data/";
			file.append(ent->d_name);
			if (file.find(".csv") != -1) {
				if(file.find("DST")!=-1){
					createTeams(file);
				}else{
					readRankings(file);
				}
			}
		}
		closedir(dir);
	} else {
		/* could not open directory */
		perror("");
		return;
	}
}

void readPlays(string filename) {
//	string filename = "data/json/2014090701.json";
	ifstream myfile(filename);
	Game *g;
	string line;

	if (myfile.is_open()) {

		getline(myfile, line);
//		cout << "GAMECOUNT: " << gameCount << endl;
		cout << "Game: " << line.substr(0,400) << endl;

		g = new Game();
		int home = 0, away=0;
		string homet,awayt;

		home = line.find("\"abbr\":");
		away = line.find("\"abbr\":",home+5);

		homet = line.substr( home +8,line.find("\",",home+8) - (home+8));
		awayt = line.substr( away +8,line.find("\",",away+8) - (away+8));

		g->away = awayt;
		g->home = homet;
		teams[awayt].addGame(g);
		teams[homet].addGame(g);
		g->parseDrives(line.substr(line.find("\"drives\"")));
		games.push_back(g);
	}
	myfile.close();
}

void readPlayFiles() {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("data/json")) != nullptr) {
		/* print all the files and directories within directory */
//		readPlays("data/json/2014113004.json");
//		readPlays("data/json/2014111603.json");
//		readPlays("data/json/2014113011.json");
		readPlays("data/json/2014113007.json");
		while ((ent = readdir(dir)) != nullptr) {
			//printf("%s\n", ent->d_name);
			string file = "data/json/";
			file.append(ent->d_name);
			if (file.find(".json") != -1) {
				if(file.find("")!=-1){
//					readPlays(file);
				}

			}
		}
		closedir(dir);
	} else {
		/* could not open directory */
		perror("");
		return;
	}
}

void configureTeamPlays(){
	cout << "configureTeams" << endl;
	Team *team;
	Game *game;
	Drive *drive;

	for(map<string, Team>::iterator it1=teams.begin(); it1!=teams.end(); ++it1){
		//std::cout << it1->first << " => " << (it1->second).name << " plays: "<< (it1->second).plays.size( )<<'\n';
	    team = &(it1->second);

	    for(list<Game *>::iterator it2 = team->games.begin(); it2!=team->games.end(); it2++){

	    	game = *it2;

	    	for(list<Drive *>::iterator it3 = game->drives.begin(); it3!=game->drives.end(); it3++){
	    		drive = *it3;

	    		if(team->name_hash == drive->posteam)
	    			std::copy(drive->plays.begin(), drive->plays.end(),
	    					std::back_insert_iterator<std::list<Play *> >(team->plays));
	    	}
	    }
	}
}

void configureTeamPlayers(){
	cout << "configureTeamPlayers" << endl;
	Players *player;
	Game *game;
	Drive *drive;

    for (map<string, Players>::iterator it1=players.begin(); it1!=players.end(); ++it1){
    	player = &it1->second;
//  	  std::cout << it1->first << " => " << player->name << " team " << player->team <<  endl;
	  teams[player->team].addPlayer(player);

    }
}
void playsToPoints(){
//	string output = "JacvsNYG.csv";
//	ofstream myout(output);
	PointCalculator *convert =  new PointCalculator();
	string name="";
	Team *team;
	Play *play;
	Players *player;
	string *s;
	PlayPoints *playpoint;
	int first= 0,next =0 ;
	double pts = 0.0;

	for (map<string, Team>::iterator it1=teams.begin(); it1!=teams.end(); ++it1){
//		std::cout << it1->first << " => " << (it1->second).name << " plays: "<< (it1->second).plays.size( )<<'\n';

		team = &(it1->second);
		for(list<Play *>::iterator it2 = team->plays.begin(); it2!=team->plays.end(); it2++){
			play = *it2;

			for(list<string>::iterator it3 = play->_players.begin(); it3!=play->_players.end(); it3++){
				s = &(*it3);

				first = s->find("\"playerName\":");
				next = s->find("\",",first);
				if(first != -1 && next != -1){
					name = s->substr(first + 14, next - first - 14);
				}
				pts = convert->play(s);
				//cout << "PlayPoints for: " << name << " found: "<< players[name].name <<endl;
				player = &players[name];

				playpoint = new PlayPoints(player,pts, s);
				play->playPoints.push_back(playpoint);

			}
	    }
	}

//	Rushing yards made = 0.1pts
//	Rushing touchdowns = 6pts
//	Passing yards = 0.04pts
//	Passing touchdowns = 4pts
//map<string, double> points;
//points["10"] = 0.1;
//points["11"] = 6.0;
////points["13"] = 0.04;
//points["15"] = 0.04;
//points["16"] = 4;
////	Interceptions = -1pt
////	Receiving yards = 0.1pts
////	Receiving touchdowns = 6pts
////	Receptions = 0.5pts
////	Kickoff return touchdowns = 6pts
////	Punt return touchdowns = 6pts
////	Fumbles lost = -2pts
////	Own fumbles recovered touchdowns = 6pts
////	Two-point conversions scored = 2pts
////	Two-point conversion passes = 2pts
////	Field-goals from 0-19 yards = 3pts
////	Field-goals from 20-29 yards = 3pts
////	Field-goals from 30-39 yards = 3pts
////	Field-goals from 40-49 yards = 4pts
////	Field-goals from 50+ yards = 5pts
////	Extra-point conversions = 1ptDefense:
////	Sacks = 1pt
//points["19"] = -1;
//points["20"];
//points["21"] = 0.1;
//points["22"] = 6;
//points["24"];
//points["25"];
//points["26"];
//points["33"];
//points["34"];
//points["38"];
//points["45"];
//points["46"];
//points["52"];
//points["53"];
//points["54"];
//points["55"];
//points["56"];
//points["63"];
//points["64"];
//points["70"];
//points["71"];
//points["72"];
//points["73"];
//points["74"];
//points["75"];
//points["77"];
//points["83"];
//points["86"];
//points["87"];
//points["88"];
//points["89"];
//points["90"];
//points["91"];
//points["95"];
//points["96"];
//points["102"];
//points["103"];
//points["104"];
//points["106"];
//points["108"];
//points["111"];
//points["120"];
//	Offense:
//	Rushing yards made = 0.1pts
//	Rushing touchdowns = 6pts
//	Passing yards = 0.04pts
//	Passing touchdowns = 4pts
//	Interceptions = -1pt
//	Receiving yards = 0.1pts
//	Receiving touchdowns = 6pts
//	Receptions = 0.5pts
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

}

void getPointTotals(string away, string home){
	cout << "getPointTotals "<< home << "@" << away << endl;
	Game *game;
	Drive *drive;
	Play *play;
	PlayPoints *plpt;

	string playerName;
int count = 0;
int sum = 0;

for (list<Game *>::iterator it1=games.begin(); it1!=games.end(); ++it1){
	game = *it1;
	cout << game->away << "@" << game->home << endl;
	if(game->home == home && game->away == away){
		cout << "FOUND " << game->away << "@" << game->home << endl;
		for(list<Drive *>::iterator it2 = game->drives.begin(); it2!=game->drives.end(); it2++){
			drive = *it2;
			for(list<Play *>::iterator it3 = drive->plays.begin(); it3!=drive->plays.end(); it3++){
				play = *it3;
				for(list<PlayPoints *>::iterator it4 = play->playPoints.begin(); it4!=play->playPoints.end(); it4++){
					plpt = *it4;
					count ++ ;
					plpt->player->updateStats(plpt);
					plpt->player->points += plpt->pts;
				}
		   }
		}
	}
  }

	Players *player;

	for (list<Players *>::iterator it1=teams[home].players.begin(); it1!=teams[home].players.end(); ++it1){
		player = *it1;
		cout << "Player: " << player->name <<
				" PaY "<< player->PaY <<
				" , PaTD: " << player->PaTD <<
				" , RuY " << player->RuY <<
				" , RuTD "<< player->RuTD <<
				" , ReY " << player->ReY<<
				" , ReTD " << player->ReTD <<
				" , FL " << player->FL <<
				" , Int " << player->Int <<
				" , points: " <<  player->points
				<<endl;
	}

	for (list<Players *>::iterator it1=teams[away].players.begin(); it1!=teams[away].players.end(); ++it1){
		player = *it1;
		cout << "Player: " << player->name <<
				" PaTD: " << player->PaTD <<
				" , PaY "<< player->PaY <<
				" , RuY " << player->RuY <<
				" , RuTD "<< player->RuTD <<
				" , FL " << player->FL <<
				" , Int " << player->Int <<
				" , ReTD " << player->ReTD <<
				" , points: " <<  player->points
				<<endl;
	}
}


void printOutPlaysPerTeam(){
	Team *team;
	Play *play;
	PlayPoints *plpt;
	Players *player;

	string output = "Fantasy_Week13_Salaries.csv";
	ofstream myout(output);
	double total = 0.0;
	string stuffs;

	map<string,double> results;

	for (map<string, Team>::iterator it1=teams.begin(); it1!=teams.end(); ++it1){
		team = &it1->second;

		cout << team->name << " Players: " << team->players.size() <<
				" Plays: " << team->plays.size()<< endl;

		for (list<Play *>::iterator it2=team->plays.begin(); it2!=team->plays.end(); ++it2){
			results.clear();

			play = *it2;
//			cout << play->desc << endl;

			for(list<PlayPoints *>::iterator it3=play->playPoints.begin(); it3!=play->playPoints.end(); it3++){
					plpt = *it3;
//					cout << "IDX: " << plpt->player->idx << endl;
					stuffs = plpt->player->position +plpt->player->idx;
					results[stuffs] += plpt->pts;
					player->points += plpt->pts;
			}

//			for (map<string, double>::iterator it4=results.begin(); it4!=results.end(); ++it4){
//				cout << it4->first <<" : "<<  it4->second << endl;
//			}
		}
	}

	myout.close();
}

int main() {
	// writeSalaries();
	readInSalaries();
	readInRankings();
	readPlayFiles();
	configureTeamPlayers();
	configureTeamPlays();
	playsToPoints();
	printOutPlaysPerTeam();

	getPointTotals("OAK","STL");

//	for (map<string, Team>::iterator it1=teams.begin(); it1!=teams.end(); ++it1){
//
//	}

Team *team;

//for (map<string, Team>::iterator it1=teams.begin(); it1!=teams.end(); ++it1){
//	team = &it1->second;
//	cout << team->name << " Players: " << team->players.size() << " Plays: " << team->plays.size()<< endl;
//}

//	vector<string> keys;
//	keys.reserve(players.size());

//	for (map<string,Players>::iterator it=players.begin(); it!=players.end(); ++it)
//	    std::cout << it->first << " => " << it->second << '\n';


	cout << "Game count: " << games.size() << " Team Count: " << teams.size()
			<< " Players Count: " << players.size() << endl;
	cout << "BYE " << endl;

	return 0;
}
