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

TAR_BANK_RBT=bank_rb_tree.cpp
OBJ_BANK_RBT=bank_rb_tree.o

TAR_BANK_TRIE=bank_trie.cpp
OBJ_BANK_TRIE=bank_trie.o

MAIN=main.cpp

RESULT=final_project

all: $(OBJ_MD5) $(OBJ_SHA) $(OBJ_ACCOUNT) $(OBJ_BANK_UMAP) $(RESULT)

$(OBJ_MD5): $(TAR_MD5)
	$(CC) $(CFLAGS) -c $(TAR_MD5)

$(OBJ_SHA): $(TAR_SHA)
	$(CC) $(CFLAGS) -c $(TAR_SHA)

$(OBJ_ACCOUNT): $(TAR_ACCOUNT)
	$(CC) $(CFLAGS) -c $(TAR_ACCOUNT)

$(OBJ_BANK_UMAP): $(TAR_BANK_UMAP)
	$(CC) $(CFLAGS) -c $(TAR_BANK_UMAP)

$(OBJ_BANK_RBT): $(TAR_BANK_RBT)
	$(CC) $(CFLAGS) -c $(TAR_BANK_RBT)

$(OBJ_BANK_TRIE): $(TAR_BANK_TRIE)
	$(CC) $(CFLAGS) -c $(TAR_BANK_TRIE)

bank1: $(MAIN)
	$(CC) $(CFLAGS) -DBANK_UM $(OBJ_BANK_UMAP) $(OBJ_ACCOUNT) $(OBJ_MD5) $(OBJ_SHA) $(MAIN) -o final_project

bank2: $(MAIN)
	$(CC) $(CFLAGS) -DBANK_RB $(OBJ_BANK_RBT) $(OBJ_ACCOUNT) $(OBJ_MD5) $(OBJ_SHA) $(MAIN) -o final_project

bank3: $(MAIN)
	$(CC) $(CFLAGS) -DBANK_TR $(OBJ_BANK_TRIE) $(OBJ_ACCOUNT) $(OBJ_MD5) $(OBJ_SHA) $(MAIN) -o final_project

$(RESULT): $(MAIN)
	$(CC) $(CFLAGS) -DBANK_UM $(OBJ_BANK_UMAP) $(OBJ_ACCOUNT) $(OBJ_MD5) $(OBJ_SHA) $(MAIN) -o final_project

run1:
	./final_project

clean:
	rm -rf account.o md5.o sha256.o bank_unordered_map.o bank_rb_tree.o bank_trie.o final_project
