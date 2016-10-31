TARGET      = rico
LIBS        = -lncursesw
CC          = gcc
CFLAGS      = -g1 -Wall
SRCDIR      = src
BINDIR      = bin
OBJDIR      = build
SRC         = $(wildcard $(SRCDIR)/*.c)
OBJ         = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

.PHONY: default all clean install uninstall

default: $(TARGET)
all: default

$(BINDIR):
	@mkdir -p $@

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

$(TARGET): $(OBJ) | $(BINDIR)
	$(CC) -pthread -o $(BINDIR)/$(TARGET) $(OBJ) $(LIBS)

clean:
	rm -fr $(BINDIR)
	rm -fr $(OBJDIR)
	rm -f $(TARGET)

install:
	install -m 755 $(BINDIR)/$(TARGET) /usr/local/bin/$(TARGET)

uninstall:
	rm -f /usr/local/bin/$(TARGET)

