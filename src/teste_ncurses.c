#include <ncurses.h>
#include <unistd.h>
#include <string.h>
// #include <cstdlib>
#include <stdlib.h>
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
void runBoat(WINDOW *boatWin){	
  // initscr();			
  int groupsAntigo[2] = {4,4};
  int groups[2] = {2,2};
  int posx = 0, posy = 0;
  time_t oldTime = time(NULL), currTime;
  char *boat = getBoat(groups, groupsAntigo); 

  mvprintw(0,0, "%s", getQueue(groups, 0));
  mvprintw(13,0, "%s", getQueue(groups, 1));
  refresh();
  while(posx <= strlen("______________________________________________________________________________________________________________") - 3) {
    // mvprintw(1,0, "______________________________________________________________________________________________________________");	
    // mvprintw(3,posy, "                  ~                     ~                     ~                         ~                     ");
    wclear(boatWin);
    mvwprintw(boatWin, 0,posx, "%s", boat);
    wrefresh(boatWin);
    // mvprintw(6,!posy, "                  ~                     ~                     ~                         ~                     ");
    // mvprintw(7,0, "______________________________________________________________________________________________________________");
    currTime = time(NULL);
    // if (currTime - oldTime == 1) {
    //   oldTime = currTime;
    //   posy = !posy;
    // }
    posx++;	
    usleep(50000);
    // clear();
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
  // runBoat();
  initscr();	
  WINDOW *border = newwin(15, 150, 2, 0);
  WINDOW *waves = newwin(7, 150, 4, 0);
  WINDOW *boat = newwin(1, 150, 7, 0);

  refresh();
  mvwprintw(border, 0, 0, "______________________________________________________________________________________________________________");
  mvwprintw(border, 10, 0, "______________________________________________________________________________________________________________");
  wrefresh(border);
  sleep(1); 
  mvwprintw(waves, 1, 0, "                    ~                     ~                     ~                         ~                   ");
  mvwprintw(waves, 6, 0, "                  ~                     ~                     ~                         ~                     ");
  wrefresh(waves);
  sleep(3);
  runBoat(boat);
  endwin();
  return 0;
}