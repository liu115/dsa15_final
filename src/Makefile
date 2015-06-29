# Makefile
# Copyright 2015-06 dsa_final15

CC=g++
CFLAGS=-std=c++11 -O2 -Wall

TAR_ACCOUNT=account/account.cpp
OBJ_ACCOUNT=account.o

TAR_MD5=account/encoder/md5.cpp
OBJ_MD5=md5.o

TAR_SHA=account/encoder/sha256.cpp
OBJ_SHA=sha256.o

TAR_HASH=account/MurmurHash3.cpp
OBJ_HASH=MurmurHash3.o

TAR_BANK_UMAP=bank_unordered_map.cpp
OBJ_BANK_UMAP=bank_unordered_map.o

TAR_BANK1=main.cpp

all: $(OBJ_MD5) $(OBJ_SHA) $(OBJ_ACCOUNT) $(OBJ_BANK_UMAP)

$(OBJ_MD5): $(TAR_MD5)
	$(CC) $(CFLAGS) -c $(TAR_MD5)

$(OBJ_SHA): $(TAR_SHA)
	$(CC) $(CFLAGS) -c $(TAR_SHA)

$(OBJ_ACCOUNT): $(TAR_ACCOUNT)
	$(CC) $(CFLAGS) -c $(TAR_ACCOUNT)

$(OBJ_BANK_UMAP): $(TAR_BANK_UMAP)
	$(CC) $(CFLAGS) -c $(TAR_BANK_UMAP)

bank1: $(TAR_BANK1)
	$(CC) $(CFLAGS) -DBANK_UM $(OBJ_BANK_UMAP) $(OBJ_ACCOUNT) $(OBJ_MD5) $(OBJ_SHA) $(TAR_BANK1) -o bank_um.out

clean:
	rm -rf account.o md5.o sha256.o bank_unordered_map.o bank_um.out
