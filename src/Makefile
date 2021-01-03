CC = gcc
CFLAGS = -std=gnu11 -Wall -Wextra -pedantic-errors -O
#SRCS = $(wildcard *.c) $(wildcard */*.c)

SRCS = shafa.c moduloD/manual.c moduloC/ModuloC.c moduloC/c_array.c moduloC/d_matrix.c moduloD/d_array.c moduloD/moduloD.c moduloD/tree.c moduloD/auxiliar.c moduloF/moduloF.c utils/fsize.c moduloT/ModuloT.c utils/Lista.c utils/Pares.c

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
