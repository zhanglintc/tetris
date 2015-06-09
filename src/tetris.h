/*
 All the defines and declares.   http://zhanglintc.co
(C) COPYRIGHT 2015-06-04 ZhangLin. Nothing reserved.
*/

#ifndef _TETRIS_H_
#define _TETRIS_H_

// includes
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

// defines
#define uchar unsigned char

#define CTRL_UP             72
#define CTRL_DOWN           80
#define CTRL_RIGHT          77
#define CTRL_LEFT           75
#define CTRL_SPACE          32
#define CTRL_ESC            27
#define CTRL_ENTER          13
#define CTRL_F5             63

#define ABSOLUTE_TOP        0
#define ABSOLUTE_BOTTOM     22
#define ABSOLUTE_LEFT       0
#define ABSOLUTE_RIGHT      60

#define FRAME_TOP           (ABSOLUTE_TOP)
#define FRAME_BOTTOM        (ABSOLUTE_BOTTOM)
#define FRAME_LEFT          (ABSOLUTE_LEFT)
#define FRAME_RIGHT         22

#define DASH_TOP            (ABSOLUTE_TOP)
#define DASH_BOTTOM         (ABSOLUTE_BOTTOM)
#define DASH_LEFT           (FRAME_RIGHT + 2)
#define DASH_RIGHT          (ABSOLUTE_RIGHT - 2)

#define GRID_WIDTH          10
#define GRID_HEIGHT         21

#define YES                 1
#define NO                  0

// typedefs
typedef struct Frame {
    COORD position[2];
    int flag;
}Frame;

typedef struct Node {
    int x;
    int y;
}Node;

typedef struct Rank {
    char name[20];
    int score;
}Rank;

typedef struct Grid {
    int show;
    int stat;
}Grid;

typedef struct Shape {
    int   types;
    COORD *shape[4];
}Shape;

// constants
const uchar ICON_NULL[] = {"  "}; // nothing here, means clean one place

/* Chinese */
const uchar CIRC_CHA_B[] = {0xa1, 0xf1, 0}; // ●
const uchar RECT_CHA_B[] = {0xa1, 0xf6, 0}; // ■
const uchar RECT_CHA_W[] = {0xa1, 0xf5, 0}; // □
const uchar STAR_CHA_B[] = {0xa1, 0xef, 0}; // ★
const uchar STAR_CHA_W[] = {0xa3, 0xaa, 0}; // ※

/* Japanese */
const uchar CIRC_JPN_B[] = {0x81, 0x9c, 0}; // ●
const uchar RECT_JPN_B[] = {0x81, 0xa1, 0}; // ■
const uchar RECT_JPN_W[] = {0x81, 0xa0, 0}; // □
const uchar STAR_JPN_B[] = {0x81, 0x9a, 0}; // ★
const uchar STAR_JPN_W[] = {0x81, 0x96, 0}; // ※

//////////////////////////////////// SHAPE_O ====> S
const COORD SHAPE_O_1[] = {
    {0, 0},                 // ■ □
    {1, 0},                 // □ □
    {0, 1},
    {1, 1},
};
//////////////////////////////////// SHAPE_O ====> E

//////////////////////////////////// SHAPE_T ====> S
const COORD SHAPE_T_1[] = {
    { 0,  0},                //   □
    { 0, -1},                // □ ■ □
    { 1,  0},
    {-1,  0},
};
const COORD SHAPE_T_2[] = {
    { 0,  0},                // □
    { 0, -1},                // ■ □
    { 1,  0},                // □
    { 0,  1},
};
const COORD SHAPE_T_3[] = {
    { 0,  0},                // □ ■ □
    { 1,  0},                //   □
    { 0,  1},
    {-1,  0},
};
const COORD SHAPE_T_4[] = {
    { 0,  0},                //   □
    { 0, -1},                // □ ■
    { 0,  1},                //   □
    {-1,  0},
};
//////////////////////////////////// SHAPE_T ====> E

//////////////////////////////////// SHAPE_S ====> S
const COORD SHAPE_S_1[] = {
    { 0, 0},                 //   ■ □
    { 1, 0},                 // □ □
    { 0, 1}, 
    {-1, 1},
};
const COORD SHAPE_S_2[] = {
    {0,  0},                 // □
    {0, -1},                 // ■ □
    {1,  0},                 //   □
    {1,  1},
};
//////////////////////////////////// SHAPE_S ====> E

//////////////////////////////////// SHAPE_2 ====> S
const COORD SHAPE_2_1[] = {
    { 0, 0},                 // □ ■
    { 1, 1},                 //   □ □
    { 0, 1},
    {-1, 0},
};
const COORD SHAPE_2_2[] = {
    { 0,  0},                 //   □
    { 0, -1},                 // □ ■
    {-1,  1},                 // □
    {-1,  0},
};
//////////////////////////////////// SHAPE_2 ====> E

//////////////////////////////////// SHAPE_L ====> S
const COORD SHAPE_L_1[] = {
    {0,  0},                 // □
    {0, -1},                 // □
    {0, -2},                 // ■ □
    {1,  0},
};
const COORD SHAPE_L_2[] = {
    {0,  0},                 // ■ □ □
    {1,  0},                 // □
    {2,  0},
    {0,  1},
};
const COORD SHAPE_L_3[] = {
    { 0, 0},                 // □ ■
    { 0, 1},                 //   □
    { 0, 2},                 //   □
    {-1, 0},
};
const COORD SHAPE_L_4[] = {
    { 0,  0},                 //     □
    { 0, -1},                 // □ □ ■
    {-1,  0},
    {-2,  0},
};
//////////////////////////////////// SHAPE_J ====> E

const COORD SHAPE_J_1[] = {
    { 0,  0},                 //   □
    { 0, -1},                 //   □
    { 0, -2},                 // □ ■
    {-1,  0},
};
const COORD SHAPE_J_2[] = {
    {0,  0},                 // □
    {0, -1},                 // ■ □ □
    {1,  0},
    {2,  0},
};
const COORD SHAPE_J_3[] = {
    { 0, 0},                 // ■ □
    { 1, 0},                 // □
    { 0, 1},                 // □
    { 0, 2},
};
const COORD SHAPE_J_4[] = {
    { 0,  0},                 // □ □ ■
    { 0,  1},                 //     □
    {-1,  0},
    {-2,  0},
};
//////////////////////////////////// SHAPE_J ====> E

//////////////////////////////////// SHAPE_I ====> S
const COORD SHAPE_I_1[] = {
    {0, 0},                 // ■
    {0, 1},                 // □
    {0, 2},                 // □
    {0, 3},                 // □
};
const COORD SHAPE_I_2[] = {
    {0, 0},                 // ■ □ □ □
    {1, 0},
    {2, 0},
    {3, 0},
};
//////////////////////////////////// SHAPE_I ====> E

// externals
extern char g_Local_Language[];
extern Grid g_Grid[GRID_WIDTH][GRID_HEIGHT];
extern Grid g_Grid_Bak[GRID_WIDTH][GRID_HEIGHT];

extern const uchar *g_const_circ_b;
extern const uchar *g_const_rect_b;
extern const uchar *g_const_rect_w;
extern const uchar *g_const_star_b;
extern const uchar *g_const_star_w;

// classes
class Cube {
public:
    int cur_type;
    int type_len;

    void setCoord(int x, int y) {
        this->coord.X = x;
        this->coord.Y = y;
    }

    COORD getCoord() {
        return this->coord;
    }

    void setX(int x) {
        this->coord.X = x;
    }

    void setY(int y) {
        this->coord.Y = y;
    }

    int getX() {
        return this->coord.X;
    }

    int getY() {
        return this->coord.Y;
    }

    void moveUp() {
        this->coord.Y -= 1;
    }

    void moveDown() {
        this->coord.Y += 1;
    }

    void moveLeft() {
        this->coord.X -= 1;
    }

    void moveRight() {
        this->coord.X += 1;
    }

    // COORD* getShape() {
    //     return this->shape;
    // }

    COORD** getShapes() {
        return this->shapes;
    }

    Cube(COORD coord, /*COORD shape[],*/ COORD **shapes, int type_len) {
        this->coord = coord;
        // memcpy(this->shape, shape, 4 * sizeof(COORD));
        this->shapes = shapes;
        this->type_len = type_len;
        this->cur_type = 0;
    }

private:
    COORD coord;
    // COORD shape[4];
    COORD **shapes;
};

class CubeGenerator {
public:
    int getLength() {
        return this->length;
    }

    void loadShape(Shape shape) {
        shapeList[this->length] = shape;
        length += 1;
    }

    Shape* getShapeList() {
        return this->shapeList;
    }

    CubeGenerator() {
        this->length = 0;
    }
private:
    Shape shapeList[20];
    int   length;
};

// declares
void drawOne(int x, int y, char ch[]);
void SetPos(COORD a);
void SetPos(int i, int j);
void HideCursor();
void drawRow(int y, int x1, int x2, char ch[]);
void drawRow(COORD a, COORD b, char ch[]);
void drawCol(int x, int y1, int y2, char ch[]);
void drawCol(COORD a, COORD b, char ch[]);
void drawFrame(COORD a, COORD  b, char row[], char col[]);
void drawFrame(int x1, int y1, int x2, int y2, char row[], char col[]);
void drawFrame(Frame frame, char row[], char col[]);
int random(int min, int max);
int random(int max);
COORD random(COORD leftup, COORD rightdown);
Shape *createShape();
void swap(int *a, int *b);
void getLocalLanguage();
void initialize();
void playing();
void notSupported();
int checkGrid();
void displayDemo();

#endif //_TETRIS_H_

