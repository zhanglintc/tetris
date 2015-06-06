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

const COORD SHAPE_O[] = {
    {0, 0},                 // ■ □
    {2, 0},                 // □ □
    {0, 1},
    {2, 1},
};

const COORD SHAPE_T[] = {
    { 0, 0},                //   ■
    {-2, 1},                // □ □ □
    { 0, 1},
    { 2, 1},
};

const COORD SHAPE_S[] = {
    {0, 0},                 // ■
    {0, 1},                 // □ □
    {2, 1},                 //   □
    {2, 2},
};

// externals
extern char g_Local_Language[];
extern int  g_Grid[GRID_WIDTH][GRID_HEIGHT];

extern const uchar *g_const_circ_b;
extern const uchar *g_const_rect_b;
extern const uchar *g_const_rect_w;
extern const uchar *g_const_star_b;
extern const uchar *g_const_star_w;

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

// classes
class Cube {
public:
    void setCoord(int x, int y) {
        this->coord.X = x;
        this->coord.Y = y;
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

    COORD* getShape() {
        return this->shape;
    }

    int getTop() {
        return this->coord.Y + top;
    }

    int getBottom() {
        return this->coord.Y + bottom;
    }

    int getLeft() {
        return this->coord.X + left;
    }

    int getRight() {
        return this->coord.X + right;
    }

    Cube(COORD coord, COORD shape[]) {
        this->coord = coord;
        memcpy(this->shape, shape, 4 * sizeof(COORD));
        int minX = 0, minY = 0, maxX = 0, maxY = 0;
        for(int i = 0; i < 4; i++) {
            minX = this->shape[i].X < minX ? this->shape[i].X : minX;
            minY = this->shape[i].Y < minY ? this->shape[i].Y : minY;
            maxX = this->shape[i].X > maxX ? this->shape[i].X : maxX;
            maxY = this->shape[i].Y > maxY ? this->shape[i].Y : maxY;
        }

        top    = minY;
        bottom = maxY;
        left   = minX;
        right  = maxX;
    }

private:
    COORD coord;
    COORD shape[4];
    int top;
    int bottom;
    int left;
    int right;
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
int random(int a, int b);
COORD random(COORD leftup, COORD rightdown);
void swap(int *a, int *b);
void getLocalLanguage();
void initialize();
void playing();
void notSupported();

#endif //_TETRIS_H_

