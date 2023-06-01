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

MATH_PROJ_ROOT:=$(shell pwd)
MATH_PROJ_BUILD:=$(MATH_PROJ_ROOT)$(PATHSEP)$(BUILDPATH)

MATH_MODULES:=vec mat utils statistics algorithm

all: $(patsubst %, build_%, $(MATH_MODULES)) 

build_vec:
	$(MAKE) -C vec
	$(MAKE) -C vec install PREFIX=$(MATH_PROJ_BUILD)

build_mat:
	$(MAKE) -C mat CFLAGS="$(CFLAGS) -I$(MATH_PROJ_BUILD)include"
	$(MAKE) -C mat install PREFIX=$(MATH_PROJ_BUILD)

build_utils:
	$(MAKE) -C utils CFLAGS="$(CFLAGS) -I$(MATH_PROJ_BUILD)include"
	$(MAKE) -C utils install PREFIX=$(MATH_PROJ_BUILD)

build_statistics:
	$(MAKE) -C statistics CFLAGS="$(CFLAGS) -I$(MATH_PROJ_BUILD)include"
	$(MAKE) -C statistics install PREFIX=$(MATH_PROJ_BUILD)

build_algorithm:
	$(MAKE) -C algorithm CFLAGS="$(CFLAGS) -I$(MATH_PROJ_BUILD)include"
	$(MAKE) -C algorithm install PREFIX=$(MATH_PROJ_BUILD)

.PHONY: clean createdir	test

test: createdir
	$(MAKE) -C vec test CFLAGS="$(CFLAGS) -I$(MATH_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(MATH_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"
	$(MAKE) -C mat test CFLAGS="$(CFLAGS) -I$(MATH_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(MATH_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"
	$(MAKE) -C utils test CFLAGS="$(CFLAGS) -I$(MATH_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(MATH_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"
	$(MAKE) -C statistics test CFLAGS="$(CFLAGS) -I$(MATH_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(MATH_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"
	$(MAKE) -C algorithm test CFLAGS="$(CFLAGS) -I$(MATH_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(MATH_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"

createdir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)
	$(MAKE) -C vec clean
	$(MAKE) -C mat clean
	$(MAKE) -C utils clean
	$(MAKE) -C statistics clean
	$(MAKE) -C algorithm clean

install:
	$(info install at: $(INSTALL_ROOT))
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib$(BIT_SUFFIX)
	cp $(BUILDPATH)include/*.h $(INSTALL_ROOT)include
	cp $(BUILDPATH)lib$(BIT_SUFFIX)/*.a $(INSTALL_ROOT)lib$(BIT_SUFFIX)
