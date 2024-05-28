_CFLAGS:=$(CFLAGS)
CFLAGS:=$(_CFLAGS)
_LDFLAGS:=$(LDFLAGS)
LDFLAGS:=$(_LDFLAGS)

ARFLAGS?=rcs
PATHSEP?=/
BUILDROOT?=build

BUILDDIR?=$(BUILDROOT)$(PATHSEP)$(CC)
BUILDPATH?=$(BUILDDIR)$(PATHSEP)

ifndef PREFIX
	INSTALL_ROOT=$(BUILDPATH)
else
	INSTALL_ROOT=$(PREFIX)$(PATHSEP)
	ifeq ($(INSTALL_ROOT),/)
	INSTALL_ROOT=$(BUILDPATH)
	endif
endif

ifdef DEBUG
	CFLAGS+=-ggdb
	ifeq ($(DEBUG),)
	CFLAGS+=-Ddebug=1
	else 
	CFLAGS+=-Ddebug=$(DEBUG)
	endif
endif

ifeq ($(M32),1)
	CFLAGS+=-m32
	BIT_SUFFIX+=32
endif

override CFLAGS+=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra
#-ggdb
#-pg for profiling 

NAME=compression

LIBNAME=lib$(NAME).a
LIB=$(BUILDPATH)$(LIBNAME)

COMPRESSION_MODULES=deflate checksum lz77
OBJS=$(patsubst %, $(BUILDPATH)%.o, $(COMPRESSION_MODULES))
#OBJS=$(BUILDPATH)$(NAME).o

override CFLAGS+=-I. -I/c/dev/include
LIBSDIR?=-L/c/dev/lib$(BIT_SUFFIX)

TESTBIN=$(BUILDPATH)test_$(NAME).exe
TESTLIB= -l$(NAME)
TESTLIBDIR=-L$(BUILDDIR) $(LIBSDIR)

override LDFLAGS+=$(TESTLIBDIR) $(TESTLIB)

all: createdir $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJS): $(NAME).h
	$(CC) $(CFLAGS) -c $(@F:.o=.c) -o $@
	
$(TESTBIN): $(LIB)
	$(CC) $(CFLAGS) -Wno-overlength-strings $(@F:.exe=.c) -o $@ $(LDFLAGS)
	
.PHONY: createdir clean test install

createdir:
	mkdir -p $(BUILDDIR)

test: createdir $(TESTBIN)
	./$(TESTBIN)

clean:
	-rm -dr $(BUILDROOT)
	
install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib$(BIT_SUFFIX)
	cp ./$(NAME).h $(INSTALL_ROOT)include$(PATHSEP)$(NAME).h
	cp ./deflate.h $(INSTALL_ROOT)include$(PATHSEP)deflate.h
	cp ./lz77.h $(INSTALL_ROOT)include$(PATHSEP)lz77.h
	cp $(LIB) $(INSTALL_ROOT)lib$(BIT_SUFFIX)$(PATHSEP)$(LIBNAME)
