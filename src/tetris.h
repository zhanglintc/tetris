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
using namespace std;

// defines
#define CTRL_UP         72
#define CTRL_DOWN       80
#define CTRL_RIGHT      77
#define CTRL_LEFT       75
#define CTRL_SPACE      32
#define CTRL_ESC        27
#define CTRL_ENTER      13
#define CTRL_F5         63

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
char* getLocalLanguage();

#endif //_TETRIS_H_

