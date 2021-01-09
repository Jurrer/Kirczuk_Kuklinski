DEPS=iCzolg.o ../cJSON/cJSON.o

iCzolg: $(DEPS)
	cc $^ -o $@ --pedantic -Wall

%.o:%.c
	cc -c $^ -o $@

run:iCzolg
	./iCzolg ../cJSON/cJSON.o

clean:
	rm -f iCzolg
	rm -f *.o