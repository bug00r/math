include ../../../_make_/make_config
#CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -O1 $(debug)
#-ggdb
#-pg for profiling 

SRC=geometry.c

LIBNAME=libgeometry.a
OBJS=geometry.o

INCLUDEDIR=-I./../../../collections/dl_list -I./../../../math/vec -I./../../../math/utils -I.
INCLUDEDIR_DBG=-I./../../../debug/

TESTSRC=test_geometry.c
TESTBIN=test_geometry.exe
TESTLIB= -lgeometry -ldl_list -lutilsmath -lvec 
TESTLIBDIR=-L$(BUILDDIR) \
			-L./../../../collections/dl_list/$(BUILDDIR) \
			-L./../../../math/utils/$(BUILDDIR) \
			-L./../../../math/mat/$(BUILDDIR) \
			-L./../../../math/vec/$(BUILDDIR)

all: createdir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN)

$(BUILDPATH)$(LIBNAME): $(BUILDPATH)$(OBJS)
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(OBJS)

$(BUILDPATH)$(OBJS):
	$(CC) $(CFLAGS) -c $(SRC) -o $(BUILDPATH)$(OBJS) $(INCLUDEDIR) $(debug)
	
$(BUILDPATH)$(TESTBIN):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(INCLUDEDIR_DBG) $(INCLUDEDIR) $(TESTLIBDIR) $(TESTLIB) $(debug)
	
.PHONY: createdir clean test

createdir:
	mkdir -p $(BUILDDIR)

test:
	./$(BUILDPATH)$(TESTBIN)

clean:
	-rm -dr $(BUILDROOT)
	