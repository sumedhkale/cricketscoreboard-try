#include<stdio.h>
#define max 12
typedef struct over{
	int n;
	char over[max];
	float dcount;
	int bcount;//char 
}OVER;
typedef struct teamscore{
	int total;
	int wickets;
	float crr,rrr;
}teamscr;
/*typedef struct pship{
	int total;
	int wickets;
	float crr;
}teamscore;*/
typedef struct batsman{
	int b;//balls played
	int r,high,no,fours,sixes,ducks,Fifties,Hundreds;//runsmade,highest,notouts
	float bat_avg,SR;
}batsman; 
typedef struct bowler{
	int ob,bb,rg,m,w,fivewktH,tenwktH,hatricks;//oversbowled,ballsbowled,runsgiven,maidens,wicktes
	float bowl_avg,eco;
}bowler;
typedef struct extras{
	int wides,noballs,legbyes,byes;
}extras;
typedef struct partnership{
	int scr;
	int balls;
}pship;

