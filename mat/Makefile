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
SRC=mat.c

LIBNAME=libmat.a
OBJS=mat.o

TESTSRC=test_mat.c
TESTBIN=test_mat.exe
TESTLIB=-lmat
TESTLIBDIR=-L$(BUILDDIR)

all: createdir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN) test

$(BUILDPATH)$(LIBNAME): $(BUILDPATH)$(OBJS)
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(OBJS)

$(BUILDPATH)$(OBJS): mat.h
	$(CC) $(CFLAGS) -c $(SRC) -o $(BUILDPATH)$(OBJS)

$(BUILDPATH)$(TESTBIN): 
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(TESTLIBDIR) $(TESTLIB) 
	
.PHONY: clean test createdir

createdir:
	mkdir -p $(BUILDDIR)
test:
	./$(BUILDPATH)$(TESTBIN)
	
clean:
	-rm -dr $(BUILDROOT)

install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib
	cp ./mat.h $(INSTALL_ROOT)include/mat.h
	cp ./mat2.h $(INSTALL_ROOT)include/mat2.h
	cp ./mat3.h $(INSTALL_ROOT)include/mat3.h
	cp ./mat4.h $(INSTALL_ROOT)include/mat4.h
	cp ./mat_config.h $(INSTALL_ROOT)include/mat_config.h
	cp $(BUILDPATH)$(LIBNAME) $(INSTALL_ROOT)lib/$(LIBNAME)
