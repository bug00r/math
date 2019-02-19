include ../../make_config
#CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -O1 $(debug)
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
	