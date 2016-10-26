TARGET      = rico
LIBS        = -lncursesw
CC          = gcc
CFLAGS      = -g1 -Wall
SRCDIR      = src
OBJDIR      = build
SRC         = $(wildcard $(SRCDIR)/*.c)
OBJ         = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

.PHONY: default all clean

default: $(TARGET)
all: default

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIBS)

clean:
	rm -fr $(OBJDIR)
	rm -f $(TARGET)
