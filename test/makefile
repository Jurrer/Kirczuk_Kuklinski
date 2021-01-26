DEPS=mapa_t.o
#drugi plik makefile powstał dla tego, że wywoływanie programów testowych z podfolderu 'testy' powodowało segmentation fault
#było to prawdopodobnie przez problem z wskazaniem pliku cJSON.o

all:complex_test

%.o:%.c
	cc -c $^ -o $@

kompiluj: $(DEPS)
	cc mapa_t.o -o mapa_t.a ../../cJSON/cJSON.o

complex_test:kompiluj
	./mapa_t.a explore
	./mapa_t.a left

clean:
	rm -f *.a
	rm -f *.o

memtest:kompiluj
	valgrind ./mapa_t.a explore
	
