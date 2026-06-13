CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -O0 -Iinclude/
LDLIBS = -lGL -lX11
TARGET = game

SRC = src/main.c src/glxwin.c src/gl/gl_main.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
