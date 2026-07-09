CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = test_scan

SRC = src/main.c src/dir_list.c src/scan.c src/activate.c src/io.c
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)