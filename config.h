#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Config{
    int col;
    int row;
    int n_it;
    char rule;
    bool out;
} *config;

void defaultConfig(config );

void userConfig(config , bool);

void chooseConfig(config , bool);

void fileConfig(config , char* );

void loadRowCol(config , char* );
#endif
