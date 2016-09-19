
CC = g++
CFLAGS = -std=c++11 -stdlib=libc++

all: main.cpp
	$(CC) $(CFLAGS) -o pixel-sprite-generator *.cpp

default: all
