#ifndef VARS_H
#define VARS_H

#include "raylib.h"

//Ball
const short velocityMinX = 300;
const short velocityMaxX = 500;
const short velocityMinY = 400;
const short velocityMaxY = 900;
const short minDirection = 1;
const short maxDirection = 4;

//ASCII 
const short zero = 48; //0
const short one = 49; //1
const short two = 50; //2
const short three = 51; //3
const short four = 52; //4
const short five = 53; //5
const short six = 54; //6
const short seven = 55; //7
const short eight = 56; //8
const short nine = 57; //9

//Screen
const short SDWidth = 640;
const short SDHeight = 480;
const short HDWidth = 1280;
const short HDHeight = 720;
const short FHDWidth = 1920;
const short FHDHeight = 1080;

//Enums
enum class scenes { game, menu, tutorial, paused, credits, exit, endGame };
enum class TexturesBall {one, two, three, four, five};
enum class TexturesPad {one, two, three, four, five};
enum class Movement { up, down, none };

//Buttons 
const Color recButtonColor = BLACK;
const Color recTextColor = ORANGE;
const Color recButtonColorTwo = ORANGE;
const Color recTextColorTwo = BLACK;

//Timer
const double initDTimer = 1;
const short initATimer[3] = {one, two, zero};
const Vector2 leftTimerPosition = { 520,72 };
const Vector2 middleTimerPosition = { 600,72 };
const Vector2 rightTimerPosition = { 680,72 };

//Score
const int initScoreToWin[2] = {two, one};
const Vector2 playerOnePositionLeftScore = { 360, 72 };
const Vector2 playerOnePositionRightScore = { 420, 72 };
const Vector2 playerTwoPositionLeftScore = { 800, 72 };
const Vector2 playerTwoPositionRightScore = { 860, 72 };

//Arrow Buttons
const int arrowButtonsWidth = 60;
const int arrowButtonsHeight = 60;

//Music 
const int stopMusicKey = KEY_M;

#endif
