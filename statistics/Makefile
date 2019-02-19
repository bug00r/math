include ../../make_config
#CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -O1 
#-ggdb
#-pg for profiling 

SRC=statistics.c average.c

LIBNAME=libstatistics.a
OBJS=$(BUILDPATH)statistics.o $(BUILDPATH)average.o

INCLUDEDIR= -I./../vec -I./../mat -I./../utils -I. 

TESTSRC=test_statistics.c
TESTBIN=test_statistics.exe
TESTLIB= -lstatistics -lutilsmath -lmat -lvec
TESTLIBDIR=-L$(BUILDDIR) \
		   -L./../vec/$(BUILDDIR) \
		   -L./../mat/$(BUILDDIR) \
		   -L./../utils/$(BUILDDIR) \

all: mkbuilddir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN) test

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
	