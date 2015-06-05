/*
 Main process here.  http://zhanglintc.co
(C) COPYRIGHT 2015-06-04 ZhangLin. Nothing reserved.
*/

#include "tetris.h"

// these variables are assigned in function Initialize()
uchar const *g_const_circ_b;    // global ●
uchar const *g_const_rect_b;    // global ■
uchar const *g_const_rect_w;    // global □
uchar const *g_const_star_b;    // global ★
uchar const *g_const_star_w;    // global ※

// global variable declares
char g_Local_Language[10];      // global language info

/*******************************************************
Function: initialize, set color, hide cursor, get system language, copy icon data
Argument: none
Return  : void
*******************************************************/
void initialize() {
    char con_size[30] = {};
    sprintf(con_size, "mode con cols=%d lines=%d", ABSOLUTE_RIGHT + 1, ABSOLUTE_BOTTOM + 1);
    system (con_size);
    system ("title Tetris Game by Lane at ZDS");
    system ("color 3e"); // set color
    system ("cls");      // clean screen

    HideCursor();       // hide cursor
    getLocalLanguage(); // get local language information

    //initialize icons
    if(!strcmp(g_Local_Language, "CHS") && !strcmp(g_Local_Language, "JPN")) {
        notSupported(); // if not supported, stop in NotSupport() function
    }

    else if(!strcmp(g_Local_Language, "CHS")) {
        g_const_circ_b = CIRC_CHA_B;
        g_const_rect_b = RECT_CHA_B;
        g_const_rect_w = RECT_CHA_W;
        g_const_star_b = STAR_CHA_B;
        g_const_star_w = STAR_CHA_W;
    }

    else if(!strcmp(g_Local_Language, "JPN")) {
        g_const_circ_b = CIRC_JPN_B;
        g_const_rect_b = RECT_JPN_B;
        g_const_rect_w = RECT_JPN_W;
        g_const_star_b = STAR_JPN_B;
        g_const_star_w = STAR_JPN_W;
    }

    srand((unsigned)time(NULL));        // Random number seed initial
}

/*******************************************************
Function: draw the game frame
Argument: none
Return  : void
*******************************************************/
void drawGame() {
    system("cls");

    drawFrame(FRAME_LEFT, FRAME_TOP, FRAME_RIGHT, FRAME_BOTTOM, (char *)g_const_rect_w, (char *)g_const_rect_w);  // outside frame
    drawFrame( DASH_LEFT,  DASH_TOP,  DASH_RIGHT,  DASH_BOTTOM, (char *)g_const_star_w, (char *)g_const_star_w);  // dashboard frame
}

/*******************************************************
Function: play game
Argument: none
Return  : void
*******************************************************/
void playing() {
    ;
}

/*******************************************************
Function: main entrance
Argument: none
Return  : int
*******************************************************/
int main() {
    initialize();
    drawGame();
    playing();
    while(true);
    return 0;
}


