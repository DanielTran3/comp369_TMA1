#ifndef _POCKETTRIVIA_H
#define _POCKETTRIVIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <allegro.h>

#include "UserOptions.h"

#define MODE_WINDOWED GFX_AUTODETECT_WINDOWED
#define MODE_FULL GFX_AUTODETECT_FULLSCREEN

#define WIDTH 640
#define HEIGHT 480

#define CHARACTER_WIDTH 8
#define LINE_SPACING 10

#define TITLE "Pocket Trivia"
#define UNITS "otherTextfiles/units.txt"
#define CHAPTERS "otherTextfiles/chapters.txt"
#define QUESTIONS "questions/questions.txt"

#define WHITE makecol(255, 255, 255)
#define BLACK makecol(0, 0, 0)

void drawTitle();
void drawInstructions();
void readFile();
void fillFilenames(std::string filenameList[]);
void randomQuestion(const char *filename);
int print_long_text(const char *text, int x, int y);

#endif
