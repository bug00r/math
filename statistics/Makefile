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
NAME=statistics

LIBNAME=lib$(NAME).a
LIB=$(BUILDPATH)$(LIBNAME)
OBJS=$(BUILDPATH)$(NAME).o $(BUILDPATH)average.o

INCLUDE?=-I. -I/c/dev/include
INCLUDEDIR=$(INCLUDE) 

LIBSDIR?=-L/c/dev/lib$(BIT_SUFFIX)

TESTBIN=$(BUILDPATH)test_$(NAME).exe
TESTLIB= -l$(NAME) -lutilsmath -lmat -lvec
TESTLIBDIR=-L$(BUILDDIR) $(LIBSDIR)

all: mkbuilddir $(LIB) $(TESTBIN)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJS): $(NAME).h average.h
	$(CC) $(CFLAGS) -c $(@F:.o=.c) -o $@ $(INCLUDEDIR) $(debug)
	
$(TESTBIN): $(LIB)
	$(CC) $(CFLAGS) $(@F:.exe=.c) -o $@ $(INCLUDEDIR) $(TESTLIBDIR) $(TESTLIB) $(debug)
	
.PHONY: clean mkbuilddir test

test:
	./$(TESTBIN)

mkbuilddir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)

install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib$(BIT_SUFFIX)
	cp ./$(NAME).h $(INSTALL_ROOT)include$(PATHSEP)$(NAME).h
	cp ./average.h $(INSTALL_ROOT)include$(PATHSEP)average.h
	cp $(LIB) $(INSTALL_ROOT)lib$(BIT_SUFFIX)$(PATHSEP)$(LIBNAME)