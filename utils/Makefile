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

SRC=utils_math.c

LIBNAME=libutilsmath.a
OBJS=utils_math.o

INCLUDEDIR?=-I/c/dev/include
LIB?=-L/c/dev/lib$(BIT_SUFFIX)

TESTSRC=test_utils_math.c
TESTBIN=test_utils_math.exe
TESTLIB= -lutilsmath -lmat -lvec  
TESTLIBDIR=-L$(BUILDDIR) $(LIB)

all: createdir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN)

$(BUILDPATH)$(LIBNAME): $(BUILDPATH)$(OBJS)
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(OBJS)

$(BUILDPATH)$(OBJS): utils_math.h
	$(CC) $(CFLAGS) -c $(SRC) -o $(BUILDPATH)$(OBJS) $(INCLUDEDIR) 
	
$(BUILDPATH)$(TESTBIN):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(INCLUDEDIR) $(TESTLIBDIR) $(TESTLIB) $(debug)

.PHONY: clean createdir test

test:
	./$(BUILDPATH)$(TESTBIN)

createdir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)

install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib$(BIT_SUFFIX)
	cp ./utils_math.h $(INSTALL_ROOT)include/utils_math.h
	cp $(BUILDPATH)$(LIBNAME) $(INSTALL_ROOT)lib$(BIT_SUFFIX)/$(LIBNAME)
