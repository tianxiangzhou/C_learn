CC=cc
CFLAGS=
LDFLAGS=-lm
TARGET=test
SRC=test.c
OBJ=$(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
