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
#CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -O1 $(debug)
#-ggdb
#-pg for profiling 

SRC=vec.c

LIBNAME=libvec.a
OBJS=vec.o

TESTSRC=test_vec.c
TESTBIN=test_vec.exe
TESTLIB=-lvec
TESTLIBDIR=-L$(BUILDDIR)

all: createdir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN)

$(BUILDPATH)$(LIBNAME):$(BUILDPATH)$(OBJS)
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(OBJS)
	
$(BUILDPATH)$(OBJS): vec.h
	$(CC) $(CFLAGS) -c $(SRC) -o $(BUILDPATH)$(OBJS)
	
$(BUILDPATH)$(TESTBIN):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(TESTLIBDIR) $(TESTLIB)
	
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
	cp ./vec.h $(INSTALL_ROOT)include/vec.h
	cp ./vec2.h $(INSTALL_ROOT)include/vec2.h
	cp ./vec3.h $(INSTALL_ROOT)include/vec3.h
	cp ./vec_config.h $(INSTALL_ROOT)include/vec_config.h
	cp $(BUILDPATH)$(LIBNAME) $(INSTALL_ROOT)lib$(BIT_SUFFIX)/$(LIBNAME)
