#include "game.h"
#include "logger.h"

void matGen(bool** matrix, config conf){
    srand(time(NULL));
    for(int i = 1; i <= conf->row; i++)
        for (int j = 1; j <= conf->col; j++)
            matrix[i][j] = rand() % 2;
}

bool cmpMat(bool** matrix1, bool** matrix2, config conf){
    for(int i = 1; i <= conf->row; i++)
        for(int j = 1; j <= conf->col; j++)
            if(matrix1[i][j] != matrix2[i][j])
                return true;
    return false;
}

bool** Neumann (bool** matrix, config conf) {
    int sum;
    // Creating temporary matrix
    bool ** tempMat = malloc(conf->row*sizeof(bool*) + conf->row*conf->col*sizeof(bool));
    char * pc = tempMat;
    pc += conf->row*sizeof(bool*);
    for (int i = 1; i <= conf->row; i++)
        tempMat[i] = pc + i*sizeof(conf->col*sizeof(bool));
    for (int i = 1 ; i <= conf->row; i++)
        for (int j = 1; j <= conf->col; j++)
            tempMat[i][j] = matrix[i][j];

    for (int i = 1 ; i <= conf->row; i++) {
        for (int j = 1; j <= conf->col; j++) {

                    // Death of points

            if (matrix[i][j] == 1 && i == 1 && j > 1 && j < conf->col) {
                sum = 0;
                sum = matrix[i][j-1] + matrix[i][j+1] + matrix[i+1][j];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && i == conf->row && j > 1 && j < conf->col) {
                sum = 0;
                sum = matrix[i-1][j] + matrix[i][j-1] + matrix[i][j+1];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && j == 1 && i > 1 && i < conf->row) {
                sum = 0;
                sum = matrix[i-1][j] + matrix[i+1][j] + matrix[i][j+1];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && j == conf->col && i > 1 && i < conf->row) {
                sum = 0;
                sum = matrix[i][j-1] + matrix[i-1][j] + matrix[i+1][j];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && i > 1 && j > 1 && i < conf->row && j < conf->col) {
                sum = 0;
                sum = matrix[i-1][j]+ matrix[i][j-1] + matrix[i][j+1] + matrix[i+1][j];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && i == 1 && j == 1) {
                sum = 0;
                sum = matrix[i][j+1] + matrix[i+1][j];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && i == 1 && j == conf->col) {
                sum = 0;
                sum = matrix[i+1][j] + matrix[i][j-1];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && i == conf->row && j == 1) {
                sum = 0;
                sum = matrix[i-1][j] + matrix[i][j+1];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && i == conf->row && j == conf->col) {
                sum = 0;
                sum = matrix[i][j-1] + matrix[i-1][j];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            // Points reviving
            if (matrix[i][j] == 0 && i == 1 && j > 1 && j < conf->col) {
                sum = 0;
                sum = matrix[i][j-1] + matrix[i][j+1] + matrix[i+1][j];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && i == conf->row && j > 1 && j < conf->col) {
                sum = 0;
                sum = matrix[i-1][j] + matrix[i][j-1] + matrix[i][j+1];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && j == 1 && i > 1 && i < conf->row) {
                sum = 0;
                sum = matrix[i-1][j] + matrix[i+1][j] + matrix[i][j+1];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && j == conf->col && i > 1 && i < conf->row) {
                sum = 0;
                sum = matrix[i][j-1] + matrix[i-1][j] + matrix[i+1][j];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && i > 1 && j > 1 && i < conf->row && j < conf->col) {
                sum = 0;
                sum = matrix[i-1][j]+ matrix[i][j-1] + matrix[i][j+1] + matrix[i+1][j];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && i == 1 && j == 1) {
                sum = 0;
                sum = matrix[i][j+1] + matrix[i+1][j];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && i == 1 && j == conf->col) {
                sum = 0;
                sum = matrix[i+1][j] + matrix[i][j-1];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && i == conf->row && j == 1) {
                sum = 0;
                sum = matrix[i-1][j] + matrix[i][j+1];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && i == conf->row && j == conf->col) {
                sum = 0;
                sum = matrix[i][j-1] + matrix[i-1][j];
                if (sum == 3) tempMat[i][j] = 1;
            }
        } 
    }
    printMatrix(tempMat, conf);
    if(!cmpMat(matrix, tempMat, conf)){
        for(int i = 1; i <= conf->row; i++)
            for(int j = 1; j <= conf->col; j++)
                tempMat[i][j] = 0;
    }
    for(int i = 1; i <= conf->row; i++)
            for(int j = 1; j <= conf->col; j++)
                matrix[i][j] = tempMat[i][j];
    free(tempMat);
    return matrix;
}

bool** Moore (bool** matrix, config conf){
    int sum;
    // Creating temporary matrix
    bool ** tempMat = malloc(conf->row*sizeof(bool*) + conf->row*conf->col*sizeof(bool));
    char * pc = tempMat;
    pc += conf->row*sizeof(bool*);
    for (int i = 1; i <= conf->row; i++)
        tempMat[i] = pc + i*sizeof(conf->col*sizeof(bool));
    for (int i = 1 ; i <= conf->row; i++)
        for (int j = 1; j <= conf->col; j++)
            tempMat[i][j] = matrix[i][j];

    for (int i = 1 ; i <= conf->row; i++) {
        for (int j = 1; j <= conf->col; j++) {

            // Death of points

            if (matrix[i][j] == 1 && i == 1 && j > 1 && j < conf->col) {
                sum = 0;
                sum = matrix[i][j-1] + matrix[i][j+1] + matrix[i+1][j-1] + matrix[i+1][j] + matrix[i+1][j+1];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && i == conf->row && j > 1 && j < conf->col) {
                sum = 0;
                sum = matrix[i-1][j-1] + matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j-1] + matrix[i][j+1];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && j == 1 && i > 1 && i < conf->row) {
                sum = 0;
                sum = matrix[i-1][j] + matrix[i+1][j] + matrix[i-1][j+1] + matrix[i][j+1] + matrix[i+1][j+1];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && j == conf->col && i > 1 && i < conf->row) {
                sum = 0;
                sum = matrix[i-1][j-1] + matrix[i][j-1] + matrix[i+1][j-1] + matrix[i-1][j] + matrix[i+1][j];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && i > 1 && j > 1 && i < conf->row && j < conf->col) {
                sum = 0;
                sum = matrix[i-1][j-1] + matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j-1] + matrix[i][j+1] + 
                matrix[i+1][j-1] + matrix[i+1][j] + matrix[i+1][j+1];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && i == 1 && j == 1) {
                sum = 0;
                sum = matrix[i][j+1] + matrix[i+1][j] + matrix[i+1][j+1];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && i == 1 && j == conf->col) {
                sum = 0;
                sum = matrix[i+1][j] + matrix[i][j-1] + matrix[i+1][j-1];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && i == conf->row && j == 1) {
                sum = 0;
                sum = matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j+1];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }
            if (matrix[i][j] == 1 && i == conf->row && j == conf->col) {
                sum = 0;
                sum = matrix[i][j-1] + matrix[i-1][j] + matrix[i-1][j-1];
                if (sum != 2 && sum != 3) tempMat[i][j] = 0;
            }



            // Points reviving

            if (matrix[i][j] == 0 && i == 1 && j > 1 && j < conf->col) {
                sum = 0;
                sum = matrix[i][j-1] + matrix[i][j+1] + matrix[i+1][j-1] + matrix[i+1][j] + matrix[i+1][j+1];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && i == conf->row && j > 1 && j < conf->col) {
                sum = 0;
                sum = matrix[i-1][j-1] + matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j-1] + matrix[i][j+1];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && j == 1 && i > 1 && i < conf->row) {
                sum = 0;
                sum = matrix[i-1][j] + matrix[i+1][j] + matrix[i-1][j+1] + matrix[i][j+1] + matrix[i+1][j+1];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && j == conf->col && i > 1 && i < conf->row) {
                sum = 0;
                sum = matrix[i-1][j-1] + matrix[i][j-1] + matrix[i+1][j-1] + matrix[i-1][j] + matrix[i+1][j];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && i > 1 && j > 1 && i < conf->row && j < conf->col) {
                sum = 0;
                sum = matrix[i-1][j-1] + matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j-1] + matrix[i][j+1] + 
                matrix[i+1][j-1] + matrix[i+1][j] + matrix[i+1][j+1];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && i == 1 && j == 1) {
                sum = 0;
                sum = matrix[i][j+1] + matrix[i+1][j] + matrix[i+1][j+1];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && i == 1 && j == conf->col) {
                sum = 0;
                sum = matrix[i+1][j] + matrix[i][j-1] + matrix[i+1][j-1];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && i == conf->row && j == 1) {
                sum = 0;
                sum = matrix[i-1][j] + matrix[i-1][j+1] + matrix[i][j+1];
                if (sum == 3) tempMat[i][j] = 1;
            }
            if (matrix[i][j] == 0 && i == conf->row && j == conf->col) {
                sum = 0;
                sum = matrix[i][j-1] + matrix[i-1][j] + matrix[i-1][j-1];
                if (sum == 3) tempMat[i][j] = 1;
            }
        } 
    }
    printMatrix(tempMat, conf);
    if(!cmpMat(matrix, tempMat, conf)){
        for(int i = 1; i <= conf->row; i++)
            for(int j = 1; j <= conf->col; j++)
                tempMat[i][j] = 0;
    }
    for(int i = 1; i <= conf->row; i++)
            for(int j = 1; j <= conf->col; j++)
                matrix[i][j] = tempMat[i][j];
    free(tempMat);
    return matrix;
}

void clrscr()
{
    #ifdef _WIN32
    system("@cls");
    #else
    system("clear");
    #endif
}

void printMatrix(bool** matrix, config conf){
    clrscr();
    for (int i = 1 ; i <= conf->row; i++){
        for (int j = 1; j <= conf->col; j++){
            if(conf->out == 0)
                printf("%d ", matrix[i][j]);
            else{
                if(matrix[i][j] == 1)
                    printf("\u25d9 ");
                else printf("\u25cb ");
            }
        }
    printf("\n");
    }
    printf("\n");
    //Sleep cmd  
    #ifdef _WIN32
    Sleep(100);
    #else
    usleep(200000);
    #endif
}

void startGame(config conf, char* saveName){
    if(saveName != NULL)
        loadRowCol(conf, saveName);
    //Memory for matrix
    bool ** matrix = malloc(conf->row * sizeof(bool*) + conf->row * conf->col * sizeof(bool));
    char * pc = matrix;
    pc += conf->row*sizeof(bool*);
    for (int i = 1; i <= conf->row; i++)
        matrix[i] = pc + i * sizeof(conf->col * sizeof(bool));
    if(saveName == NULL)
        matGen(matrix, conf);
    else
        matrix = loadLog(matrix, saveName, conf);
    removeOldLog();
    removeOldImage();
    int i = 0;
    bool isContinue = true;
    while(i < conf->n_it && isContinue){
        if(conf->rule == 'N')
            matrix = Neumann(matrix, conf);
        else if (conf->rule == 'M')
            matrix = Moore(matrix, conf);
        int sum = 0;
        saveLog(matrix, conf, i);
        process_file(matrix, conf);
        write_png_file(i);
        for (int k = 1 ; k <= conf->row; k++)
            for (int j = 1; j <= conf->col; j++)
                sum += matrix[k][j];
        isContinue = sum;
        i++;
    } 
    free(matrix);
    //Making *.gif
    system("convert -delay 20 -loop 0 images/*.png images/game.gif");
}