all: cat

cat: cat.o ../lib/libhelpers.so
	gcc -o $@ -L../lib $< ../lib/libhelpers.so -lhelpers
	rm -f cat.o

../lib/libhelpers.so:
	$(MAKE) -C ../lib

cat.o:
	gcc -o $@ -c -Wall -I../lib cat.c

clean:
	rm -f cat cat.o cat2.c
	$(MAKE) -C ../lib clean
