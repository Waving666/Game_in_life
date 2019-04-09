#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "stdbool.h"
#include "config.h"
#include <time.h>

void matGen(bool** , config );

bool cmpMat(bool** , bool** , config );

bool** Neumann(bool** , config );

bool** Moore(bool** , config );

void clrscr();

void printMatrix(bool** , config );

void startGame(config , char* );