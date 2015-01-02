CC=cc
LFLAGS=-Wall -Iinc -std=c99
LNFLAGS=-Wall -Iinc -W -Os -g
EFLAGS=-lm

ODIR=obj
TIDIR=ti

_LSPY = lispy.o
_OBJ = func.o mpc.o lenv.o lval.o builtins.o
_LN = linenoise.o
OBJ = $(patsubst %,$(ODIR)/%,$(_LSPY) $(_OBJ) $(_LN))
OBJT = $(patsubst %,$(ODIR)/%,$(_OBJ) $(_LN))

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(LFLAGS)

$(ODIR)/%.o: linenoise/%.c $(DEPS)
	$(CC) -c -o $@ $< $(LNFLAGS)

lispy: $(OBJ)
	$(CC) -o $@ $^ $(EFLAGS)

ti: $(OBJT)
	$(CC) -o $@ $^ $(EFLAGS)

# clean routine
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o lispy
