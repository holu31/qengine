CC = clang
CFLAGS = -g -Wall -Wextra -std=c99 -O0 -Iinclude/
LDLIBS = -lGL -lX11
TARGET = game

SRC = src/main.c src/mesh.c src/gl/glx_win.c src/gl/gl_init.c 
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
