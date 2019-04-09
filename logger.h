#include "stdbool.h"
#include "config.h"
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <png.h>

void write_png_file();

void process_file(bool** , config conf);

void saveLog(bool**, config , int );

bool** loadLog(bool**, char* , config );

void removeOldLog();

void removeOldImage();