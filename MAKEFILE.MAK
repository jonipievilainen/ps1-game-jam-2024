all:
	ccpsx -O3 -Xo$80010000 main.c -omain.cpe,main.sym,mem.map
	ccpsx -O3 -Xo$80010000 main.c \psx\lib\none2.obj -omain.cpe

	cpe2x /ce main.cpe