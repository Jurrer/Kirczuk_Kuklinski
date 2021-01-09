DEPS=iCzolg.o ../cJSON/cJSON.o

iCzolg: $(DEPS)
	cc $^ -o $@ --pedantic -Wall

%.o:%.c
	cc -c $^ -o $@

run:iCzolg
	./iCzolg

clean:
	rm -f iCzolg
	rm -f *.o