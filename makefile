DEPS=jaja_2.c

iCzolg: $(DEPS)
	cc $(DEPS) -o jaja_2.a -lcurl -Wall --pedantic ../cJSON/cJSON.o

run:jaja_2.a
	./jaja_2.a left 

clean:
	rm -f jaja_2.a
	rm -f *.o
	rm -f *.a