all: teststub

teststub: teststub.c libcounter.a
	gcc -o teststub teststub.c libcounter.a

libcounter.a: counter.o
	ar r libcounter.a counter.o

counter.o: counter.c counter.h
	gcc -c counter.c

clean:
	rm *.o *.a teststub