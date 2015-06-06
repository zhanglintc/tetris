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
int  g_Grid[GRID_WIDTH][GRID_HEIGHT] = {};

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
Function: Appearance deme of the game
Argument: None
Return  : Void
*******************************************************/
void display_demo() {
    COORD ref_coord = {8, 5};
    Cube *cube = new Cube(ref_coord, (COORD *)SHAPE_S);

    initialize();
    drawGame();

    drawOne( 6, 15, (char *)g_const_rect_b);
    drawOne( 8, 15, (char *)g_const_rect_b);
    drawOne( 8, 16, (char *)g_const_rect_b);
    drawOne(10, 16, (char *)g_const_rect_b);

    SetPos (34, 2); cout << "NEXT CUBE:";
    drawOne(36, 4,  (char *)g_const_rect_b);
    drawOne(38, 4,  (char *)g_const_rect_b);
    drawOne(36, 5,  (char *)g_const_rect_b);
    drawOne(38, 5,  (char *)g_const_rect_b);

    SetPos (34,  8); cout << "HIGH SCORE:";
    SetPos (36, 10); cout << "9999";

    SetPos (34, 13); cout << "  STATUS:";
    SetPos (34, 15); cout << " Pausing";

    for(int i = 0; i < 4; i++) {
        g_Grid[cube->getShape()[i].X / 2 + 4 ][cube->getShape()[i].Y + 3] = 1;
    }
    
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(g_Grid[i][j] == 1) {
                drawOne(i * 2 + 2, j + 1, (char *)g_const_rect_b);
            }
        }
    }

    char gotten;
    while(true) {
        if(_kbhit()){
            gotten=_getch();

            for(int i = 0; i < 4; i++) {
                SetPos(cube->getX() + cube->getShape()[i].X, cube->getY() + cube->getShape()[i].Y);
                cout << (char *)ICON_NULL;
            }

            switch(gotten) {
                case CTRL_UP:
                    if(cube->getTop() - 1 > FRAME_TOP)
                        cube->setY(cube->getY() - 1);
                    break;

                case CTRL_DOWN:
                    if(cube->getBottom() + 1 < FRAME_BOTTOM)
                        cube->setY(cube->getY() + 1);
                    break;

                case CTRL_LEFT:
                    if(cube->getLeft() - 2 > FRAME_LEFT)
                        cube->setX(cube->getX() - 2);
                    break;

                case CTRL_RIGHT:
                    if(cube->getRight() + 2 < FRAME_RIGHT)
                        cube->setX(cube->getX() + 2);
                    break;
            }

            for(int i = 0; i < 4; i++) {
                SetPos(cube->getX() + cube->getShape()[i].X, cube->getY() + cube->getShape()[i].Y);
                cout << g_const_rect_b;
            }
        }
    }
}

/*******************************************************
Function: main entrance
Argument: none
Return  : Int
*******************************************************/
int main() {
    display_demo();
    return 0;
}


