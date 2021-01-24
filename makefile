DEPS=main.o main_auto.o komunikacja.o funkcje.o

all:kompiluj

%.o:%.c
	cc -c $^ -o $@

kompiluj: $(DEPS)
	cc main_auto.o komunikacja.o funkcje.o -o main_auto.a -lcurl ../cJSON/cJSON.o

komp: $(DEPS)
	cc main.o komunikacja.o funkcje.o -o main.a -lcurl ../cJSON/cJSON.o

lewo:komp
	./main.a qwerty_16 left 

prawo:komp
	./main.a qwerty_16 right

explore:komp
	./main.a qwerty_18 explore

info:komp
	./main.a qwerty_16 info

move:main_auto.a
	./main_auto.a qwerty_16 move  	

duzo:main.a
	./main.a qwerty_16 left right move explore move right left info move 

clean:
	rm -f *.a
	rm -f *.o

<<<<<<< HEAD
auto:kompiluj
	valgrind ./main_auto.a qwerty_18
=======
auto:main_auto.a
	./main_auto.a qwerty_18
>>>>>>> 4de20695f4bef836fbd71fa62fbcc32cc024f41d
