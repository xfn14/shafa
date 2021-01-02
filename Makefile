CC = gcc
CFLAGS = -std=gnu11 -Wall -Wextra -pedantic-errors -O -g
#SRCS = $(wildcard src/*.c) $(wildcard src/*/*.c)

SRCS = src/Main.c src/moduloD/manual.c src/moduloC/ModuloC.c src/moduloC/c_array.c src/moduloC/d_matrix.c src/moduloD/d_array.c src/moduloD/moduloD.c src/moduloD/tree.c src/moduloD/auxiliar.c src/moduloF/moduloF.c src/utils/fsize.h #src/moduloT/ModuloT.c src/moduloT/ModuloT.h src/utils/Lista.c src/utils/Lista.h

OBJS = $(SRCS:.c=.o)
MAIN = shafa


all:    $(MAIN)  
	@echo "Shafa compiled"
		@ rm -f $(OBJS)

$(MAIN): $(OBJS) 
	@ $(CC) $(CFLAGS) -o $(MAIN) $(OBJS) -lm

.c.o:
	@ $(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $^
