#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h> 

#define MAX_QB 38
#define MAX_RB 117
#define MAX_WR 150
#define MAX_TE 82
#define MAX_K 33
#define MAX_DST 32
#define MAX_ROSTERS 8589220
#define MAX_PLAYS 1000
#define SALARY_CAP 60000
#define ACCEPT 100


static int idx1h = 0;
static int idx2h = 0;

struct player {
  int rank;
  int salary;
  char name[30];
  char team[20];
  char matchup[20];
  int best_rank;
  int worst_rank;
  double avg_rank;
  double std_dev;
} qb[38], rb[117], wr[150], te[82], k[33], dst[32];

double _qb[38],_rb[117], _wr[150],_te[82], _k[33], _dst[32];

struct roster {
  int qb;
  int rb1;
  int rb2;
  int wr1;
  int wr2;
  int wr3;
  int te;
  int k;
  int dst;
  int total_amount;
  int accept_ratio;
} rosters1h[MAX_ROSTERS], rosters2h[MAX_ROSTERS];


void updateRoster(struct roster *rost){

 double points = _qb[rost->qb] + _rb[rost->rb1] + _rb[rost->rb2] + _wr[rost->wr1] + _wr[rost->wr2] + _wr[rost->wr3] + _te[rost->te];


  if(points > ACCEPT) {
      rost->accept_ratio++; 
  }
}

struct plays {
  char role1[3];
  int player1;
  double pts1;
  char role2[3];
  int player2;
  double pts2;
};


void copyMe(char *from, char *to){
  while(*to++=*from++);
}



int mean = 100;
int var = 10;


void populateData (FILE *fp, struct player * playersarr, int l) {
  char curplayer[300];
  int i = 0;
  
  fgets(curplayer, 300, fp);

  while (fgets(curplayer, 300, fp) != EOF){
    char* tok;
    tok = strtok (curplayer, ",");
    playersarr[i].rank = atoi(tok);

    copyMe(strtok(NULL, ","), playersarr[i].name);
    
    copyMe(strtok(NULL, ","), playersarr[i].team);
    copyMe(strtok(NULL, ","), playersarr[i].matchup);
    playersarr[i].best_rank = atoi(strtok(NULL, ","));
    playersarr[i].worst_rank = atoi(strtok(NULL, ","));
    tok = strtok(NULL, ",");
    sscanf(tok,"%lf", &playersarr[i].avg_rank);
    sscanf(curplayer, "%lf", &playersarr[i].std_dev);
    i++;
        
    if (i == l){
      break;
    }
    
  }
}

int readPlays (FILE *fp, struct plays * playsarr, int l){
  char curplay[300];
  int i = 0;
  char* tok;
  while (fgets(curplay, 300, fp) != EOF) {
    if(strlen(curplay) < 3) break;
    curplay[strlen(curplay)-1] = 0;

    tok = strtok(curplay, ",");
   if(tok != NULL){
    copyMe(tok, playsarr[i].role1);
    
    playsarr[i].player1 = atoi(strtok(NULL, ","));
 
    sscanf(strtok(NULL, ","), "%lf", &playsarr[i].pts1);
    }
    tok = strtok(NULL, ",");
    if(tok != NULL){

    copyMe(tok, playsarr[i].role2);

    playsarr[i].player2 = atoi(strtok(NULL, ","));
    
    sscanf(strtok(NULL, ","), "%lf", &playsarr[i].pts2);
    }
    
    i++;
  }
return i;
}

void getsalaries(){
  char curplayer[300];
  FILE *fp; 
  fp = fopen("FantasyData/Fantasy_Week13_Salaries.csv","r");
  int salary;
  char role[4];
  char name[30];
  int row = 0;
  int i;

  while (fgets(curplayer, 300, fp) != EOF){
   if(row++ == 213) break;
  
    char* tok;
    tok = strtok (curplayer, ",");
    
    copyMe(tok, role);
    copyMe(strtok(NULL, ","), name);
    salary = atoi(strtok(NULL, ","));
    struct player *ptr;
    int max; 

    if(!strcmp(role,"QB")){
	ptr = qb;
	max = MAX_QB;	
    }else if(!strcmp(role,"RB")){
	ptr = rb;
	max = MAX_RB;	
    }else if(!strcmp(role,"WR")){
   	ptr = wr;
	max = MAX_WR;	
    }else if(!strcmp(role,"K")){
 	ptr = k;
	max = MAX_K;	
    }else if(!strcmp(role,"D")){
	ptr= dst;
	max = MAX_DST;	
    }else if(!strcmp(role,"TE")){
 	ptr = te;
	max = MAX_TE;	
    }
   
    for(i = 0; i < max; i++ ){
  	if(strcmp(name,ptr[i].name)==0){	
	ptr[i].salary = salary;
    }
   }
  }
}

void finalizeDST (int qbi, int rb1i, int rb2i, int wr1i, int wr2i, int wr3i, int tei, int ki){
  int dsti;
  int amount = qb[qbi].salary + rb[rb1i].salary + rb[rb2i].salary + wr[wr1i].salary + wr[wr2i].salary + wr[wr3i].salary + te[tei].salary + k[ki].salary;
 int sum;
 struct roster * rosters;
 int idx;
 for (dsti = 0; dsti < 5; dsti++) {
    sum = amount + dst[dsti].salary;
    if (dst[dsti].salary != 0 && sum <= SALARY_CAP && sum >= 59000){
      if (idx1h < MAX_ROSTERS){
	rosters = rosters1h;
	idx = idx1h;
	idx1h++;
      }
      else {
        rosters = rosters2h;
	idx = idx2h;
	idx2h++;
      } 
      rosters[idx].qb = qbi;
      rosters[idx].rb1 = rb1i;
      rosters[idx].rb2 = rb2i;
      rosters[idx].wr1 = wr1i;
      rosters[idx].wr2 = wr2i;
      rosters[idx].wr3 = wr3i;
      rosters[idx].te = tei;
      rosters[idx].k = ki;
      rosters[idx].dst = dsti;
      rosters[idx].total_amount = sum;
    }
  }
}

void finalizeK (int qbi, int rb1i, int rb2i, int wr1i, int wr2i, int wr3i, int tei){
  int ki;
  for (ki = 0; ki < 5; ki++) {
    if (k[ki].salary != 0){
      finalizeDST (qbi, rb1i, rb2i, wr1i, wr2i, wr3i, tei, ki);
    }
  }
}

void finalizeTE (int qbi, int rb1i, int rb2i, int wr1i, int wr2i, int wr3i){
  int tei;
  for (tei = 0; tei < 5; tei++) {
    if (te[tei].salary != 0){
      finalizeK (qbi, rb1i, rb2i, wr1i, wr2i, wr3i, tei);
    }
  }
}

void finalizeWR3 (int qbi, int rb1i, int rb2i, int wr1i, int wr2i) {
  int wr3i;
  for (wr3i = wr2i + 1; wr3i < 20; wr3i++) {
    if ( wr[wr3i].salary != 0) {
      finalizeTE (qbi, rb1i, rb2i, wr1i, wr2i, wr3i);
    }
  }
}


void finalizeWR2 (int qbi, int rb1i, int rb2i, int wr1i) {
  int wr2i;
  for (wr2i = wr1i + 1; wr2i < 20; wr2i++) {
    if (wr[wr2i].salary != 0) {
      finalizeWR3 (qbi, rb1i, rb2i, wr1i, wr2i);
	}
  }
}


void finalizeWR1 (int qbi, int rb1i, int rb2i){
  int wr1i;
  for (wr1i = 0; wr1i < 20; wr1i++) {
    if (wr[wr1i].salary != 0){
      finalizeWR2 (qbi, rb1i, rb2i, wr1i);
    }
  }
}


void finalizeRB2 (int qbi, int rb1i) {
  int rb2i;
  for (rb2i = rb1i + 1; rb2i < 20; rb2i++) {
    if (rb2i != rb1i && rb[rb2i].salary != 0) {
      finalizeWR1 (qbi, rb1i, rb2i);
    }
  }
}

void finalizeRB1 (int qbi) {
  int rb1i;
  for (rb1i = 0; rb1i < 10; rb1i++) {
    if (rb[rb1i].salary != 0){
      finalizeRB2 (qbi, rb1i);
    }
  }
}


void makeRosters(){
  int qbi;
  for (qbi = 0; qbi < 15; qbi++) {
    if (qb[qbi].salary != 0){
      finalizeRB1(qbi);
    }
  }
}

int nextNormal(int mean, int var){

 float Y=0;
 float U=0;
  int i = 0;
 float result=-1;
while(result < 0 || result >130){ 
                                                                        
    Y = ((rand()%10000)/1000.0) -5.0;                                   
    U = ((rand()%10000)/10000.0);                                       
                                                                        
    result = mean + Y*var;                                       
     
}                                
 return (int) result;                                                               
}

int nextUniform(int max){
   
int r = rand()%max;

return r; 
}

struct plays teams[32][1010];
int playcount[32];
 

void updatePlayer(struct plays *curPlay){

   if(strcmp(curPlay->role1,"QB")==0){
    	_qb[curPlay->player1] += curPlay->pts1;
    } else if(strcmp(curPlay->role1,"RB")==0){
    	_rb[curPlay->player1] += curPlay->pts1;
    }else if(strcmp(curPlay->role1,"WR")==0){
    	_wr[curPlay->player1] += curPlay->pts1;
 
    }else if(strcmp(curPlay->role1, "TE") == 0){
    	_te[curPlay->player1] += curPlay->pts1;

    }else if(strcmp(curPlay->role1, "K") == 0){
    	_k[curPlay->player1] += curPlay->pts1;
    
    }else if(strcmp(curPlay->role1, "DST") == 0){
     	_dst[curPlay->player1]  = 0;
    } 

    if(strlen(curPlay->role2) > 1){

    if(strcmp(curPlay->role2,"QB")==0){
    	_qb[curPlay->player2] += curPlay->pts2;
    } else if(strcmp(curPlay->role2,"RB")==0){
    	_rb[curPlay->player2] += curPlay->pts2;
    }else if(strcmp(curPlay->role2,"WR")==0){
    	_wr[curPlay->player2] += curPlay->pts2;
 
    }else if(strcmp(curPlay->role2, "TE") == 0){
    	_te[curPlay->player2] += curPlay->pts2;

    }else if(strcmp(curPlay->role2, "K") == 0){
    	_k[curPlay->player2] += curPlay->pts2;
    
    }else if(strcmp(curPlay->role2, "DST") == 0){
    	_dst[curPlay->player2] = 0;
    } 
    }
}
void eraseArray( double *arr,int size){
  int  i = 0;
  while( i++ < size) *(arr++) = 0;
}

int main (){
  
 srand(time(NULL));

  FILE *fpqb;
  FILE *fprb;
  FILE *fpwr;
  FILE *fpte;
  FILE *fpk;
  FILE *fpdst;
  fpqb = fopen("FantasyData/FantasyPros_2014_Week_13_QB_Rankings.csv", "r");
  fprb = fopen("FantasyData/FantasyPros_2014_Week_13_RB_Rankings.csv", "r");
  fpwr = fopen("FantasyData/FantasyPros_2014_Week_13_WR_Rankings.csv", "r");
  fpte = fopen("FantasyData/FantasyPros_2014_Week_13_TE_Rankings.csv", "r");
  fpk = fopen("FantasyData/FantasyPros_2014_Week_13_K_Rankings.csv", "r");
  fpdst = fopen("FantasyData/FantasyPros_2014_Week_13_DST_Rankings.csv", "r");
  populateData(fpqb, qb, 38);
  populateData(fprb, rb, 117);
  populateData(fpwr, wr, 150);
  populateData(fpte, te, 82);
  populateData(fpk, k, 33);
  populateData(fpdst, dst, 32);
  
  int i, j;
  getsalaries();
  
  makeRosters();
 
int  z = 0;

char *prefix = "FantasyData/playcsv/Fantasy_";
char str[80];

for(i=0;i < 32; i++){
}

  FILE *teamplays;
  for (z = 0; z < 32; z++) {
	strcpy(str,  prefix);
	strcat (str, dst[z].name);
	strcat( str, ".csv");
       
	if(access(str, F_OK) != -1){
 	  teamplays = fopen(str,"r" );
	  if(teamplays){
	       playcount[z] = readPlays (teamplays,teams[z], 1002);
	   }else{
		printf("does not exist");
	    }

    	  fclose(teamplays);
	}else{
	  printf("No \n");
	}
  } 
 
  printf(" DONE \n" );
  int pickPlay;
  int randomPlay;
  int ret=0;
  int teamnumber = 0;
 
  struct roster rost; 
  rost.qb = 10;
  rost.rb1 = 12;
  rost.rb2 = 3;
  rost.wr1=1;
  rost.wr2=2;
  rost.wr3=3;
  rost.te=3;
  rost.k=3;
  rost.dst=1;
  rost.accept_ratio = 0 ;
  struct plays *curPlay;


int totalLoop;

for(totalLoop=0; totalLoop < 1000; totalLoop++){

 for(teamnumber=0; teamnumber < 32; teamnumber++){
   pickPlay = nextNormal(mean, var);
 
   for (ret=0;ret < pickPlay; ret++){
     randomPlay = nextUniform(playcount[teamnumber]);
     curPlay = &teams[teamnumber][randomPlay];
    updatePlayer(curPlay);
   } 
  }
  
  int xx,yy;
  
  for(xx=0; xx < idx1h; xx++){
    updateRoster(&rosters1h[xx]);
  }
 
  for(yy=0; yy < idx2h; yy++){
    updateRoster(&rosters2h[yy]);
  }  


  updateRoster(&rost); 
eraseArray(_qb,MAX_QB);
eraseArray(_rb,MAX_RB);
eraseArray(_wr,MAX_WR);
eraseArray(_te,MAX_TE);
eraseArray(_k,MAX_K);
eraseArray(_dst,MAX_DST);
}

//Filter the ones with accepting ratio more than 75% and minize on analyst rankings
 int minrank = 99999;
 int temp=0;
 struct roster *minrost;
 struct roster *ro;
 int xx;
 for(xx=0; xx < idx1h; xx++){

  if(rosters1h[xx].accept_ratio > 0.75){
     ro = &rosters1h[xx];
     temp = ro->qb+ ro->rb1+ ro->rb2 + ro->wr1 + ro->wr2 + ro->wr3 + ro->te + ro->dst + ro->k;
     if(temp < minrank){
       minrost = ro;
       minrank=temp;
     }
   }
 }

//Print our final choice
    printf ("QB: %s Salary: %d\n", qb[minrost->qb].name, qb[minrost->qb].salary);
    printf ("RB: %s Salary: %d\n", rb[minrost->rb1].name, rb[minrost->rb1].salary);
    printf ("RB: %s Salary: %d\n", rb[minrost->rb2].name, rb[minrost->rb2].salary);
    printf ("WR: %s Salary: %d\n", wr[minrost->wr1].name, wr[minrost->wr1].salary);
    printf ("WR: %s Salary: %d\n", wr[minrost->wr2].name, wr[minrost->wr2].salary);
    printf ("WR: %s Salary: %d\n", wr[minrost->wr3].name, wr[minrost->wr3].salary);
    printf ("TE: %s Salary: %d\n", te[minrost->te].name, te[minrost->te].salary);
    printf ("K: %s Salary: %d\n", k[minrost->k].name, k[minrost->k].salary);
    printf ("DST: %s Salary: %d\n", dst[minrost->dst].name, dst[minrost->dst].salary);
    printf ("Total Salary: %d\n\n", minrost->total_amount);

return 0;
}
