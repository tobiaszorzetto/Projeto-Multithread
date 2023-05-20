#include "animation.h"

void animation_setup(){
    initscr();
    curs_set(0);
    initializeWindows();
}

void animation_subscribe(){
     for(int i=0; i<global_state->num_groups; i++){
        subscribe(global_state->individuals_queue_publishers[i], individuals_queue);
    }
    subscribe(global_state->groups_queue_publisher, groups_queue);
}

void individuals_queue(void* args){
    Queue_change* q_c = args;
    if(q_c->diff == 1){
        drawQueue();
    }
    else{
        drawQueue();
    }
}

void groups_queue(void* args){
    Queue_change* q_c = args;
    if(q_c->diff == 1){
        drawGroupsQueue();
    }
    else{
        sleep(2);
        runBoat(q_c->diff_elem);
    }
}

void initializeWindows() {
    drawRiverMargins();
    drawWaves();
    global_state->windows->boatWin = newwin(1, WIN_WIDTH, (BOT_MARGIN_POS+TOP_MARGIN_POS)/2, 0);
    global_state->windows->groupsQueueWin = newwin(1, WIN_WIDTH, BOT_MARGIN_POS + 1, 0);
    global_state->windows->individualsQueueWin = newwin(20, WIN_WIDTH, BOT_MARGIN_POS + 3, 0);
    refresh();
}


void *moveWaves() {
    int posx_wave = 0;
    time_t oldTime = time(NULL), currTime;
    char waves[] = "                  ~                     ~                     ~                         ~                     ";
    while(1) {
        currTime = time(NULL);
        if (currTime - oldTime == 1)
        {
            oldTime = currTime;
            posx_wave = !posx_wave;
            mvwprintw(global_state->windows->topWaves, 0, posx_wave, "%s", waves);
            mvwprintw(global_state->windows->botWaves, 0, !posx_wave, "%s", waves);
            wrefresh(global_state->windows->topWaves);
            wrefresh(global_state->windows->botWaves);
        }
    }
}

void drawRiverMargins() {
    global_state->windows->topMargin = newwin(1, WIN_WIDTH, TOP_MARGIN_POS, 0);
    global_state->windows->botMargin = newwin(1, WIN_WIDTH, BOT_MARGIN_POS, 0);
    refresh();
    char margin[] = "______________________________________________________________________________________________________________";
    mvwprintw(global_state->windows->topMargin, 0, 0, "%s", margin);
    mvwprintw(global_state->windows->botMargin, 0, 0, "%s", margin);
    wrefresh(global_state->windows->topMargin);
    wrefresh(global_state->windows->botMargin);
}

void drawWaves() {
    global_state->windows->topWaves = newwin(1, WIN_WIDTH, TOP_MARGIN_POS+2, 0);
    global_state->windows->botWaves = newwin(1, WIN_WIDTH, BOT_MARGIN_POS-2, 0);
    refresh();
    char waves[] = "                  ~                     ~                     ~                         ~                     ";
    mvwprintw(global_state->windows->topWaves, 0, 0, "%s", waves);
    mvwprintw(global_state->windows->botWaves, 0, 0, "%s", waves);
    wrefresh(global_state->windows->topWaves);
    wrefresh(global_state->windows->botWaves);
}

void drawQueue() {
    for(int i = 0; i < global_state->num_groups; i++){   
        mvwprintw(global_state->windows->individualsQueueWin, i, 0, "%s", getQueue(i));
    }
    wrefresh(global_state->windows->individualsQueueWin);
}

void drawGroupsQueue() {
    wclear(global_state->windows->groupsQueueWin);
    mvwprintw(global_state->windows->groupsQueueWin, 0, 0, "%s", getGroupsQueue());
    wrefresh(global_state->windows->groupsQueueWin);
}

char* getGroupsQueue() {
    char typeChar = 'A';
    
    char *fila = (char *)malloc(MAX_BOAT_SIZE);
    for (int i = 0; i < MAX_BOAT_SIZE; i++)
    {
        fila[i] = ' ';
    }

    for (int i = 0; i < global_state->groups_queue->size; i++)
    {
        fila[i*(global_state->group_size + 1)] = '|';
        Group* g = (global_state->groups_queue->items[i+global_state->groups_queue->front]);
        for (int j = 0; j < global_state->group_size; j++) {
            fila[i*5+j+1] = g->participants[j]->type + typeChar;
        }
    }
    return fila;
}

char *getBoat(Group* g)
{
    char *barco = (char *)malloc(MAX_BOAT_SIZE);
    barco[0] = '<';

    char s = 'A';

    for (int i = 1; i < MAX_BOAT_SIZE; i++)
    {
        barco[i] = ' ';
    }

    for (int i = 0; i < g->size; i++)
    {
        barco[i * 2 + 2] = s + g->participants[i]->type;
    }

    barco[(g->size) * 2 + 2] = '>';
    return barco;
}

char* getQueue(int type)
{
    char typeChar = 'A';
    typeChar += type;
    
    char *fila = (char *)malloc(MAX_BOAT_SIZE + 2);
    for (int i = 0; i < MAX_BOAT_SIZE; i++)
    {
        fila[i] = ' ';
    }
    fila[0] = typeChar;
    fila[1] = ':';
    fila[2] = ' ';
    for (int i = 0; i < global_state->individuals_queue[type]->size; i++)
    {
        fila[i * 2 + 3] = typeChar;
    }
    return fila;
}


void runBoat(Group* g)
{
    int posx = 0;
    char *boat = getBoat(g);

    while (posx != MARGIN_LEN - (global_state->group_size + 2))
    {
        mvwprintw(global_state->windows->boatWin, 0, posx, "%s", boat);
        wrefresh(global_state->windows->boatWin);
        posx++;
        usleep(50000);
        wclear(global_state->windows->boatWin);
        drawGroupsQueue();
    }
    wrefresh(global_state->windows->boatWin);
}