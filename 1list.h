#include"OVER.h"
typedef struct info{
	int matches;
	batsman batsmn;
	bowler bowlr;
}profile;
typedef struct node {
	char attr[5];
	char fname[20];
	char lname[20];
	struct node *next, *prev;
	struct info *prof;
}node;
typedef struct list {
	struct node *head, *tail;
	int length;
	int initlen;
}list;
void init(list *l);
//void traverse(list *l);
void insert(list *l, char *attr,char *fname,char *lname, int pos);
int length(list *l);
/*char *remov(list *l, int pos);
void append(list *l, char *str);
int length(list *l);
void reverse(list *l);
void sort(list *l);*/
