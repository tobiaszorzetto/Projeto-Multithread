IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

LIBS=-lncurses

_DEPS = helper.h person.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o person.o helper.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 