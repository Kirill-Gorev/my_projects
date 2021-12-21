# Makefile for project
TARGET=P03.c
CC=gcc
CFLAGS=-O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -std=gnu11 -lm
OBJECTS=a.o 

all:$(TARGET)

clean:
	rm -f *.o $(TARGET) core
	
$(TARGET): $(OBJECTS)
	$(CC) $(TARGET) -o $(CFLAGS) $(OBJECTS)
a.o:
	$(CC) $(TARGET) -c $(CFLAGS) $<
