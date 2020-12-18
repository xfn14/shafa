CC = gcc
CFLAGS = -Wall -g
SRCS = src/Main.c src/moduloC/ModuloC.c src/moduloC/ModuloC.h #src/moduloT/ModuloT.c src/moduloT/ModuloT.h src/utils/Lista.c src/utils/Lista.h
OBJS = $(SRCS:.c=.o)
MAIN = shafa

.PHONY: depend clean

all:    $(MAIN)
	@echo  Simple compiler named shafa has been compiled

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $^

# DO NOT DELETE THIS LINE -- make depend needs it
