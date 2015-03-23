all: revwords

revwords: revwords.o ../lib/libhelpers.so
	gcc -o $@ -L../lib $< ../lib/libhelpers.so -lhelpers
	rm -f revwords.o

../lib/libhelpers.so:
	$(MAKE) -C ../lib

revwords.o:
	gcc -o $@ -c -Wall -I../lib revwords.c

clean:
	rm -f revwords revwords.o revwords2.c
	$(MAKE) -C ../lib clean
