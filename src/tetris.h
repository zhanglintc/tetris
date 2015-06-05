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

#define CTRL_UP         72
#define CTRL_DOWN       80
#define CTRL_RIGHT      77
#define CTRL_LEFT       75
#define CTRL_SPACE      32
#define CTRL_ESC        27
#define CTRL_ENTER      13
#define CTRL_F5         63

#define ABSOLUTE_TOP    0
#define ABSOLUTE_BOTTOM 22
#define ABSOLUTE_LEFT   0
#define ABSOLUTE_RIGHT  60

#define FRAME_TOP       (ABSOLUTE_TOP)
#define FRAME_BOTTOM    (ABSOLUTE_BOTTOM)
#define FRAME_LEFT      (ABSOLUTE_LEFT)
#define FRAME_RIGHT     22

#define DASH_TOP        (ABSOLUTE_TOP)
#define DASH_BOTTOM     (ABSOLUTE_BOTTOM)
#define DASH_LEFT       (FRAME_RIGHT + 2)
#define DASH_RIGHT      (ABSOLUTE_RIGHT - 2)

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

// externals
extern char g_Local_Language[];

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

// declares
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

