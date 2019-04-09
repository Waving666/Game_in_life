#include "logger.h"

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

void write_png_file(int n_it) {
    char fname[20];
    snprintf(fname, 20, "images/image_%d%s", n_it, ".png");
    FILE *fp = fopen(fname, "wb");
    if (!fp)
        printf("[write_png_file] File %s could not be opened for writing", fname);

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
        printf("[write_png_file] png_create_write_struct failed");

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        printf("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during init_io");

    png_init_io(png_ptr, fp);

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during writing header");

    png_set_IHDR(png_ptr, info_ptr, width, height,
    bit_depth, color_type, PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during writing bytes");

    png_write_image(png_ptr, row_pointers);

    if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    for (y=0; y<height; y++)
        free(row_pointers[y]);
    free(row_pointers);

    fclose(fp);
}

void process_file(bool** matrix, config conf) {
    width = conf->row;
    height = conf->col;
    bit_depth = 8;
    color_type = PNG_COLOR_TYPE_GRAY;

    number_of_passes = 7;
    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (y=0; y<height; y++)
        row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * width);

    for (y=0; y<height; y++) {
        png_byte* row = row_pointers[y];
        for (x=0; x<width; x++) {
            if(matrix[y+1][x+1] == 1)
                row[x] = 255;
            else if (matrix[y+1][x+1] == 0)
                row[x] = 0;
        }
    }
}

void removeOldImage(){
    int i = 0;
    char fname[20], gifname[20];
    do{
        snprintf(fname, 20, "images/image_%d%s", i, ".png");
        i++;
    }while(remove(fname) == 0);
    do{
        snprintf(fname, 20, "images/game%s", ".gif");
    }while(remove(fname) == 0);
}

void saveLog(bool** matrix, config conf, int n_it){
    char fname[20];
    snprintf(fname, 20, "log/log_%d%s", n_it, ".txt");
    FILE *file = fopen(fname, "w");
    fprintf(file, "%d %d\n", conf->row, conf->col);
    for(int i = 1; i <= conf->row; i++){
        for(int j = 1; j <= conf->col; j++)
            fprintf(file, "%d ", matrix[i][j]);
        fprintf(file, "\n");
    }
    fclose(file);
}

bool** loadLog(bool** matrix, char* fname, config conf){
    FILE* file = fopen(fname, "r");
    for(int i = 1; i <= conf->row; i++)
        for(int j = 1; j <= conf->col; j++){
            fscanf(file, "%d", &matrix[i][j]);
            printf("%d\n", matrix[i][j]);
        }
    return matrix;
}

void removeOldLog(){
    int i = 0;
    char fname[20];
    do{
        snprintf(fname, 20, "log/log_%d%s", i, ".txt");
        i++;
    }while(remove(fname) == 0);
}