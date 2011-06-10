#include <curses.h>			/* ncurses.h includes stdio.h */  
#include <string.h> 
 
int main()
{
 char mesg[]="Just a string";		/* message to be appeared on the screen */
 int row,col;				/* to store the number of rows and *
					 * the number of colums of the screen */
 initscr();				/* start the curses mode */
 getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
 mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
                                	/* print the message at the center of the screen */
 mvprintw(row-3,0,"This screen has %d rows and %d columns\n",row,col);
 mvprintw(row-2,0,"Try resizing your window(if possible) and then run this program again");
 attron(A_BOLD);
 mvprintw(1,1,"Ligne 1 row 1");
 attroff(A_BOLD);
 //printw("Try resizing your window(if possible) and then run this program again");
 refresh();
 getch();
 endwin();

 return 0;
}

