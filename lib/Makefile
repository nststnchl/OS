all: libhelpers.so libbufio.so

libhelpers.so: helpers.o
	gcc -o $@ -shared $<
	rm -f helpers.o

helpers.o:
	gcc -o $@ -c -Wall -fPIC helpers.c

libbufio.so: bufio.o
	gcc -o $@ -shared $<
	rm -f bufio.o

bufio.o:
	gcc -o $@ -c -Wall -fPIC bufio.c

clean:
	rm -f helpers.o libhelpers.so bufio.o libbufio.so
