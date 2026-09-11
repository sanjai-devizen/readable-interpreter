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
	echo "Run with 'ri'."

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: ri
ri: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	del /q *.o *.exe 2>nul || rm -f *.o *.exe
	echo "Clean complete."

