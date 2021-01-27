DEPS=json_test.o szukanie_obwiedni_t.o szukanie_granicy_t.o request_t.o ../komunikacja.o ../funkcje.o ../automat.o
#drugi plik makefile powstał dla tego, że wywoływanie programów testowych z podfolderu 'testy' powodowało segmentation fault
#było to prawdopodobnie przez problem z wskazaniem pliku cJSON.o

all:complex_test

%.o:%.c
	cc -c $^ -o $@

kompiluj: $(DEPS)
	cc json_test.o -o json_test.a ../../cJSON/cJSON.o
	cc szukanie_obwiedni_t.o ../komunikacja.o ../funkcje.o ../automat.o -o szukanie_obwiedni_t.a -lcurl ../../cJSON/cJSON.o
	cc szukanie_granicy_t.o ../komunikacja.o ../funkcje.o ../automat.o -o szukanie_granicy_t.a -lcurl ../../cJSON/cJSON.o
	cc request_t.o ../komunikacja.o -o request_t.a -lcurl 

szukanie_obwiedni:kompiluj
	./szukanie_obwiedni_t.a qwerty_18

szukanie_granicy:kompiluj
	./szukanie_granicy_t.a qwerty_18

complex_test:kompiluj
	./request_t.a qwerty_10 left right
	./json_test.a left explore

clean:
	rm -f *.a
	rm -f *.o
	rm -f ../*.a
	rm -f ../*.o

memtest:kompiluj
	valgrind ./request_t.a left right
	valgrind ./json_test.a left explore

