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
int  g_SCORE = 0;
CubeGenerator *g_CubeGenerator;
Cube *g_CUR_CUBE;
Cube *g_NEXT_CUBE;
Grid g_GRID[GRID_WIDTH][GRID_HEIGHT] = {};
Grid g_GRID_BAK[GRID_WIDTH][GRID_HEIGHT] = {};
Shape SHAPE_O = {1, {(COORD *)SHAPE_O_1}};
Shape SHAPE_I = {2, {(COORD *)SHAPE_I_1, (COORD *)SHAPE_I_2}};
Shape SHAPE_T = {4, {(COORD *)SHAPE_T_1, (COORD *)SHAPE_T_2, (COORD *)SHAPE_T_3, (COORD *)SHAPE_T_4}};
Shape SHAPE_S = {2, {(COORD *)SHAPE_S_1, (COORD *)SHAPE_S_2}};
Shape SHAPE_2 = {2, {(COORD *)SHAPE_2_1, (COORD *)SHAPE_2_2}};
Shape SHAPE_L = {4, {(COORD *)SHAPE_L_1, (COORD *)SHAPE_L_2, (COORD *)SHAPE_L_3, (COORD *)SHAPE_L_4}};
Shape SHAPE_J = {4, {(COORD *)SHAPE_J_1, (COORD *)SHAPE_J_2, (COORD *)SHAPE_J_3, (COORD *)SHAPE_J_4}};

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

    // initialize global varibals
    memset(g_GRID,     0, sizeof(g_GRID));
    memset(g_GRID_BAK, 0, sizeof(g_GRID_BAK));
    g_SCORE = 0;

    // initialize icons
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

    g_CubeGenerator = new CubeGenerator();
    g_CubeGenerator->loadShape(SHAPE_O);
    g_CubeGenerator->loadShape(SHAPE_I);
    g_CubeGenerator->loadShape(SHAPE_T);
    g_CubeGenerator->loadShape(SHAPE_S);
    g_CubeGenerator->loadShape(SHAPE_2);
    g_CubeGenerator->loadShape(SHAPE_L);
    g_CubeGenerator->loadShape(SHAPE_J);

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

bool isInCube(COORD pos, Cube *cube) {
    for(int i = 0; i < 4; i++) {
        if(pos.X == cube->getX() + cube->getShapes()[cube->cur_type][i].X && pos.Y == cube->getY() + cube->getShapes()[cube->cur_type][i].Y) {
            return true;
        }
    }

    return false;
}

void cleanShape(Cube *cube) {
    for(int i = 0; i < 4; i++) {
        g_GRID[cube->getX() + cube->getShapes()[cube->cur_type][i].X][cube->getY() + cube->getShapes()[cube->cur_type][i].Y].show = 0;
    }
}

void setShape(Cube *cube) {
    for(int i = 0; i < 4; i++) {
        g_GRID[cube->getX() + cube->getShapes()[cube->cur_type][i].X][cube->getY() + cube->getShapes()[cube->cur_type][i].Y].show = 1;
    }
}

void moveGridDown(int tergetY) {
    for(int y = tergetY; y >= 0; y--) {
        for(int x = 0; x < GRID_WIDTH; x++) {
            if(y == 0) {
                g_GRID[x][y].show = 0;
            }
            else {
                g_GRID[x][y] = g_GRID[x][y - 1];
            }
        }
    }
}

int checkGrid() {
    for(int y = 0; y < GRID_HEIGHT; y++) {
        while(  g_GRID[0][y].show && g_GRID[1][y].show &&
                g_GRID[2][y].show && g_GRID[3][y].show && 
                g_GRID[4][y].show && g_GRID[5][y].show &&
                g_GRID[6][y].show && g_GRID[7][y].show &&
                g_GRID[8][y].show && g_GRID[9][y].show) {
            g_SCORE += 10;
            SetPos (FRAME_RIGHT + 9, 12); cout << g_SCORE;
            moveGridDown(y);
        }
    }

    return g_SCORE;
}

bool isValidShapePos(Cube *cube) {
    COORD c;

    for(int i = 0; i < 4; i++) {
        c.X = cube->getCoord().X + cube->getShapes()[cube->cur_type][i].X;
        c.Y = cube->getCoord().Y + cube->getShapes()[cube->cur_type][i].Y;

        // hit dormant cubes?
        if(g_GRID[c.X][c.Y].show == 1) {
            return false;
        }

        // out of bound?
        if(c.X < 0 || c.X >= GRID_WIDTH || c.Y < 0 || c.Y >= GRID_HEIGHT) {
            return false;
        }
    }

    return true;
}

void ctrl_up(Cube *cube) {
    int tmp = cube->cur_type;

    cleanShape(cube);
    cube->cur_type += 1;
    if(cube->cur_type >= cube->type_len) {
        cube->cur_type = 0;
    }

    if(isValidShapePos(cube) == false) {
        cube->cur_type = tmp; // restore it
    }
    else {
        ; // do nothing
    }
    setShape(cube);
}

Cube *ctrl_down(Cube *cube) {
    // cleanShape(cube);
    // if(cube->getBottom() + 1 < GRID_HEIGHT) {
    //     if(g_GRID[cube->getX()][cube->getBottom() + 1].show == YES) {
    //         setShape(cube);
    //         free(cube);
    //         COORD ref_coord = {4, 0};
    //         cube = new Cube(ref_coord, (COORD *)SHAPE_I_2);
    //         setShape(cube);
    //         return cube;
    //     }
    //     else {
    //         cube->setCoord(cube->getX(), cube->getY() + 1);
    //     }
    // }
    // setShape(cube);
    cleanShape(cube);
    COORD c;
    for(int i = 0; i < 4; i++) {
        c.X = cube->getCoord().X + cube->getShapes()[cube->cur_type][i].X;
        c.Y = cube->getCoord().Y + cube->getShapes()[cube->cur_type][i].Y + 1;
        if(
            // if reach blocks
            isInCube(c, cube) == false && g_GRID[cube->getCoord().X + cube->getShapes()[cube->cur_type][i].X][cube->getCoord().Y + 1 + cube->getShapes()[cube->cur_type][i].Y].show == 1
            // if reach bottom
            || cube->getCoord().Y + 1 + cube->getShapes()[cube->cur_type][i].Y >= GRID_HEIGHT) {
            setShape(cube);
            // free(cube);
            COORD ref_coord = {4, 2};
            // cube = new Cube(ref_coord, SHAPE_T.shape, SHAPE_T.types);
        
            cube = g_NEXT_CUBE;
            if(isValidShapePos(cube) == false) {
                gameOver();
            }
            Shape *s = createShape();
            g_NEXT_CUBE = new Cube(ref_coord, s->shape, s->types);
            // g_NEXT_CUBE = new Cube(ref_coord, SHAPE_T.shape, SHAPE_T.types);
            // int index = random(0, g_CubeGenerator->getLength());
            // g_NEXT_CUBE = new Cube(ref_coord, g_CubeGenerator->getShapeList()[index].shape, g_CubeGenerator->getShapeList()[index].types);
            checkGrid();
            setShape(cube);
            return cube;
        }        
    }
    cube->setCoord(cube->getX(), cube->getY() + 1);
    checkGrid();
    cube = ctrl_down(cube);
    setShape(cube);
    return cube;
}

void ctrl_left(Cube *cube) {
    cleanShape(cube);

    cube->moveLeft();
    if(isValidShapePos(cube) == false) {
        cube->moveRight(); // move back
    }
    else {
        ; // do nothing
    }

    setShape(cube);
}

void ctrl_right(Cube *cube) {
    cleanShape(cube);

    cube->moveRight();
    if(isValidShapePos(cube) == false) {
        cube->moveLeft(); // move back
    }
    else {
        ; // do nothing
    }

    setShape(cube);
}

void backupGrid() {
    memcpy(g_GRID_BAK, g_GRID, sizeof(g_GRID));
}

void drawGrid() {
    for(int x = 0; x < GRID_WIDTH; x++) {
        for(int y = 0; y < GRID_HEIGHT; y++) {
            if(g_GRID[x][y].show == YES && g_GRID_BAK[x][y].show == NO) {
                drawOne(x * 2 + 2, y + 1, (char *)g_const_rect_b);
            }
            else if(g_GRID[x][y].show == NO && g_GRID_BAK[x][y].show == YES){
                drawOne(x * 2 + 2, y + 1, (char *)ICON_NULL);
            }
        }
    }
}

void drawNEXT(Cube *cube) {
    SetPos (FRAME_RIGHT + 6, 2); cout << "NEXT CUBE";

    COORD c = {FRAME_RIGHT + 9, 5};
    for(int i = 0; i < 4; i++) {
		drawOne(c.X + cube->getShapes()[cube->cur_type][i].X * 2, c.Y + cube->getShapes()[cube->cur_type][i].Y, (char *)g_const_rect_b);
    }
}

void cleanNEXT(Cube *cube) {
    COORD c = {FRAME_RIGHT + 9, 5};
    for(int i = 0; i < 4; i++) {
        drawOne(c.X + cube->getShapes()[cube->cur_type][i].X * 2, c.Y + cube->getShapes()[cube->cur_type][i].Y, (char *)ICON_NULL);
    }
}

Shape *createShape() {
    int r = random(g_CubeGenerator->getLength());
    return &g_CubeGenerator->getShapeList()[r];
}

void gameOver() {
    system("cls");
    SetPos(17, 10); cout << "Game over";
    SetPos(13, 11); cout << "Press space to replay...";
    while(_kbhit() || !_kbhit()) {
        if(CTRL_SPACE == _getch()) {
            break;
        }
    }
    displayDemo();
}

/*******************************************************
Function: Appearance deme of the game
Argument: None
Return  : Void
*******************************************************/
void displayDemo() {
    initialize();

    COORD ref_coord = {4, 2};
    // Cube *cube = new Cube(ref_coord, SHAPE_T.shape, SHAPE_T.types);
    Shape *next = createShape();
    Shape *curr = createShape();
    g_NEXT_CUBE = new Cube(ref_coord, next->shape, next->types);
    g_CUR_CUBE =  new Cube(ref_coord, curr->shape, curr->types);

    drawGame();

    // set g_GRID, test code
    // for(int i = 0; i < 10; i++) {
    //     g_GRID[i][20].show = YES;
    //     g_GRID[i][19].show = YES;
    //     g_GRID[i][18].show = YES;
    // }

    drawNEXT(g_NEXT_CUBE);

    SetPos (FRAME_RIGHT + 5, 10); cout << "HIGH SCORE";
    SetPos (FRAME_RIGHT + 9, 12); cout << g_SCORE;

    SetPos (FRAME_RIGHT + 8, 17); cout << "STATUS";
    SetPos (FRAME_RIGHT + 7, 19); cout << "Playing";

    // // set g_GRID, test code
    // for(int i = 0; i < 4; i++) {
    //     g_GRID[cube->getShapes()[0][i].X + 4][cube->getShapes()[0][i].Y + 3].show = YES;
    // }

    setShape(g_CUR_CUBE);

    checkGrid();
    drawGrid();

    int counter = 0;

    char gotten;
    while(true) {

        counter++;
        if(counter >= 30000) {
            backupGrid();
            cleanShape(g_CUR_CUBE);
            g_CUR_CUBE->moveDown();
            if(isValidShapePos(g_CUR_CUBE) == false) {
                // move back && setShape
                g_CUR_CUBE->moveUp();
                setShape(g_CUR_CUBE);

                // get next cube && draw it
                g_CUR_CUBE = g_NEXT_CUBE;
                if(isValidShapePos(g_CUR_CUBE) == false) {
                    gameOver();
                }
                Shape *s = createShape();
                g_NEXT_CUBE = new Cube(ref_coord, s->shape, s->types);
                cleanNEXT(g_CUR_CUBE);
                drawNEXT(g_NEXT_CUBE);
            }
            else {
                ; // do nothing
            }
            setShape(g_CUR_CUBE);
            drawGrid();
            counter = 0;
        }

        if(_kbhit()){
            gotten=_getch();
            backupGrid();
            switch(gotten) {
                case CTRL_UP:
                    ctrl_up(g_CUR_CUBE);
                    break;

                case CTRL_DOWN:
                    g_CUR_CUBE = ctrl_down(g_CUR_CUBE);
                    cleanNEXT(g_CUR_CUBE);
                    drawNEXT(g_NEXT_CUBE);
                    break;

                case CTRL_LEFT:
                    ctrl_left(g_CUR_CUBE);
                    break;

                case CTRL_RIGHT:
                    ctrl_right(g_CUR_CUBE);
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


