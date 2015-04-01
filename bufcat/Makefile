all: bufcat

bufcat: bufcat.o ../lib/libhelpers.so
	gcc -o $@ -L../lib $< ../lib/libhelpers.so -lhelpers ../lib/libbufio.so -lbufio
	rm -f bufcat.o

../lib/libhelpers.so:
	$(MAKE) -C ../lib

bufcat.o:
	gcc -o $@ -c -Wall -I../lib bufcat.c

clean:
	rm -f bufcat bufcat.o bufcat2.c
	$(MAKE) -C ../lib clean
