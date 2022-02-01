.PHONY: clean install test

all:
	$(MAKE) -C noise
	$(MAKE) -C fractals
	$(MAKE) -C geometry

clean:
	$(MAKE) -C noise clean
	$(MAKE) -C fractals clean
	$(MAKE) -C geometry clean

install:
	$(MAKE) -C noise install
	$(MAKE) -C fractals install
	$(MAKE) -C geometry install

test:
	$(MAKE) -C noise test
	$(MAKE) -C fractals test
	$(MAKE) -C geometry test
	
