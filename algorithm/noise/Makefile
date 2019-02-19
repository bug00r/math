include ../../../make_config
#CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -O1 $(debug)
#-ggdb
#-pg for profiling 

SRC=noise.c

LIBNAME=libnoise.a
OBJS=noise.o

INCLUDEDIR=-I./../../../collections/array/ -I./../../statistics/ -I./../../vec/ -I./../../mat/ -I./../../utils/ -I. 

TESTSRC=test_noise.c
TESTBIN=test_noise.exe
TESTLIB= -lnoise -lfarray -larray -lstatistics -lutilsmath -lmat -lvec
TESTLIBDIR=-L$(BUILDDIR) \
		   -L./../../../collections/array/$(BUILDDIR) \
		   -L./../../statistics/$(BUILDDIR) \
		   -L./../../utils/$(BUILDDIR) \
		   -L./../../mat/$(BUILDDIR) \
		   -L./../../vec/$(BUILDDIR)

all: createdir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN) test

$(BUILDPATH)$(LIBNAME): $(BUILDPATH)$(OBJS) 
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(OBJS)

$(BUILDPATH)$(OBJS): noise.h
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
	