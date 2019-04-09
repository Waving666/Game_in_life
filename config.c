#include "config.h"

void defaultConfig(config conf){
    conf->col = 15;
    conf->row = 15;
    conf->n_it = 50;
    conf->rule = 'M';
    conf->out = 1; //'0' - "0 or 1"; '1' - "\u25d9 or \u25cb"
}

void userConfig(config conf, bool isSave){
    conf->row = conf->col = 0;
    //If we have configuration's file, we shouldn't type number of
    if(!isSave){
        printf("Number of rows (1 - 500): ");
        do{
            scanf("%d", &conf->row);
        } while (conf->row < 1 || conf->row > 500);
        printf("Number of columns (1 - 500): ");
        do{
            scanf("%d", &conf->col);
        } while(conf->col < 1 || conf->col > 500);
    }
    printf("Number of iterations (1 - inf): ");
    do{
        scanf("%d", &conf->n_it);
    } while(conf->n_it < 1);
    printf("Choose the rules (M - Moore / N - von Neuman): ");
    do{
        scanf(" %c", &conf->rule);
    } while(conf->rule != 'M' && conf->rule != 'N');
    printf("Choose outpoot method (1 - \u25d9 / \u25cb); 0 - 0 / 1: ");
    do{
        scanf("%d", &conf->out);
    } while(conf->out != 1 && conf->out != 0);
}

void chooseConfig(config conf, bool isSave){
    char temp;
    bool isOk;
    do{
        printf("Do you want to load configurations from file? (y/n)\n");
        scanf(" %c", &temp);
        if(temp == 'y'){
            isOk = true;
            char fname[20];
            printf("Please enter name of file: ");
            scanf(" %s", fname);
            fileConfig(conf, fname);
        }
        else if (temp == 'n'){
            do{
                printf("Do you want to setup default configuration? (y/n)\n");
                scanf(" %c", &temp);
                if(temp == 'y'){
                    defaultConfig(conf);
                    isOk = true;
                }
                else if(temp == 'n'){
                    userConfig(conf, isSave);
                    isOk = true;
                }
                else{
                    printf("Please type y or n\n");
                    isOk = false;
                }
                }while (isOk == false); 
            }
            else{
                printf("Please type y or n\n");
                isOk = false;
        }
                        
    }while (isOk == false);
}

void fileConfig(config conf, char* fname){
    FILE *file;
    bool isOk = true; 
    if(file = fopen(fname, "r"))
        file = fopen(fname, "r");
    else{
        printf("File %s not found. Configurations are setuped as default\n", fname);
        defaultConfig(conf);
        return;
    }
    isOk = fscanf(file, "%d%d%d%c%d", &conf->col, &conf->row, &conf->n_it, &conf->rule, &conf->out);
    if(conf->col < 0 || conf->col > 500)
        isOk = false;
    if(conf->row < 0 || conf->row > 500)
        isOk = false;
    if(conf->n_it < 1)
        isOk = false;
    if(conf->rule != 'M' && conf->rule != 'N')
        isOk = false;
    if(conf->out != 0 && conf->out != 1)
        isOk = false;
    if(!isOk){
        printf("ERROR! Bad format of configuration's file. Configurations are setuped as default\n");
        defaultConfig(conf);
        return;
    }

}

void loadRowCol(config conf, char* fname){
    FILE* file = fopen(fname, "r");
    fscanf(file, "%d%d", &conf->row, &conf->col);
    fclose(file);
}