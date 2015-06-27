# Makefile
# Copyright 2015-06 dsa_final15

CC=g++
CFLAGS=-std=c++11 -O2 -Wall

TAR_ACCOUNT=account.cpp
OBJ_ACCOUNT=account.o

TAR_MD5=md5.cpp
OBJ_MD5=md5.o

TAR_SHA=sha256.cpp
OBJ_SHA=sha256.o

TAR_HASH=MurmurHash3.cpp
OBJ_HASH=MurmurHash3.o

all: $(OBJ_ACCOUNT) $(OBJ_MD5) $(OBJ_SHA) $(OBJ_HASH)

$(OBJ_ACCOUNT): $(TAR_ACCOUNT)
	$(CC) $(CFLAGS) -c $(TAR_ACCOUNT)

$(OBJ_MD5): $(TAR_MD5)
	$(CC) $(CFLAGS) -c $(TAR_MD5)

$(OBJ_SHA): $(TAR_SHA)
	$(CC) $(CFLAGS) -c $(TAR_SHA)

$(OBJ_HASH): $(TAR_HASH)
	$(CC) $(CFLAGS) -c $(TAR_HASH)

clean:
	rm -rf account.o md5.o sha256.o MurmurHash3.o
