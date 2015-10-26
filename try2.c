#include <ncurses.h>
#include<string.h>
#include<stdlib.h>
#include "1list.h"
#include <time.h>
//#include "OVER.h"
WINDOW *wteamA,*wteamB,*owps,*scrbrd;
FILE *fpA,*fpB;
int tsA,tsB,token = 0,stadium,tossr;
WINDOW *tsquadA,*tsquadB;
WINDOW *win;
list l1,l2;
time_t tt;
list *lA,*lB;
int tok = 0;
node *p11,*q11;
int over;
//OVER *ovr;
//teamscr *tscr;
//pship *ps;
//extras *ex;
//static batsman *batsmen;
int res = 1,choice1,tossflag = 0,tAbat,tBbat,ser = 1;
node *q,*r,*t;
char ball_input;
int overno = 0;
void init(list *l) {
	l->head = l->tail = NULL;
	l->length = 0;
}
void insert(list *l, char *Attr,char *Fname,char *Lname, int pos) {
	node *p, *tmp;
	profile *prof1;
	int i;
	if(pos < 0 || pos > l->length)		
		return;
	tmp = (node *)malloc(sizeof(node));
	strcpy(tmp->attr, Attr);
	strcpy(tmp->fname, Fname);
	strcpy(tmp->lname, Lname);
	tmp->prof = NULL;
	tmp->next = tmp->prev = NULL;
	if(l->head == NULL) {
		
		l->head = l->tail = tmp;
		l->length = 1;
		return;
	}// assert: posoitin is =>0 && <= length 
	p = l->head;
	for(i = 0; i < pos - 1; i++)
		p = p->next;
	tmp->prev = p;	
	p->next = tmp;
	prof1 = tmp->prof = (profile *)malloc(sizeof(struct info));
	prof1->batsmn.r = prof1->batsmn.b = prof1->batsmn.fours = prof1->batsmn.sixes = prof1->batsmn.bat_avg = 0;
	prof1->bowlr.ob = prof1->bowlr.m = prof1->bowlr.w = prof1->bowlr.rg = prof1->bowlr.eco = 0;
	if(pos == l->length)
		l->tail = tmp;
	(l->length)++;
}
void traverse1(list *l){
	lB = l;	
	node *p = l->head;
	while(p!=NULL) {
		
		wprintw(win,"%s %s %s\n", p->attr, p->fname, p->lname);
		wrefresh(win);
		p = p->next;
	}
	wprintw(win,"End\n");
	wrefresh(win);
	
}
void traverse(list *L) {
	node *p = L->head;
	if(token == 0)
		lA = L;
	while(p!=NULL) {
		wprintw(win,"%s %s %s\n", p->attr, p->fname, p->lname);
		wrefresh(win);
		p = p->next;
	}
	wprintw(win,"End\n");
	wrefresh(win);
	
}
//void append(list *l,char *Attr,char *Fname,char *Lname
//){
	//insert(list *l, char *Attr,char *Fname,char *Lname, int pos)
//}	
int printmenu() {
	int choice;
	mvwprintw(win,22,0,"1. swap  \t"\
			       "2. remove\t"\
			       "3. append\t"\
		               "4. length\t"\
			       "5. sort  \t"\
			       "6. save & proceed\n");
	mvwprintw(win,24,0,"your choice:");
	wrefresh(win);
	wscanw(win,"%d", &choice);		
	return choice;
}
void swap(list *l,int posi, int posj){
	node *p;
	node *q;
	node *tmp;
	//node *tmp1,*tmp2;
	int i,j;
	profile *ptmp;
	tmp = (node *)malloc(sizeof(struct node));
	tmp->prof = NULL;
	p = q = l->head;
	
	for(i=0;i<(posi-1);i++)
		p = p->next;
	for(j=0;j<(posj-1);j++)
		q = q->next;
	if(p == q)
		return;
	strcpy(tmp->attr, p->attr);
	strcpy(tmp->fname,p->fname);
	strcpy(tmp->lname,p->lname);
	strcpy(p->attr, q->attr);
	strcpy(p->fname,q->fname);
	strcpy(p->lname,q->lname);
	strcpy(q->attr, tmp->attr);
	strcpy(q->fname,tmp->fname);
	strcpy(q->lname,tmp->lname);
	free(tmp);
	//ptmp = p->prof;
	//p->prof = q->prof;
	//q->prof = ptmp;
	//free(ptmp);
	/*tmp->prof->matches = p->prof->matches;
	tmp->prof->matches = p->prof->matches;
	tmp->prof->matches = p->prof->matches;
	tmp->prof->matches = p->prof->matches;
	tmp->prof->matches = p->prof->matches;
	tmp->prof->matches = p->prof->matches;
	tmp->prof->matches = p->prof->matches;
	tmp->prof->matches = p->prof->matches;
	tmp->prof->matches = p->prof->matches;
	tmp->prof->matches = p->prof->matches;*/
/*if((p == l->head) && (q==l->head))
		return;
	if((p == l->tail) && (q==l->tail))
		return;
	if(p == l->head)
		l->head = q;
	if(q == l->head )
		l->head = p;
	if(p == l->tail)
		l->tail = q;
	if(q == l->tail )
		l->tail = p;
	p->next->prev = p->prev->next = tmp1;
	tmp1->prev = p->prev;
	tmp1->next = p->next;
	q->next->prev = q->prev->next = tmp2;
	tmp2->prev = q->prev;
	tmp2->next = q->next;
	q->next = tmp1->next;
	q->prev = tmp1->prev;
	tmp1->prev->next = tmp1->next->prev = q;
	p->next = tmp2->next;
	p->prev = tmp2->prev;
	tmp2->prev->next = tmp2->next->prev = p;
	tmp1->prev = tmp1->next = tmp2->prev = tmp2->next = NULL;
	free(tmp1);
	free(tmp2);*/
}

void drawmenu(int item,int label){	
	int c,MENUMAX;
	if( label == 1){
		MENUMAX = 3;
		char menu[3][21] = {		/* 6 items for MENUMAX */
			"PLAY",
			"PLAYER PROFILES",
			"EXIT"
			};
		for(c=0;c<MENUMAX;c++){
			if( c==item )
				attron(A_REVERSE);	/* highlight selection */
			mvaddstr(3+(c*2),20,menu[c]);
			attroff(A_REVERSE);		/* remove highlight */
		}
		mvaddstr(20,25,"Use 'ARROW' keys to move UP and DOWN.\n\t\t\tPress 'Enter' to select the desired option.");
		curs_set(0);
		refresh();
	} 
	if(label == 2){
		MENUMAX = 8;
		char menu[8][30]={
			"1.INDIA",
			"2.SOUTH AFRICA",
			"3.AUSTRALIA",
			"4.ENGLAND",
			"5.WESTINDIES",
			"6.NEWZEALAND",
			"7.PAKISTAN",
			"8.SRILANKA"};
		for(c=0;c<MENUMAX;c++){
			if( c==item )
				wattron(wteamA,A_REVERSE);	/* highlight selection */
			mvwaddstr(wteamA,4+(c*2),3,menu[c]);
			wattroff(wteamA,A_REVERSE);		/* remove highlight */
		}
		wrefresh(wteamA);
	}
	if(label == 3){
		MENUMAX = 8;
		char menu[8][30]={
			"1.INDIA",
			"2.SOUTH AFRICA",
			"3.AUSTRALIA",
			"4.ENGLAND",
			"5.WESTINDIES",
			"6.NEWZEALAND",
			"7.PAKISTAN",
			"8.SRILANKA"};
		for(c=0;c<MENUMAX;c++){
			if( c==item )
				wattron(wteamB,A_REVERSE);	/* highlight selection */
			mvwaddstr(wteamB,4+(c*2),3,menu[c]);
			wattroff(wteamB,A_REVERSE);		/* remove highlight */
		}
	wrefresh(wteamB);
	}
	if(label == 4){
		MENUMAX = 2;
		char menu[2][10]={
			"1.DAY",
			"2.NIGHT"};
		for(c=0;c<MENUMAX;c++){
			if( c==item )
				wattron(owps,A_REVERSE);	/* highlight selection */
			mvwaddstr(owps,1+c,0,menu[c]);
			wattroff(owps,A_REVERSE);
		}
	wrefresh(owps);
	}
	if(label == 5){
		MENUMAX = 4;
		char menu[4][12]={
			"1.WARM",
			"2.COOL",
			"3.HUMID",
			"4.OVERCAST"};
		for(c=0;c<MENUMAX;c++){
			if( c==item )
				wattron(owps,A_REVERSE);	/* highlight selection */
			mvwaddstr(owps,5+c,0,menu[c]);
			wattroff(owps,A_REVERSE);
		}
	wrefresh(owps);
	}
	if(label == 6){
		MENUMAX = 8;
		char menu[8][80]={
			"1.A",
			"2.B",
			"3.C",
			"4.D",
			"5.E",
			"6.F",
			"7.G",
			"8.H",};
		for(c=0;c<MENUMAX;c++){
			if( c==item )
				wattron(owps,A_REVERSE);	/* highlight selection */
			mvwaddstr(owps,2+c,80,menu[c]);
			wattroff(owps,A_REVERSE);
		}
	wrefresh(owps);
	}
	if(label == 7){
		MENUMAX = 7;
		char menu[7][10]={
			"1.NORMAL",
			"2.HARD",
			"3.DRY",
			"4.DAMP",
			"5.GREEN",
			"6.DUSTY",
			"7.WET"};
		for(c=0;c<MENUMAX;c++){
			if( c==item )
				wattron(owps,A_REVERSE);	/* highlight selection */
			mvwaddstr(owps,12+c,0,menu[c]);
			wattroff(owps,A_REVERSE);
		}
	wrefresh(owps);
	}
	if(label == 8){
		MENUMAX = 2;
		char menu[2][8]={
			"HEADS",
			"TAILS"};
		for(c=0;c<MENUMAX;c++){
			if( c==item )
				wattron(owps,A_REVERSE);	/* highlight selection */
			mvwaddstr(owps,12+c,72,menu[c]);
			wattroff(owps,A_REVERSE);
		}
	wrefresh(owps);
	}
	if(label == 9){
		MENUMAX = 2;
		char menu[2][8]={
			"BATTING",
			"BOWLING"};
		for(c=0;c<MENUMAX;c++){
			if( c==item )
				wattron(owps,A_REVERSE);	/* highlight selection */
			mvwaddstr(owps,21+c,72,menu[c]);
			wattroff(owps,A_REVERSE);
		}
	wrefresh(owps);
	}
	
	
}
// need to make sc1 small
int sc1(int label){
	int key,menuitem = 0,MENUMAX;
	keypad(stdscr,TRUE);
	noecho();
	if(label == 1)
		MENUMAX = 3;
	if((label == 2) || (label == 3) )
		MENUMAX = 8;
	if(label == 4)
		MENUMAX = 2;
	if(label == 5)
		MENUMAX = 4;
	if(label == 6)
		MENUMAX = 8;
	if(label == 7)
		MENUMAX = 7;
	if(label == 8)
		MENUMAX = 2;
	if(label == 9)
		MENUMAX = 2;
	do
	{
		key = getch();
		switch(key){
			case KEY_DOWN:
				menuitem++;
				if(menuitem > MENUMAX-1) menuitem = 0;
				break;
			case KEY_UP:
				menuitem--;
				if(menuitem < 0) menuitem = MENUMAX-1;
				break;
			default:
				break;
		}
		drawmenu(menuitem,label);
		refresh();
	} while(key != '\n');
	echo();		
	return menuitem;
}
void screen(int label){
	int menuitem = 0;
	drawmenu(menuitem,label);
}
int teamselect(int tlabel){
	int i,j;
	int /*wx,wy,*/halfy,halfx;
	int x,y,x1,y1,x2,y2;
	y1 = x2 = y2 = 0;//x1 = 0;
	//char team[]="TEAM SELECTION";
	char teamA[] ="SELECT TEAM A";
	char teamB[] ="SELECT TEAM B";
	getmaxyx(stdscr,y,x);
	halfx = x/2;
	halfy = y/2;
	init_pair(4,COLOR_BLACK,COLOR_CYAN);
	if(tlabel == 2){
		wteamA = newwin(y-1,halfx,1,0);
		mvwaddstr(wteamA,2,(halfx-strlen(teamA))/2,teamA);
		screen(2);
		i = sc1(2);
		wrefresh(wteamA);
		return i;
	}
	if(tlabel == 3){
		wteamB = newwin(y-1,halfx,1,halfx);
		wbkgd(wteamB,COLOR_PAIR(4));
		mvwaddstr(wteamB,2,(halfx-strlen(teamB))/2,teamB);
		screen(3);
		j = sc1(3);
		wrefresh(wteamB);
		return j;
	}	
}
void errorwin(){
	WINDOW *error;
	error = subwin(stdscr,4,50,30,30);
	wprintw(error,"You are a true cricket fan! :P\nLol ! How can same teams play a match?\nPlease select the teams again!");
	wrefresh(error);
	napms(8000);
	delwin(error);
}

void makesquad(char *fname,char *tn){
	if(token == 1)
		win = tsquadB = newwin(0,0,0,0);
	else 
		win = tsquadA = newwin(0,0,0,0);//int t){
	int x,y,i;
	getmaxyx(win,y,x);
	node pl;
	int choice;
	int inpos,posi,posj;
	inpos = 0;
	fpA = fopen(fname,"r");
		/*while(!feof(fpA)){
			fscanf(fpA,"%s %s %s\n",pl.attr,pl.fname,pl.lname);*/
	if(token == 0){
		init(&l1);
		l1.initlen = 15;
		for(i = 0;i<(l1.initlen);i++){//while(!feof(fpA) ){
			fscanf(fpA,"%s %s %s",pl.attr,pl.fname,pl.lname);
			insert(&l1, pl.attr, pl.fname, pl.lname, inpos);
			inpos++;				
		}
	}
	if(token == 1){
		init(&l2);
		l2.initlen = 15;
		for(i = 0;i<(l2.initlen);i++){//while(!feof(fpA) ){
			fscanf(fpA,"%s %s %s",pl.attr,pl.fname,pl.lname);
			insert(&l2, pl.attr, pl.fname, pl.lname, inpos);
			inpos++;				
		}
	}
	while(1) {
		wprintw(win,"TEAM '%s' SQUAD\n\n",tn);
		wprintw(win,"BAT:BATSMEN   \t"\
				"ALL:ALL-ROUNDER \t"\
				"FBOW:FAST-BOWLER\t"\
				"SBOW:SPIN-BOWLER\n\n\n");
		wrefresh(win);
		if(token == 0)
			traverse(&l1);
		if(token == 1)
			traverse1(&l2);
		wrefresh(win);		//printf("Length = %d \n", length(&l));
		choice = printmenu();
		switch(choice) {
			case 1: //swap  
				wprintw(win,"\nEnter the value of positions u want to swap separated by space\n");
				wrefresh(win);
				wscanw(win,"%d %d", &posi, &posj);
				if(token == 0)
					swap(&l1, posi, posj);
				else
					swap(&l2, posi, posj);
				wclear(win);
				break;
			/*case 2: //remove
				printf("Enter the pos \n");
				scanf("%d", &pos);
				s = remov(&p, pos);
				if(s) {
					printf("Returned val = %s \n", s);
					free(s);
				}
				break;
			case 3: //append 
				printf("Enter the val \n");
				scanf("%s", str);
				append(&p, str);
				break;*/
			/*case 4: //length
				printf("Length = %d \n", length(&l));
				break;
			case 5: //reverse
				sort(&p);
				break;*/
			case 6: /*exit */
				//exit(0);
				break;
					
		}
		if(choice == 6)
			break;
		else
			continue;

		
	}
}
void TEAMname(int a){
	char *r;	
	char *teamname;
	switch(a){
		case 0:
			teamname = "team_ind.txt";
			r = "INDIA";
			break;
		case 1:
			teamname = "team_rsa.txt";
			r = "SOUTH AFRICA";
			break;
		case 2:
			teamname = "team_aus.txt";
			r = "AUSTRALIA";
			break;
		case 3:
			teamname = "team_eng.txt";
			r = "ENGLAND";
			break;
		case 4:
			teamname = "team_wind.txt";
			r = "WEST INDIES";
			break;
		case 5:
			teamname = "team_nzl.txt";
			r = "NEWZEALAND";
			break;
		case 6:
			teamname = "team_pak.txt";
			r = "PAKISTAN";
			break;
		case 7:
			teamname = "team_sl.txt";
			r = "SRILANKA";
			break;
		default:
			break;
	}
	makesquad(teamname, r);
}

void owpsf(){
	//ovr = (OVER *)malloc(sizeof(struct over));
	int j,k,l,m;
	owps = newwin(0,0,0,0);
	/*char *ovp;
	printf("ENTER THE NUMBER OVERS:");
	scanf("%f",ovr->n);
	ovp = ovr->over;*/
	wprintw(owps,"SELECT TIME OF DAY:");
	screen(4);
	k = sc1(4);
	wprintw(owps,"\n\nselect weather cnditions(warm,cool,humid,overcast)");
	screen(5);
	l = sc1(5);
	mvwprintw(owps,0,80,"select venue(stadiums at all venues)");
	screen(6);
	stadium = sc1(6);	
	wprintw(owps,"\n\nselect pitch type(normal,hard,dry,damp,green,dusty,Wet)");
	screen(7);
	m = sc1(7);
	//mvwprintw(owps,20,40,"enter the no. of overs:");
	//wscanw(owps,"%d",ovr->n);
	wmove(owps,30,0);
	wattron(owps,A_UNDERLINE | A_BOLD);
	wprintw(owps,"GUIDELINES FOR THE TOSS\n");
	wattroff(owps,A_UNDERLINE | A_BOLD);
	switch(l){
		case 3:
			if((m==0)||(m==1)||(m==2)||(m==5))
				wprintw(owps,"It's OVERCAST!The WICKET looks a good BATTING pitch.\nThe ball will come on to bat nicely.\nSo it's time to get some runs on the board!");
			if(m == 3)
				wprintw(owps,"It's OVERCAST!The pitch is DAMP.\nAn ODD ball might bounce as well,and hence BOWLERS can extract something out of this pitch.\nYou may opt to BOWL first!"); 
			if(m == 4)				
				wprintw(owps,"It's OVERCAST & a GREEN pitch !\nIt's a heaven for BOWLERS!The ball will swing and nip around.\nif you win the toss,BOWL first!");
			if(m == 6)
				wprintw(owps,"It's OVERCAST! The pitch is WET.\nThe ball will stay LOW, and hence the pitch will helps BOWLERS.\nYou may opt to BOWL first!");
			break;
		case 0: case 1:
			if((m==0)||(m==1)||(m==2)||(m==5))
				wprintw(owps,"The WICKET looks a good bating pitch.\nThe ball will come on to the bat nicely.\nSo it's time to get some runs on the board!");
			if((m==3)||(m==4)||(m==6))
				wprintw(owps,"The ball might not bounce as expected.\nThe BOWLERS can surely extract something out of the pitch.\nSo give them a chance first!"); 
			break;
		case 2:
			if((m==0)||(m==1)||(m==2)||(m==5))
    				wprintw(owps,"It's HUMID! The deck looks a good bating pitch.\nThe ball will come on to bat nicely.\nSo it's time to get some runs on the board !");
			if((m==3)||(m==4)||(m==6))
				wprintw(owps,"It's HUMID! The ball might just hold back after bouncing from the deck.\nThe pitch type will assist BOWLERS.\nSo you may give them a chance first !"); 
			break;
		default:
			break;
	}
	wrefresh(owps);
	napms(750);
	getch();
}

char *whichteam(int a){
	char *r;
	switch(a){
		case 0: r="INDIA";
			break; 
		case 1: r="SOUTH AFRICA";
			break;
		case 2: r="AUSTRALIA";
			break;
		case 3: r="ENGLAND";
			break;
		case 4: r="WEST INDIES";
			break;
		case 5: r="NEWZEALAND";
			break;
		case 6: r="PAKISTAN";
			break;
		case 7: r="SRILANKA";
			break;
		default: 
			break;	
	}
	return r;
}
void toss(){
	long int k,l;
	int y,x,tossr,i;
	char ch;
	wclear(owps);
	getmaxyx(owps,y,x);
	mvwprintw(owps,4,45,"%s vs %s",whichteam(tsA),whichteam(tsB));
	wattron(owps,A_UNDERLINE);
	mvwaddstr(owps,(y/2)-10,(x/2)-2,"TOSS");
	mvwaddstr(owps,(y/2)-8,(x/2)-11,"CHOOSE:");
	wattroff(owps,A_UNDERLINE);
	screen(8);
	tossr = sc1(8);
	//wprintw(owps,"tossr:%d",tossr);
	srandom(time(0));
	k = random();
	//wprintw(owps,"k :%ld",k);
	if((k%2) == 0)
		res = 0;
	for(i=0;i<5;i++){
		wmove(owps,16,69+i);
		wprintw(owps,".");
		wrefresh(owps);
		napms(50);
	}
	wdeleteln(owps);
	//wprintw(owps,"res:%d",res);
	//wrefresh(owps);//user has chosen heads and toss results in heads as well
	if( tossr == res ){
		if(res == 0)
			mvwprintw(owps,17,69,"HEADS");
		else
			mvwprintw(owps,17,69,"TAILS");
		mvwprintw(owps,19,61,"%s WON THE TOSS.",whichteam(tsA));
		mvwprintw(owps,21,55,"PLEASE CHOOSE:");
		screen(9);
		choice1 = sc1(9);
		wprintw(owps,"choice1:%d",choice1);
		if(choice1 == 0){
			tAbat = 1;
			tBbat = 0;
			//wprintw(owps,"tAbat:%d tBbat:%d",tAbat,tBbat);
		}
		else{
			tBbat = 1;
			tAbat = 0;
			//wprintw(owps,"tAbat:%d tBbat:%d",tAbat,tBbat);
		}			
		tossflag = 1;
		wrefresh(owps);	
	}
	else{ 
		if(res == 0)
			mvwprintw(owps,17,69,"HEADS");
		else
			mvwprintw(owps,17,69,"TAILS");
		mvwprintw(owps,19,55,"%s LOST THE TOSS.",whichteam(tsA));
		srandom(time(&tt));
		l = random();
		
		if((l%2) == 0)
			ser = 0;
		//wprintw(owps,"l:%ld",l);
		//wprintw(owps,"ser:%d",ser); 
		//	ser = 0;//bowl
		if(ser==0){
			mvwprintw(owps,21,53,"%s CHOSE TO BOWL FIRST.",whichteam(tsB));
			tAbat = 1;
			tBbat = 0;
			//wprintw(owps,"tAbat:%d tBbat:%d",tAbat,tBbat);
		}
		else{
			mvwprintw(owps,21,53,"%s CHOSE TO BAT FIRST.",whichteam(tsB));
			tBbat = 1;
			tAbat = 0;
			//wprintw(owps,"tAbat:%d tBbat:%d",tAbat,tBbat);	
		} 
		wrefresh(owps);
	}
	getch();
	/*if user wins toss give him choice of bat or ball.
	if user loses toss use random.c to decide what will user OR set a default that if user loses toses he will either everytime bat or 		everytime ball.*/

}
/*void getbatsman(int n,int pos){
	profile *ptmp;
	if((tAbat == 1) && (tBbat == 0))
		t = p11 = lA->head;	
	if((tBbat == 1) && (tAbat == 0))
		t = q11 = lB->head;
	int i=1;
	while(i<=n)
		t = t->next;
	ptmp = t->prof;
	mvwprintw(batm,2+pos,0,"%s %s %s",t->attr,t->fname,t->lname);
	mvwprintw(batm,2+pos,42,"%d    \t\t%d\t\t\t%d    \t\t%d\t\t\t%f",ptmp->runs,ptmp->balls,ptmp->fours,ptmp->sixes,ptmp->strikerate);
}*/
/*void nextball(char ball){
	switch(ball){
		case '0':
			(ovr->bcount)++;
			break;
		case '1':
			(ovr->bcount)++;
		  	break;
		case '2':
			(ovr->bcount)++;
			break;
		case '3':
			(ovr->bcount)++;
			break;
		case '4':
			(ovr->bcount)++;
			break;
		case '6':
			(ovr->bcount)++;
			break;
		case o: case O:
			(ovr->bcount)++;
			break;
		case w: case W:
			break;	
		case n: case N:
			break;
		case default:
			 break;
	}
}*/
//int bcount;	
void scrboard(){
	//node *tmp1;//*tmp2;
	//batsmen = (batsman *)malloc(sizeof(struct batsman) * 2);
	//batsman batsman[1];
	//batsmen = batman;//*batsmanB;//*batsmen;
	//batsmanA = NULL;//batsmanB = NULL;
	/*ex = (extras *)malloc(sizeof(struct extras));
	ps = (pship *)malloc(sizeof(struct partnership));
	tscr = (teamscr *)malloc(sizeof(struct teamscore));*/

	scrbrd = newwin(0,0,0,0);
	WINDOW *scr,*batm,*bowl,*curr,*extras,*thisover,*prevover;
	int y,x,batflag = 0;
	float CRR = 0;
	int projscr=0;
	pship ps;
	ps.scr = ps.balls = 0;
	//ps->scr = ps->balls = 0;
	//ex->legbyes = ex->byes =ex->wides = ex->noballs = 0;
	//tscr->crr = tscr->rrr = tscr->total = tscr->wickets = 0;

	
	getmaxyx(scrbrd,y,x);
	//wclear(owps);
	//char *stdm;
	char menu[8][80]={
			"1.A",
			"2.B",
			"3.C",
			"4.D",
			"5.E",
			"6.F",
			"7.G",
			"8.H",};
	mvwprintw(scrbrd,0,((x-strlen(menu[stadium]))/2)-14,"LIVE FROM THE %s\n",menu[stadium]);
	//wrefresh(scrbrd);
	switch(tossflag){
		case 1:
			switch(choice1){
				case 0: 
					wprintw(scrbrd,"%s OPT TO BAT",whichteam(tsA));
					batflag = 1;
					break;
				case 1: 
					wprintw(scrbrd,"%s OPT TO BOWL",whichteam(tsA));
					break;
			}
			break;
		case 0: 
			switch(ser){
				case 0: 
					wprintw(scrbrd,"%s OPT TO BOWL",whichteam(tsB));
					break;
				case 1: 
					wprintw(scrbrd,"%s OPT TO BAT",whichteam(tsB));
					//tok = 1;
					break; 			
			}
			break;
	}
	scr = subwin(scrbrd,1,x,2,0);
	if(scr == NULL)
		wprintw(scrbrd,"POP");
	//waddstr(scr,"HI");
	if(batflag == 0)
		mvwprintw(scr,0,x/2-19,"%s :\t\tOVERS:\n",whichteam(tsB));
	else
		mvwprintw(scr,0,x/2-19,"%s :\t\tOVERS:\n",whichteam(tsA));
	//node *q;
	/*p11 = lA->head;
	while(p11!=NULL){
		wprintw(scrbrd,"%s %s %s\n",p11->attr,p11->fname,p11->lname);
		wrefresh(scrbrd);
		p11 = p11->next;
	}
	q11 = lB->head;
	while(q11!=NULL){
		wprintw(scrbrd,"%s %s %s\n",q11->attr,q11->fname,q11->lname);
		wrefresh(scrbrd);
		q11 = q11->next;
	}*/
	
	//wrefresh(scr);
	//wrefresh(scrbrd);
	if((tAbat == 1) && (tBbat == 0))
		t = p11 = lA->head;	
	if((tBbat == 1) && (tAbat == 0))
		t = q11 = lB->head;
	/*int i;
	for(i=0;i<2;i++){
		mvwprintw(batm,2+i,0,"%s %s %s",t->attr,t->fname,t->lname);
		t = t->next;
	}*/
	curr = subwin(scrbrd,1,100,5,1);
	mvwprintw(curr,0,1,"Current Run Rate: %f\t\tPartnership: %d(%d)\t\t\tProjected Score:%d\n",CRR,ps.scr,ps.balls,projscr);
	batm = subwin(scrbrd,5,135,9,1);	
	mvwprintw(batm,0,1,"BATSMAN\t\t\t\t\tRUNS \t\tBALLS  \t\t4's \t  6's    \t STRIKE RATE\n");
	bowl = subwin(scrbrd,4,135,15,1);	
	mvwprintw(bowl,0,1,"BOWLER \t\t\t\t\tOVERS\t\tMAIDENS\t\tRUNS\t  WICKETS\t ECONOMY\n");
	extras = subwin(scrbrd,4,30,23,1);
	mvwprintw(extras,0,0,"EXTRAS");
	mvwprintw(extras,1,0,"NOBALLS:  \tWIDES:  \nLEGBYES:  \tBYES:  \n");
	thisover = subwin(scrbrd,1,35,22,50);
	mvwprintw(thisover,0,0,"THIS OVER: 1 2 3 4 5 6 7 8 9 0\n");
	mvwprintw(scrbrd,28,0,"PRESS KEY '0 / 1 / 2 / 3 / 4 / 6' for 'DOTBALL / 1 / 2 / 3 / 4 / 6' RUNS RESPECTIVELY.\n\n");
	wprintw(scrbrd,"PRESS KEY 'w / n / o' for 'WIDES / NOBALL / WICKET' RESPECTIVELY.\n");
	mvwprintw(scrbrd,20,50,"BALL INPUT:");
	
	
	
	/*nextbatsman(1,0);
	nextbatsman(2,0);
	
	
	//char ball;
	ovr->bcount = 0;
	while(overno<over){
		if(ovr->bcount == 6){
			ovr->bcount = 0;
			overno++;
		}
		ball_input = getch();
		nextball(&ball_input);
	
	}
	/*if((tAbat == 1) && (tBbat == 0) && (choice1 == 0) && (res == 1) && ((tossr == 1) || (tossr == 0)))
		t = q = lA->head;
	if((tossr == 1) && (ser == 0) && (tAbat == 1) && (tBbat == 0))
		t = q = lA->head;*/
	
	/*if(((choice1 == 0) && (ser == 4)) || ((choice1==4) && (ser==0)))
		q = lA->head;
	if(((ser == 1) && (choice1 == 4)) || ((ser==4) && (choice1==1)) )
		q = lB->head;*/
	
		/*mvwprintw(batm,2,0,"%s %s %s",batsmanA->attr,batsmanA->fname,batsmanA->lname);
		mvwprintw(batm,2,42,"%d    \t\t%d\t\t\t%d    \t\t%d\t\t\t%f",batsmanA->runs,batsmanA->balls,batsmanA->fours,batsmanA->sixes,batsmanA->strikerate);
		mvwprintw(batm,3,0,"%s %s %s",batsmanB->attr,batsmanB->fname,batsmanB->lname);
		mvwprintw(batm,3,42,"%d    \t\t%d\t\t\t%d    \t\t%d\t\t\t%f",batsmanB->runs,batsmanB->balls,batsmanB->fours,batsmanB->sixes,batsmanB->strikerate);
	}
	batsmen = (batsman *)malloc(sizeof(struct batsman));
	strcpy(batsmen->attr,q->attr);
	strcpy(batsmen->fname,q->fname);
	strcpy(batsmen->lname,q->lname);
	batsmen->runs = batsmen->balls = batsmen->fours = batsmen->sixes = batsmen->strikerate = 0;*/
	
		//}/*mvwprintw(batm,2+i,42,"\t%d    \t\t%d\t\t\t%d    \t\t%d\t%f",batsmen[i].runs,batsmen[i].balls,batsmen[i].fours,batsmen[i].sixes,batsmen[i].strikerate);
	//}
	/*mvwprintw(batm,3,0,"%s %s %s",batsmanB->attr,batsmanB->fname,batsmanB->lname);
	mvwprintw(batm,3,42,"%d    \t\t%d\t\t\t%d    \t\t%d\t\t\t%f",batsmanB->runs,batsmanB->balls,batsmanB->fours,batsmanB->sixes,batsmanB->strikerate);*/
	
	//prevover = subwin(scrbrd,1,35,22,50);
	//mvwprintw(prevover,0,0,"PREV OVER: 1 2 3 4 5 6 7 8 9 0\n");
	//wrefresh(scr);
	//wrefresh(batm);
	//wrefresh(bowl);
	//wrefresh(curr);
	wrefresh(scrbrd);
	getch();	 
	
}		    
int main(){
	int menuitem;//tsA,tsB;
	initscr();
	screen(1);
	menuitem = sc1(1);
	switch(menuitem){
		case 0: up:tsA = teamselect(2);//values of tsA & tsB lies between 0...7
			tsB = teamselect(3);
			if(tsA == tsB){
				errorwin();
				refresh();
				wrefresh(wteamA);
				wrefresh(wteamB);
				goto up;
			}
			else

				TEAMname(tsA);
				token++;
				tok++;
				TEAMname(tsB);
				owpsf();
				toss();
				scrboard();	
			break;
		case 1: break;
		case 2: break;	
	}
	endwin();
	return 0;
}


