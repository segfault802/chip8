#include <ncurses.h>



int main()
{
	int row,col,y,x,yM,xM;
	int i,j;	
	yM = 32;
	xM = 64;
	initscr();
	getmaxyx(stdscr,row,col);
	for(i=0;i<yM;i++){
		for(j=0;j<xM;j++){
			mvaddch(i,j,(' ' | A_REVERSE));
			//mvaddch(i,j,A_REVERSE);
		}
	}
	getch();
	endwin();
	printf("rows: %d, cols: %d\n",row,col);
	return 0;	
}
/*
//test it
int main()
{
	printRow(0xF0);
	printf("\n");
	printRow(0x90);
	printf("\n");
	printRow(0x90);
	printf("\n");
	printRow(0x90);
	printf("\n");
	printRow(0xF0);
	printf("\n");
}*/
