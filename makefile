all:
	cc iCzolg.c -lcurl --pedantic -Wall

run:a.out
	./a.out

clean:
	rm -f a.out