DEPS=main.c

all: $(DEPS)
	cc $(DEPS) -o main.a -lcurl ../cJSON/cJSON.o

run:main.a
	./main.a qwerty_16 left 

clean:
	rm -f main.a
	rm -f *.a