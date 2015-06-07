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
Grid g_Grid[GRID_WIDTH][GRID_HEIGHT] = {};
Grid g_Grid_Bak[GRID_WIDTH][GRID_HEIGHT] = {};

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

void cleanShape(Cube *cube) {
    for(int i = 0; i < 4; i++) {
        g_Grid[cube->getX() + cube->getShape()[i].X][cube->getY() + cube->getShape()[i].Y].show = 0;
    }
}

void setShape(Cube *cube) {
    for(int i = 0; i < 4; i++) {
        g_Grid[cube->getX() + cube->getShape()[i].X][cube->getY() + cube->getShape()[i].Y].show = 1;
    }
}

int checkGrid() {
    int score = 0;

    for(int y = GRID_HEIGHT - 1; y >= 0; y--) {
        if(g_Grid[0][y].show && g_Grid[1][y].show && g_Grid[2][y].show && g_Grid[3][y].show) {
            score += 1;
        }
    }

    return score;
}

void ctrl_up(Cube *cube) {
    cleanShape(cube);
    if(cube->getTop() - 1 >= 0) {
        cube->setCoord(cube->getX(), cube->getY() - 1);
    }
    setShape(cube);
}

void ctrl_down(Cube *cube) {
    cleanShape(cube);
    if(cube->getBottom() + 1 < GRID_HEIGHT) {
        cube->setCoord(cube->getX(), cube->getY() + 1);
    }
    setShape(cube);
}

void ctrl_left(Cube *cube) {
    cleanShape(cube);
    if(cube->getLeft() - 1 >= 0) {
        cube->setCoord(cube->getX() - 1, cube->getY());
    }
    setShape(cube);
}

void ctrl_right(Cube *cube) {
    cleanShape(cube);
    if(cube->getRight() + 1 < GRID_WIDTH) {
        cube->setCoord(cube->getX() + 1, cube->getY());
    }
    setShape(cube);
}

void backupGrid() {
    memcpy(g_Grid_Bak, g_Grid, sizeof(g_Grid));
}

void drawGrid() {
    for(int x = 0; x < GRID_WIDTH; x++) {
        for(int y = 0; y < GRID_HEIGHT; y++) {
            if(g_Grid[x][y].show == YES && g_Grid_Bak[x][y].show == NO) {
                drawOne(x * 2 + 2, y + 1, (char *)g_const_rect_b);
            }
            else if(g_Grid[x][y].show == NO && g_Grid_Bak[x][y].show == YES){
                drawOne(x * 2 + 2, y + 1, (char *)ICON_NULL);
            }
        }
    }
}

/*******************************************************
Function: Appearance deme of the game
Argument: None
Return  : Void
*******************************************************/
void displayDemo() {
    COORD ref_coord = {4, 5};
    Cube *cube = new Cube(ref_coord, (COORD *)SHAPE_O_NEW);

    initialize();
    drawGame();

    // drawOne( 6, 15, (char *)g_const_rect_b);
    // drawOne( 8, 15, (char *)g_const_rect_b);
    // drawOne( 8, 16, (char *)g_const_rect_b);
    // drawOne(10, 16, (char *)g_const_rect_b);

    // set g_Grid, test code
    for(int i = 0; i < 10; i++) {
        g_Grid[i][20].show = YES;
        g_Grid[i][19].show = YES;
        g_Grid[i][18].show = YES;
    }

    SetPos (34, 2); cout << "NEXT CUBE:";
    drawOne(36, 4,  (char *)g_const_rect_b);
    drawOne(38, 4,  (char *)g_const_rect_b);
    drawOne(36, 5,  (char *)g_const_rect_b);
    drawOne(38, 5,  (char *)g_const_rect_b);

    SetPos (34,  8); cout << "HIGH SCORE:";
    SetPos (36, 10); cout << checkGrid();

    SetPos (34, 13); cout << "  STATUS:";
    SetPos (34, 15); cout << " Pausing";

    // // set g_Grid, test code
    // for(int i = 0; i < 4; i++) {
    //     g_Grid[cube->getShape()[i].X / 2 + 4][cube->getShape()[i].Y + 3].show = YES;
    // }
    setShape(cube);

    checkGrid();
    drawGrid();

    char gotten;
    while(true) {
        if(_kbhit()){
            gotten=_getch();
            backupGrid();
            switch(gotten) {
                case CTRL_UP:
                    // if(cube->getTop() - 1 > FRAME_TOP) {
                    //     cube->setY(cube->getY() - 1);
                    // }
                    ctrl_up(cube);
                    break;

                case CTRL_DOWN:
                    // if(cube->getBottom() + 1 < FRAME_BOTTOM) {
                    //     cube->setY(cube->getY() + 1);
                    // }
                    ctrl_down(cube);
                    break;

                case CTRL_LEFT:
                    // if(cube->getLeft() - 2 > FRAME_LEFT) {
                    //     cube->setX(cube->getX() - 2);
                    // }
                    ctrl_left(cube);
                    break;

                case CTRL_RIGHT:
                    // if(cube->getRight() + 2 < FRAME_RIGHT) {
                    //     cube->setX(cube->getX() + 2);
                    // }
                    ctrl_right(cube);
                    break;
            }
            drawGrid();
        }
    }
}

/*******************************************************
Function: main entrance
Argument: none
Return  : Int
*******************************************************/
int main() {
    displayDemo();
    return 0;
}


