# Makefile
# Copyright 2015-06 dsa_final15

CC=g++
CFLAGS=-std=c++11 -O2 -Wall

TAR_ACCOUNT=src/account/account.cpp
OBJ_ACCOUNT=account.o

TAR_MD5=src/account/encoder/md5.cpp
OBJ_MD5=md5.o

TAR_SHA=src/account/encoder/sha256.cpp
OBJ_SHA=sha256.o

TAR_HASH=src/account/MurmurHash3.cpp
OBJ_HASH=MurmurHash3.o

TAR_RB=src/rb.c
OBJ_RB=rb.o

TAR_MURMUR=src/account/encoder/murmurhash.c
OBJ_MURMUR=murmurhash.o

TAR_BANK_UMAP=src/bank_unordered_map.cpp
OBJ_BANK_UMAP=bank_unordered_map.o

TAR_BANK_RBT=src/bank_rb_tree.cpp
OBJ_BANK_RBT=bank_rb_tree.o

TAR_BANK_TRIE=src/bank_trie.cpp
OBJ_BANK_TRIE=bank_trie.o

TAR_BANK_MUR=src/bank_unordered_map_murmur.cpp
OBJ_BANK_MUR=bank_unordered_map_murmur.o

MAIN=src/main.cpp

RESULT=bin/final_project

all: bank1

obj: $(OBJ_MD5) $(OBJ_SHA) $(OBJ_ACCOUNT)

$(OBJ_MD5): $(TAR_MD5)
	$(CC) $(CFLAGS) -c $(TAR_MD5)

$(OBJ_SHA): $(TAR_SHA)
	$(CC) $(CFLAGS) -c $(TAR_SHA)

$(OBJ_ACCOUNT): $(TAR_ACCOUNT)
	$(CC) $(CFLAGS) -c $(TAR_ACCOUNT)

$(OBJ_MURMUR): $(TAR_MURMUR)
	g++ -O2 -Wall $(TAR_MURMUR) -c

$(OBJ_BANK_UMAP): $(TAR_BANK_UMAP)
	$(CC) $(CFLAGS) -c $(TAR_BANK_UMAP)

$(OBJ_RB): $(TAR_RB)
	gcc -std=c99 -O2 -Wall $(TAR_RB) -c

$(OBJ_BANK_RBT): $(TAR_BANK_RBT)
	$(CC) $(CFLAGS) -c $(TAR_BANK_RBT)

$(OBJ_BANK_TRIE): $(TAR_BANK_TRIE)
	$(CC) $(CFLAGS) -c $(TAR_BANK_TRIE)

$(OBJ_BANK_MUR): $(TAR_BANK_MUR)
	$(CC) $(CFLAGS) -c $(TAR_BANK_MUR)

bank1: $(MAIN) $(OBJ_BANK_UMAP) obj
	$(CC) $(CFLAGS) -DBANK_UM $(OBJ_BANK_UMAP) $(OBJ_ACCOUNT) $(OBJ_MD5) $(OBJ_SHA) $(MAIN) -o $(RESULT)

bank2: $(MAIN) $(OBJ_BANK_RBT) obj $(OBJ_RB)
	$(CC) $(CFLAGS) -DBANK_RB $(OBJ_BANK_RBT) $(OBJ_ACCOUNT) $(OBJ_MD5) $(OBJ_SHA) $(OBJ_RB) $(MAIN) -o $(RESULT)

bank3: $(MAIN) $(OBJ_BANK_TRIE) obj
	$(CC) $(CFLAGS) -DBANK_TR $(OBJ_BANK_TRIE) $(OBJ_ACCOUNT) $(OBJ_MD5) $(OBJ_SHA) $(MAIN) -o $(RESULT)

bank4: $(MAIN) $(OBJ_BANK_MUR) $(OBJ_MURMUR) obj
	$(CC) $(CFLAGS) -DBANK_UM $(OBJ_BANK_MUR) $(OBJ_MURMUR) $(OBJ_ACCOUNT) $(OBJ_MD5) $(OBJ_SHA) $(MAIN) -o $(RESULT)

run:
	./$(RESULT)

clean:
	rm -rf *.o $(RESULT)
