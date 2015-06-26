# Makefile
# Copyright 2015-06 dsa_final15

CC=g++
CFLAGS=-std=c++11 -O2 -Wall
TAR_MD5=md5.cpp
OBJ_MD5=md5.o
TAR_SHA=sha256.cpp
OBJ_SHA=sha256.o

all: $(OBJ_MD5) $(OBJ_SHA)

$(OBJ_MD5): $(TAR_MD5)
	$(CC) $(CFLAGS) -c $(TAR_MD5)

$(OBJ_SHA): $(TAR_SHA)
	$(CC) $(CFLAGS) -c $(TAR_SHA)

clean:
	rm -rf md5.o sha256.o

