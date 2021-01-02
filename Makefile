CC = gcc
CFLAGS = -Wall -g
#SRCS = $(wildcard src/*.c) $(wildcard src/*/*.c)
SRCS = src/Main.c src/moduloD/manual.c src/moduloC/ModuloC.c src/moduloC/c_array.c src/moduloC/d_matrix.c src/moduloD/d_array.c #src/moduloT/ModuloT.c src/moduloT/ModuloT.h src/utils/Lista.c src/utils/Lista.h
OBJS = $(SRCS:.c=.o)
MAIN = shafa

.PHONY: depend clean

all:    $(MAIN)
	@echo  Shafa compiled

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) -lm

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $^
