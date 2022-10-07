C=gcc
CFLAGS=-W -Wall -std=c99
LDFLAGS=
EXEC=app
SRC= TD-STUDENT-OOP/UserInterfaceLayer/cbApp.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

app: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -ITD-STUDENT-OOP/DomainLayer -ITD-STUDENT-OOP/ApplicationLayer/CircularBuffer

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)