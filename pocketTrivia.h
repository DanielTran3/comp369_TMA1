#ifndef _POCKETTRIVIA_H
#define _POCKETTRIVIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <allegro.h>

#include "UserOptions.h"
#include "Sound.h"

#define MODE_WINDOWED GFX_AUTODETECT_WINDOWED
#define MODE_FULL GFX_AUTODETECT_FULLSCREEN

#define WIDTH 640
#define HEIGHT 480

#define CHARACTER_WIDTH 8
#define LINE_SPACING 10
#define NUM_BACKGROUNDS 10

#define TITLE "Pocket Trivia"
#define UNITS "otherTextfiles/units.txt"
#define CHAPTERS "otherTextfiles/chapters.txt"
#define QUESTIONS "questions/questions.txt"
#define TITLE_IMAGE "images/title.pcx"
#define CORRECT_IMAGE "images/correct_image.pcx"
#define INCORRECT_IMAGE "images/correct_image.pcx"

#define WHITE makecol(255, 255, 255)
#define BLACK makecol(0, 0, 0)
#define LIGHT_GREEN makecol(100, 255, 0)
#define RED makecol(255, 0, 0)

int convertKeyPress();
void highlightKey(std::string line, int xOffset, int newLineSpacing, int color);
void drawImage(const char * filename);
void drawRandomImage();
void drawTitle();
void drawFinal(UserOptions *user);
void displayInstructions();
void displayUserInformation(UserOptions *user);
void chooseQuizType(UserOptions *user);
void chooseUnit(UserOptions *user);
void chooseChapter(UserOptions *user);
void chooseNumberOfQuestions(UserOptions *user);
void randomQuestion(const char *filename, int &answer, int questionNumber, TriviaInfo *triviaInfo);
void checkAnswer(UserOptions *user, int userAnswer, int answer, Sound *soundEffect, TriviaInfo *triviaInfo);
void generateMultipleRandomQuestions(UserOptions *user, Sound *soundEffect, TriviaInfo *triviaInfo);
int print_long_text(const char *text, int x, int y);
int print_long_text(const char *text, int x, int y, int lineMultiple, int textColor);
int getHorizontalSpacing(const char *text);
void draw_pretty_box(const char * textToMeasure, int x, int y, int offset_x, int offset_y, int numLines);
#endif
