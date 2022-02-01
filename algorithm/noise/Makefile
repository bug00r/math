MAKE?=mingw32-make
AR?=ar
ARFLAGS?=rcs
PATHSEP?=/
CC=gcc
BUILDROOT?=build

ifeq ($(CLANG),1)
	export CC=clang
endif

BUILDDIR?=$(BUILDROOT)$(PATHSEP)$(CC)
BUILDPATH?=$(BUILDDIR)$(PATHSEP)

INSTALL_ROOT?=$(BUILDPATH)

ifeq ($(DEBUG),1)
	export debug=-ggdb -Ddebug=1
	export isdebug=1
endif

ifeq ($(ANALYSIS),1)
	export analysis=-Danalysis=1
	export isanalysis=1
endif

ifeq ($(DEBUG),2)
	export debug=-ggdb -Ddebug=2
	export isdebug=1
endif

ifeq ($(DEBUG),3)
	export debug=-ggdb -Ddebug=3
	export isdebug=1
endif

ifeq ($(OUTPUT),1)
	export outimg= -Doutput=1
endif

BIT_SUFFIX=

ifeq ($(M32),1)
	CFLAGS+=-m32
	BIT_SUFFIX+=32
endif

CFLAGS+=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra
#-ggdb
#-pg for profiling 

NAME=noise

LIBNAME=lib$(NAME).a
LIB=$(BUILDPATH)$(LIBNAME)
OBJS=$(BUILDPATH)$(NAME).o

INCLUDE?=-I/c/dev/include
INCLUDEDIR=$(INCLUDE) -I. 

LIBSDIR?=-L/c/dev/lib$(BIT_SUFFIX)

TESTBIN=$(BUILDPATH)test_$(NAME).exe
TESTLIB= -l$(NAME) -lfarray -larray -lstatistics -lutilsmath -lmat -lvec
TESTLIBDIR=-L$(BUILDDIR) $(LIBSDIR)

all: createdir $(LIB) $(TESTBIN)

$(LIB): $(OBJS) 
	$(AR) $(ARFLAGS) $@ $^

$(OBJS):
	$(CC) $(CFLAGS) -c $(@F:.o=.c) -o $@ $(INCLUDEDIR)

$(TESTBIN): $(LIB)
	$(CC) $(CFLAGS) $(@F:.exe=.c) -o $@ $(INCLUDEDIR) $(TESTLIBDIR) $(TESTLIB)

.PHONY: clean createdir test

createdir:
	mkdir -p $(BUILDDIR)

test:
	./$(TESTBIN)

clean:
	-rm -dr $(BUILDROOT)

install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib$(BIT_SUFFIX)
	cp ./$(NAME).h $(INSTALL_ROOT)include$(PATHSEP)$(NAME).h
	cp ./$(NAME)_base.h $(INSTALL_ROOT)include$(PATHSEP)$(NAME)_base.h
	cp ./$(NAME)_priv_diamond_square.h $(INSTALL_ROOT)include$(PATHSEP)$(NAME)_priv_diamond_square.h
	cp ./$(NAME)_priv_evolution.h $(INSTALL_ROOT)include$(PATHSEP)$(NAME)_priv_evolution.h
	cp ./$(NAME)_priv_midpoint_displacement.h $(INSTALL_ROOT)include$(PATHSEP)$(NAME)_priv_midpoint_displacement.h
	cp $(LIB) $(INSTALL_ROOT)lib$(BIT_SUFFIX)$(PATHSEP)$(LIBNAME)
