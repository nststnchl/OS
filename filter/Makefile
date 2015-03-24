all: filter

filter: filter.o ../lib/libhelpers.so
	gcc -o $@ -L../lib -lhelpers $< ../lib/libhelpers.so
	rm -f filter.o

../lib/libhelpers.so:
	$(MAKE) -C ../lib

filter.o:
	gcc -o $@ -c -Wall -I../lib filter.c

clean:
	rm -f filter filter.o
	$(MAKE) -C ../lib clean
