all: lenwords

lenwords: lenwords.o ../lib/libhelpers.so
	gcc -o $@ -L../lib $< ../lib/libhelpers.so -lhelpers
	rm -f lenwords.o

../lib/libhelpers.so:
	$(MAKE) -C ../lib

lenwords.o:
	gcc -o $@ -c -Wall -I../lib lenwords.c

clean:
	rm -f lenwords lenwords.o
	$(MAKE) -C ../lib clean
