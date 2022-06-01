IDIR=../include
ODIR=obj
CC=gcc

CFLAGS=-I$(IDIR) -Wall -Werror

_DEPS = SimpleApp.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = SimpleAppServer.o SimpleAppClient.o SimpleAppMain.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

SimpleApp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 