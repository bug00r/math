.PHONY: clean vec mat utils statistics algorithm

all: vec mat utils statistics algorithm

vec:
	$(MAKE) -C vec

mat:
	$(MAKE) -C mat

utils:
	$(MAKE) -C utils

statistics:
	$(MAKE) -C statistics

algorithm:
	$(MAKE) -C algorithm


clean:
	$(MAKE) -C vec clean
	$(MAKE) -C mat clean
	$(MAKE) -C utils clean
	$(MAKE) -C statistics clean
	$(MAKE) -C algorithm clean
	
