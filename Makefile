TARGET = readable-interpreter.exe

CC = gcc
CFLAGS = -w -g

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

.SILENT:

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	echo "$(TARGET) built."
	echo "Run with 'make ri'."

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: ri
ri: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm -f *.o *.exe
	echo "Clean complete."

