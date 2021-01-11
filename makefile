DEPS=main.o komunikacja.o funkcje.o

all: $(DEPS)
	cc $(DEPS) -o main.a -lcurl ../cJSON/cJSON.o

%.o:%.c
	cc -c $^ -o $@

lewo:main.a
	./main.a qwerty_16 left 

prawo:main.a
	./main.a qwerty_16 right

explore:main.a
	./main.a qwerty_16 explore

info:main.a
	./main.a qwerty_16 info

move:main.a
	./main.a qwerty_16 move  	

duzo:main.a
	./main.a qwerty_16 left right move explore move right left info move 

clean:
	rm -f main.a
	rm -f *.a
