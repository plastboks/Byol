CC=cc
CFLAGS=-Wall -Iinc -std=c99
LNFLAGS=-Wall -Iinc -W -Os -g
EFLAGS=-ledit -lm

ODIR=obj

_OBJ = lispy.o func.o mpc.o lenv.o lval.o builtins.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
_LN = linenoise.o
LN = $(patsubst %,$(ODIR)/%,$(_LN))

lispy: $(OBJ) $(LN)
	$(CC) -o $@ $^ $(EFLAGS)

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: linenoise/%.c $(DEPS)
	$(CC) -c -o $@ $< $(LNFLAGS)

# clean routine
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o lispy
