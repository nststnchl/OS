all: libhelpers.so

libhelpers.so: helpers.o
	gcc -o $@ -shared $<
	rm -f helpers.o

helpers.o:
	gcc -o $@ -c -Wall -fPIC helpers.c

clean:
	rm -f helpers.o libhelpers.so
