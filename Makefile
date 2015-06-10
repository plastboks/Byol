#### Project settings ####
# Compilers
CC ?= gcc
TCC = tigcc
# Compiler flags
LFLAGS = -Wall -Iinc -std=c99
LNFLAGS = -Wall -Iinc -W -Os -g
EFLAGS = -lm
# Bin name
BIN_PATH = bin
BIN_NAME := lispy
# Object directory
ODIR = obj
# Standard library
LDIR = lib
# Destination directory
DEST_DIR = /
# Install path
INST_PFIX = usr
# Library path
GLIB_PFIX = usr/lib/$(BIN_NAME)

# Version macros
# Comment/remove this section to remove versioning
VERSION := $(shell git describe --tags --long --dirty --always | \
	sed 's/v\([0-9]*\)\.\([0-9]*\)\.\([0-9]*\)-\?.*-\([0-9]*\)-\(.*\)/\1 \2 \3 \4 \5/g')
VERSION_MAJOR := $(word 1, $(VERSION))
VERSION_MINOR := $(word 2, $(VERSION))
VERSION_PATCH := $(word 3, $(VERSION))
VERSION_REVISION := $(word 4, $(VERSION))
VERSION_HASH := $(word 5, $(VERSION))
VERSION_STRING := \
	"$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH).$(VERSION_REVISION)"
CGFLAGS := $(CCFLAGS) \
	-DVERSION_BUILD=\"$(VERSION_MAJOR)\" \
	-DGLIB_PFIX=\"$(DEST_DIR)$(GLIB_PFIX)\" \
	-DBUILD_DATE=\"$(shell date +'%Y-%m-%d\ %H:%M')\"
	#-D VERSION_MINOR=$(VERSION_MINOR) \
	#-D VERSION_PATCH=$(VERSION_PATCH) \
	#-D VERSION_REVISION=$(VERSION_REVISION) \
	#-D VERSION_HASH=\"$(VERSION_HASH)\"


_LSPY = lispy.o
_LN = linenoise.o
_OBJ = func.o mpc.o lenv.o lval.o builtins.o version.o config.o

OBJ_LIB = $(patsubst %,$(ODIR)/%,$(_OBJ))
OBJ_LN = $(patsubst %,$(ODIR)/%,$(_LN))
OBJ_LSPY = $(patsubst %,$(ODIR)/%,$(_LSPY))

$(ODIR)/%.o: src/%.c $(DEPS)
	@echo "=> Compiling source file"
	$(CC) -c -o $@ $< $(LFLAGS) $(CGFLAGS)

$(ODIR)/%.o: linenoise/%.c $(DEPS)
	@echo "=> Compiling linenoise source files"
	$(CC) -c -o $@ $< $(LNFLAGS)

.PHONY: lispy ti install clean

lispy: $(OBJ_LIB) $(OBJ_LN) $(OBJ_LSPY)
	@echo "=> Compiling release build: $(VERSION_STRING)"
	$(CC) -o $(BIN_PATH)/$(BIN_NAME) $^ $(EFLAGS)

install: 
	@echo "=> Installing $(BIN_NAME) to $(DEST_DIR)$(INST_PFIX)/bin"
	@install -m 0755 $(BIN_PATH)/$(BIN_NAME) $(DEST_DIR)$(INST_PFIX)/bin
	@echo "=> Copying lib files to $(DEST_DIR)$(GLIB_PFIX)"
	@mkdir -p $(DEST_DIR)$(GLIB_PFIX)
	@install -m 0644 $(LDIR)/* $(DEST_DIR)$(GLIB_PFIX)

clean:
	@echo "=> Removing binaries and o-files"
	rm -f $(ODIR)/*.o $(BIN_PATH)/*
