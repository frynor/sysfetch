CC = gcc
CFLAGS = -Wall -Wextra
TARGET = systemfetch
SRCDIR = src

$(TARGET) : $(SRCDIR)/main.c $(SRCDIR)/clarg.c 
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCDIR)/main.c $(SRCDIR)/clarg.c 

install:
	install -m 755 $(TARGET) /usr/local/bin/$(TARGET)

uninstall:
	rm -f /usr/local/bin$(TARGET)

clean:
	rm -f $(TARGET)
