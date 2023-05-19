IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

LIBS=-lncurses

_DEPS = actions.h change.h group.h grouping_algorithm.h person.h publisher.h queue.h state.h threads.h animation.h debugging.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = actions.o change.o group.o grouping_algorithm.o person.o publisher.o queue.o main.o state.o threads.o animation.o debugging.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 