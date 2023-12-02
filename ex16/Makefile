SOURCES=ex16.c hangman.c rps.c movement.c
OBJECTS=$(SOURCES:.c=.o)

program: $(OBJECTS)
	gcc $^ -o $@

%.o: %.c
	gcc $^ -c -o $@

clean:
	rm -fr *.o program