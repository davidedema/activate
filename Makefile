CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = test_list

SRC = src/main.c src/dir_list.c
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)