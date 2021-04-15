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

CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra
#-ggdb
#-pg for profiling 

SRC=noise.c

LIBNAME=libnoise.a
OBJS=noise.o

INCLUDE?=-I/c/dev/include
INCLUDEDIR=$(INCLUDE) -I. 

LIB?=-L/c/dev/lib

TESTSRC=test_noise.c
TESTBIN=test_noise.exe
TESTLIB= -lnoise -lfarray -larray -lstatistics -lutilsmath -lmat -lvec
TESTLIBDIR=-L$(BUILDDIR) $(LIB)

all: createdir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN) test

$(BUILDPATH)$(LIBNAME): $(BUILDPATH)$(OBJS) 
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(OBJS)

$(BUILDPATH)$(OBJS):
	$(CC) $(CFLAGS) -c $(SRC) -o $(BUILDPATH)$(OBJS) $(INCLUDEDIR)

$(BUILDPATH)$(TESTBIN):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(INCLUDEDIR) $(TESTLIBDIR) $(TESTLIB)

.PHONY: clean createdir test

createdir:
	mkdir -p $(BUILDDIR)

test:
	./$(BUILDPATH)$(TESTBIN)

clean:
	-rm -dr $(BUILDROOT)

install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib
	cp ./noise.h $(INSTALL_ROOT)include/noise.h
	cp ./noise_base.h $(INSTALL_ROOT)include/noise_base.h
	cp ./noise_priv_diamond_square.h $(INSTALL_ROOT)include/noise_priv_diamond_square.h
	cp ./noise_priv_evolution.h $(INSTALL_ROOT)include/noise_priv_evolution.h
	cp ./noise_priv_midpoint_displacement.h $(INSTALL_ROOT)include/noise_priv_midpoint_displacement.h
	cp $(BUILDPATH)$(LIBNAME) $(INSTALL_ROOT)lib/$(LIBNAME)
