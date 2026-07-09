CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = activate

SRC = src/main.c src/dir_list.c src/scan.c src/activate.c src/io.c
OBJ = $(SRC:.c=.o)

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)

.PHONY: clean install uninstall
clean:
	rm -f $(OBJ) $(TARGET)