#include "config.h"

int main(int argc, char* argv[]){
        config conf = malloc(sizeof conf);
        clrscr();
        if(argc > 1){
                FILE* file = fopen(argv[1], "r");
                if(file == NULL){
                        printf("FILE %s not found. Matrix will be generated random\n", argv[1]);
                        chooseConfig(conf, false);
                }
                else
                        chooseConfig(conf, true);
                fclose(file);
        }
        else
                chooseConfig(conf, false);
        startGame(conf, argv[1]);
        free(conf);
        return 0;
}