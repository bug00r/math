include ../../../make_config
#CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -O1 $(debug)
#-ggdb
#-pg for profiling 

SRC=fractals.c

LIBNAME=libfractals.a
OBJS=fractals.o

INCLUDEDIR=-I./../../../collections/array/ -I./../../../math/vec -I./../../../math/mat -I./../../../math/utils -I.

TESTSRC=test_fractals.c
TESTBIN=test_fractals.exe
TESTLIB= -lfractals -larray -lutilsmath -lmat -lvec 
TESTLIBDIR=-L$(BUILDDIR) \
			-L./../../../collections/array/$(BUILDDIR) \
			-L./../../../math/utils/$(BUILDDIR) \
			-L./../../../math/mat/$(BUILDDIR) \
			-L./../../../math/vec/$(BUILDDIR)

all: createdir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN) test

$(BUILDPATH)$(LIBNAME): $(BUILDPATH)$(OBJS)
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(OBJS)

$(BUILDPATH)$(OBJS): fractals.h
	$(CC) $(CFLAGS) -c $(SRC) -o $(BUILDPATH)$(OBJS) $(INCLUDEDIR) 
	
$(BUILDPATH)$(TESTBIN):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(INCLUDEDIR) $(TESTLIBDIR) $(TESTLIB)
	
.PHONY: createdir clean test

createdir:
	mkdir -p $(BUILDDIR)

test:
	./$(BUILDPATH)$(TESTBIN)

clean:
	-rm -dr $(BUILDROOT)
	