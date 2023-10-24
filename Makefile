CC = gcc
CFLAGS = -Wall -std=c99
LIBS = -lncurses

TARGET = life
SRC = life.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
	rm *~
