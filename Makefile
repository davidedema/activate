CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = activate-cli

SRC = src/main.c src/dir_list.c src/scan.c src/activate.c src/io.c
OBJ = $(SRC:.c=.o)

# Installation paths
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
DATADIR = $(PREFIX)/share
COMPDIR = $(DATADIR)/bash-completion/completions

# Staging directory (used by packages)
DESTDIR ?=

WRAPPER = scripts/activate
COMPLETION = scripts/completion


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


install: $(TARGET)
	@echo "Installing to $(DESTDIR)$(PREFIX)"

	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/activate-cli

	install -m 755 $(WRAPPER) $(DESTDIR)$(BINDIR)/activate

	install -d $(DESTDIR)$(COMPDIR)
	install -m 644 $(COMPLETION) $(DESTDIR)$(COMPDIR)/activate


uninstall:
	rm -f $(DESTDIR)$(BINDIR)/activate-cli
	rm -f $(DESTDIR)$(BINDIR)/activate
	rm -f $(DESTDIR)$(COMPDIR)/activate


clean:
	rm -f $(OBJ) $(TARGET)


.PHONY: clean install uninstall