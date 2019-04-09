CC = gcc
PNG = -lpng
RM = rm -f

default: all

all: Life

Life: main.c game.c logger.c config.c
	$(CC) -o Life main.c game.c logger.c config.c $(PNG)

clean veryclean:
	$(RM) Life