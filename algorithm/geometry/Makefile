
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

CFLAGS+=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra
#-ggdb
#-pg for profiling 

NAME=geometry

LIBNAME=lib$(NAME).a
LIB=$(BUILDPATH)$(LIBNAME)
OBJS=$(BUILDPATH)$(NAME).o

CFLAGS+=-I/c/dev/include
LIBSDIR?=-L/c/dev/lib$(BIT_SUFFIX)

CFLAGS+=-I.

TESTBIN=$(BUILDPATH)test_$(NAME).exe
TESTLIB= -l$(NAME) -lutilsmath -lmat -lvec -ldl_list
TESTLIBDIR=-L$(BUILDDIR) $(LIBSDIR)

LDFLAGS+=$(TESTLIBDIR) $(TESTLIB)

all: createdir $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJS): $(NAME).h
	$(CC) $(CFLAGS) -c $(@F:.o=.c) -o $@
	
$(TESTBIN): $(LIB)
	$(CC) $(CFLAGS) $(@F:.exe=.c) -o $@ $(LDFLAGS)
	
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
	cp $(LIB) $(INSTALL_ROOT)lib$(BIT_SUFFIX)$(PATHSEP)$(LIBNAME)
