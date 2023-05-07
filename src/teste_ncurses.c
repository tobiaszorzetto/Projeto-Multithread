#include <ncurses.h>
#include <unistd.h>
#include <string.h>

int main(){	
  initscr();			
  int posx = 0, hack = 2, microsoft = 2;
  char barco[11] = "< x x x x >";
  while(1) {
    if (posx == strlen("______________________________________________________________________________________________________________") - 3) {
        posx = 0;
    }
    mvprintw(0,0, "______________________________________________________________________________________________________________");	
    mvprintw(2,0, "                  ~                     ~                     ~                         ~                     ");
    int i;
    mvprintw(3,posx, "< H H M M >");
    mvprintw(7,0, "______________________________________________________________________________________________________________");
    posx++;	
    usleep(50000);
    refresh();
    clear();
  }
  refresh();
  endwin();

  return 0;
}