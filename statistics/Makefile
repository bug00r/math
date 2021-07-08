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
#CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -O1 
#-ggdb
#-pg for profiling 

SRC=statistics.c average.c

LIBNAME=libstatistics.a
OBJS=$(BUILDPATH)statistics.o $(BUILDPATH)average.o

INCLUDE?=-I/c/dev/include
INCLUDEDIR=$(INCLUDE) -I. 

LIB?=-L/c/dev/lib$(BIT_SUFFIX)

TESTSRC=test_statistics.c
TESTBIN=test_statistics.exe
TESTLIB= -lstatistics -lutilsmath -lmat -lvec
TESTLIBDIR=-L$(BUILDDIR) $(LIB)

all: mkbuilddir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN)

$(BUILDPATH)$(LIBNAME):  $(BUILDPATH)statistics.o $(BUILDPATH)average.o
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(OBJS)

$(BUILDPATH)statistics.o: statistics.c statistics.h
	$(CC) $(CFLAGS) -c statistics.c -o $(BUILDPATH)statistics.o  $(INCLUDEDIR) $(debug)
	
$(BUILDPATH)average.o: average.c average.h
	$(CC) $(CFLAGS) -c average.c -o $(BUILDPATH)average.o  $(INCLUDEDIR) $(debug)
	
$(BUILDPATH)$(TESTBIN):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(INCLUDEDIR) $(TESTLIBDIR) $(TESTLIB) $(debug)
	
.PHONY: clean mkbuilddir test

test:
	./$(BUILDPATH)$(TESTBIN)

mkbuilddir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)

install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib$(BIT_SUFFIX)
	cp ./statistics.h $(INSTALL_ROOT)include/statistics.h
	cp ./average.h $(INSTALL_ROOT)include/average.h
	cp $(BUILDPATH)$(LIBNAME) $(INSTALL_ROOT)lib$(BIT_SUFFIX)/$(LIBNAME)