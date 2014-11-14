CC=cc
CFLAGS=-Wall -Iinc -std=c99
EFLAGS=-ledit -lm

ODIR=obj

_OBJ = lispy.o func.o mpc.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

lispy: $(OBJ)
	$(CC) -o $@ $^ $(EFLAGS)

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


# clean routine
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o lispy
