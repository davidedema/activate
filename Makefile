CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = activate-cli

SRC = src/main.c src/dir_list.c src/scan.c src/activate.c src/io.c
OBJ = $(SRC:.c=.o)

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

WRAPPER = scripts/activate

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	mkdir -p $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/activate-cli
	install -m 755 $(WRAPPER) $(DESTDIR)$(BINDIR)/activate

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/activate-cli
	rm -f $(DESTDIR)$(BINDIR)/activate

.PHONY: clean install uninstall

clean:
	rm -f $(OBJ) $(TARGET)