all: cat

cat: cat.o libhelpers
	gcc -o $@ -L../lib -lhelpers $<

libhelpers:
	$(MAKE) -C ../lib

cat.o:
	gcc -o $@ -c -Wall -I../lib $<

clean:
	rm -f cat cat.o
	$(MAKE) -C ../lib clean
