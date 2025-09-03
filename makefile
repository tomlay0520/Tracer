CC = gcc
CFLAGS = -Wall -Wextra -g -finstrument-functions -rdynamic
LDFLAGS = -ldl

TARGET = simple
SRCS = simple.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET) > trace

.PHONY: all clean run