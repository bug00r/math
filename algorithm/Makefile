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

MATH_ALGO_PROJ_ROOT:=$(shell pwd)
MATH_ALGO_PROJ_BUILD:=$(MATH_ALGO_PROJ_ROOT)$(PATHSEP)$(BUILDPATH)

MATH_ALGO_MODULES:=noise fractals geometry compression crypt

all: $(patsubst %, build_%, $(MATH_ALGO_MODULES)) 

build_noise:
	$(MAKE) -C noise
	$(MAKE) -C noise install PREFIX=$(MATH_ALGO_PROJ_BUILD)

build_fractals:
	$(MAKE) -C fractals CFLAGS="$(CFLAGS) -I$(MATH_ALGO_PROJ_BUILD)include"
	$(MAKE) -C fractals install PREFIX=$(MATH_ALGO_PROJ_BUILD)

build_geometry:
	$(MAKE) -C geometry CFLAGS="$(CFLAGS) -I$(MATH_ALGO_PROJ_BUILD)include"
	$(MAKE) -C geometry install PREFIX=$(MATH_ALGO_PROJ_BUILD)

build_compression:
	$(MAKE) -C compression CFLAGS="$(CFLAGS) -I$(MATH_ALGO_PROJ_BUILD)include"
	$(MAKE) -C compression install PREFIX=$(MATH_ALGO_PROJ_BUILD)

build_crypt:
	$(MAKE) -C crypt CFLAGS="$(CFLAGS) -I$(MATH_ALGO_PROJ_BUILD)include"
	$(MAKE) -C crypt install PREFIX=$(MATH_ALGO_PROJ_BUILD)

.PHONY: clean createdir	test

test: createdir
	$(MAKE) -C noise test CFLAGS="$(CFLAGS) -I$(MATH_ALGO_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(MATH_ALGO_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"
	$(MAKE) -C fractals test CFLAGS="$(CFLAGS) -I$(MATH_ALGO_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(MATH_ALGO_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"
	$(MAKE) -C geometry test CFLAGS="$(CFLAGS) -I$(MATH_ALGO_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(MATH_ALGO_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"
	$(MAKE) -C compression test CFLAGS="$(CFLAGS) -I$(MATH_ALGO_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(MATH_ALGO_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"
	$(MAKE) -C crypt test CFLAGS="$(CFLAGS) -I$(MATH_ALGO_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(MATH_ALGO_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"
createdir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)
	$(MAKE) -C noise clean
	$(MAKE) -C fractals clean
	$(MAKE) -C geometry clean
	$(MAKE) -C compression clean
	$(MAKE) -C crypt clean

install:
	$(info install at: $(INSTALL_ROOT))
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib$(BIT_SUFFIX)
	-cp -f $(BUILDPATH)include/*.h $(INSTALL_ROOT)include
	-cp -f $(BUILDPATH)lib$(BIT_SUFFIX)/*.a $(INSTALL_ROOT)lib$(BIT_SUFFIX)
