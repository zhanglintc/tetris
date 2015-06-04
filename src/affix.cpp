/*
 Some frequency use functions here.   http://zhanglintc.co
(C) COPYRIGHT 2015-06-04 ZhangLin. Nothing reserved.
*/

#include "tetris.h"

/*******************************************************
Function: display a single icon
Argument: int, int, char[]
Return  : void
*******************************************************/
void drawOne(int x, int y, char ch[]) {
    SetPos(x, y);
    cout << ch;
}

/*******************************************************
Function: set cursor's position
Argument: COORD
Return  : void
*******************************************************/
void SetPos(COORD position) { // set cursor 
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(out, position);
}

/*******************************************************
Function: set cursor's position
Argument: int, int
Return  : void
*******************************************************/
void SetPos(int x, int y) { // set cursor 
    COORD position = {x, y};
    SetPos(position);
}

/*******************************************************
Function: hide consoler's cursor
Argument: none
Return  : void
*******************************************************/
void HideCursor() { // hide cursor 
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

/*******************************************************
Function: set y, [x1, x2) as ch
Argument: int, int, int, char[]
Return  : void
*******************************************************/
void drawRow(int y, int x1, int x2, char ch[]) { // by zhanglin
    SetPos(x1,y);
    for(int i = 0; i <= (x2 - x1); i += 2) {
        cout << ch;
    }
}

/*******************************************************
Function: when left, right y equal, set [left, right] as ch
Argument: COORD, COORD, char[]
Return  : void
*******************************************************/
void drawRow(COORD left, COORD right, char ch[]) { // by zhanglin
    if(left.Y == right.Y)
        drawRow(left.Y, left.X, right.X, ch);

    else {
        SetPos(0, 25);
        cout << "error code 01: \'x\' not equaled";
        system("pause");
    }
}

/*******************************************************
Function: set x, [y1, y2] as ch
Argument: int, int, int, char[]
Return  : void
*******************************************************/
void drawCol(int x, int y1, int y2, char ch[]) { // by zhanglin
    int y = y1;

    while(y != y2) {
        SetPos(x, y);
        cout << ch;
        y++;
    }
}

/*******************************************************
Function: when left, right x equal, set [left, right] as ch
Argument: COORD, COORD, char[]
Return  : void
*******************************************************/
void drawCol(COORD left, COORD right, char ch[]) { // by zhanglin
    if(left.X == right.X)
        drawCol(left.X, left.Y, right.Y, ch);

    else {
        SetPos(0, 25);
        cout << "error code 02: \'y\' not equaled";
        system("pause");
    }
}

/*******************************************************
Function: from left-up to right-down, set row using row, set col using col
Argument: COORD, COORD, char[]
Return  : void
*******************************************************/
void drawFrame(COORD leftup, COORD  rightdown, char row[], char col[]) {
    drawRow(   leftup.Y, leftup.X, rightdown.X, row);       // first row
    drawRow(rightdown.Y, leftup.X, rightdown.X, row);       // last row
    drawCol(   leftup.X, leftup.Y, rightdown.Y, col);       // first col
    drawCol(rightdown.X, leftup.Y, rightdown.Y, col);       // last col
}

/*******************************************************
Function: draw a rectangle frame
Argument: int, int, int, int, char[], char[]
Return  : void
*******************************************************/
void drawFrame(int x1, int y1, int x2, int y2, char row[], char col[]) {
    COORD leftup = {x1, y1};
    COORD rightdown = {x2, y2};
    drawFrame(leftup, rightdown, row, col);
}

/*******************************************************
Function: draw a rectangle frame
Argument: Frame, char[], char[]
Return  : void
*******************************************************/
void drawFrame(Frame frame, char row[], char col[]) {
    COORD leftup = frame.position[0];
    COORD rightdown = frame.position[1];
    drawFrame(leftup, rightdown, row, col);
}

/*******************************************************
Function: generate a random number
Argument: int, int
Return  : int
*******************************************************/
int random(int min, int max) {
    if(max < min) swap(&min, &max);
    if(min == max) return min;
    else return(rand() % (min - max)) + min;
}

/*******************************************************
Function: generate a random position
Argument: COORD, COORD
Return  : COORD
*******************************************************/
COORD random(COORD leftup, COORD rightdown) {
    int x = random(leftup.X, rightdown.X);
    int y = random(leftup.Y, rightdown.Y);
    COORD c = {x, y};
    return c;
}

/*******************************************************
Function: swap two numbers
Argument: int, int
Return  : void
*******************************************************/
void swap(int *a, int *b) {
    int m;
    m = *a;
    *a = *b;
    *b = m;
}

/*******************************************************
Function: read the registry info and get the system language info, set the info to a global variable
Argument: none
Return  : void
*******************************************************/
void getLocalLanguage() {
    FILE *fp;
    char language[10] = {};
    char str[] = "@echo off && for /f \"tokens=3\" %i in (\'reg query \"HKCU\\Control Panel\\International\" /v \"sLanguage\"\') do (echo %i>lan.txt)";
    system("echo=>lan.txt");
    system(str);
    fp = fopen("lan.txt","r");
    fscanf(fp,"%s", language);
    fclose(fp);
    system("del lan.txt");
    memcpy(g_Local_Language, language, sizeof(language));
}

/*******************************************************
Function: show system language not supported screen and exit
Argument: none
Return  : void
*******************************************************/
void notSupported() {
    system("cls");
    SetPos(20, 10);
    char str[] = "The system language is not supported!";
    cout << str << endl;
    getchar();
    exit(0);
}


