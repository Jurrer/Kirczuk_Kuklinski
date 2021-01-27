DEPS= main_auto.o komunikacja.o funkcje.o automat.o main.o

#komenda 'make memtest1' i 'make memtest2' przetestuje wycieki pamieci naszych programów

all:kompiluj auto

%.o:%.c
	cc -c $^ -o $@

kompiluj: $(DEPS)
	cc main_auto.o komunikacja.o funkcje.o automat.o -o main_auto.a -lcurl ../cJSON/cJSON.o

komp: $(DEPS)
	cc main.o komunikacja.o funkcje.o automat.o -o main.a -lcurl ../cJSON/cJSON.o

auto:
	./main_auto.a

main:duzo

memtest1:kompiluj
	valgrind ./main_auto.a

memtest2:komp
	valgrind ./main.a qwerty_16 info

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
	rm -f test/*.a
	rm -f test/*.o
	
