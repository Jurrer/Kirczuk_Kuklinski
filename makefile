DEPS=jaja.c

all: $(DEPS)
	cc $(DEPS) -o jaja.a -lcurl -Wall --pedantic ../cJSON/cJSON.o

run:jaja.a
	./jaja.a left 

clean:
	rm -f jaja.a
	rm -f *.a
