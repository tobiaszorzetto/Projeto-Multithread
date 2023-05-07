#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include <time.h>

#define MAX_BOAT_SIZE 50

char* getBoat(int* groups, int* groupsAntigo) {
  char *barco = (char *) malloc(MAX_BOAT_SIZE);
  barco[0] = '<';
  for (int i = 1; i < MAX_BOAT_SIZE; i++) {
    barco[i] = ' ';
  }
  for (int i = 0; i < groupsAntigo[0] - groups[0]; i++){
    barco[i*2+2] = 'H';
  }
  for (int i = groupsAntigo[0] - groups[0]; i < groupsAntigo[0] - groups[0] + groupsAntigo[1] - groups[1]; i++){
    barco[i*2+2] = 'M';
  }
  barco[(groupsAntigo[0] - groups[0] + groupsAntigo[1] - groups[1]) * 2 + 2] = '>';
  return barco;
}

char* getQueue(int* groups, int type) {
  char typeChar;
  if(type == 0 ){
    typeChar = 'H';
  } else{
    typeChar = 'M';
  }
  char *fila = (char *) malloc(MAX_BOAT_SIZE);
  for (int i = 0; i < MAX_BOAT_SIZE; i++) {
    fila[i] = ' ';
  }
  for (int i = 0; i < groups[type]; i++){
    fila[i*2] = typeChar;
  }
  return fila;
}
//   O
//  /|\H
//  /
void runBoat(){	
  initscr();			
  int groupsAntigo[2] = {4,4};
  int groups[2] = {2,2};
  int posx = 0, posy = 0;
  time_t oldTime = time(NULL), currTime;
  char *boat = getBoat(groups, groupsAntigo); 

  while(posx == strlen("______________________________________________________________________________________________________________") - 3) {
    mvprintw(0,0, "%s", getQueue(groups, 0));
    mvprintw(1,0, "______________________________________________________________________________________________________________");	
    mvprintw(3,posy, "                  ~                     ~                     ~                         ~                     ");
    mvprintw(4,posx, "%s", boat);
    mvprintw(6,!posy, "                  ~                     ~                     ~                         ~                     ");
    mvprintw(7,0, "______________________________________________________________________________________________________________");
    mvprintw(8,0, "%s", getQueue(groups, 1));
    currTime = time(NULL);
    if (currTime - oldTime == 1) {
      oldTime = currTime;
      posy = !posy;
    }
    posx++;	
    usleep(50000);
    refresh();
    clear();
  }
  refresh();
  endwin();

  return;
}

int formQueue(){	
  initscr();			
  int groups[2] = {2,2};
  int posx = 0;
  int posy = 0;

  for(int i = 0; i< 4; i++) {
    mvprintw(0,0, "%s", getQueue(groups, 0));
    mvprintw(1,0, "______________________________________________________________________________________________________________");	
    mvprintw(3,posy, "                  ~                     ~                     ~                         ~                     ");
    posy = !posy;
    mvprintw(6,posy, "                  ~                     ~                     ~                         ~                     ");
    mvprintw(7,0, "______________________________________________________________________________________________________________");
    mvprintw(8,0, "%s", getQueue(groups, 1));
    posx++;	
    sleep(1);
    refresh();
    clear();
  }
  refresh();
  endwin();

  return 0;
}

int main(){
  runBoat();
  return 0;
}