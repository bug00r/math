.PHONY: clean vec mat utils statistics algorithm

all: 
	$(MAKE) -C vec
	$(MAKE) -C mat
	$(MAKE) -C utils
	$(MAKE) -C statistics
	$(MAKE) -C algorithm

clean:
	$(MAKE) -C vec clean
	$(MAKE) -C mat clean
	$(MAKE) -C utils clean
	$(MAKE) -C statistics clean
	$(MAKE) -C algorithm clean
	
install:
	$(MAKE) -C vec install
	$(MAKE) -C mat install
	$(MAKE) -C utils install
	$(MAKE) -C statistics install
	$(MAKE) -C algorithm install