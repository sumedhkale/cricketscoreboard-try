#include <ncurses.h>			  
#include <string.h> 
int main(){
	int i = 0;
	char content[]="THIS OVER";		
	char ch;
	int row,col;				
	initscr();				
	getmaxyx(stdscr,row,col);		
	mvprintw(row/2,(col-strlen(content))/2,"%s",content);
 
	while( (ch = getch()) != 27 ){                     		
		if(ch == 'w'){
			attron(A_UNDERLINE | A_BOLD);						
      			mvprintw(LINES - 2,i+2,"%c", ch);
			attroff(A_UNDERLINE | A_BOLD);
			goto next;	
		}  
 		mvprintw(LINES - 2, i+2, "%c", ch);
		next:i++;
		if(i == 6)
			break;
	}	 	
	getch();
 	endwin();
	return 0;
}
