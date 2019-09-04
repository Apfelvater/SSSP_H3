// You can use these includes and defines as a hint what functions you might want to use ;)
#define _GNU_SOURCE
#include "md5.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// ART (Adaptive Radix Tree) by ARMON https://github.com/armon/libart
#include "./armon/libart/src/art.h"

#define HASH_LENGTH 16

/*  Self defined trivial list. Bad performance, ofc.
typedef struct words {
    char* word;
    struct words* next;
} words;

words* init_words() {
    words* new_words = malloc(sizeof(words));
    return new_words;
}

void add_word(words* first, char* word) {
    char* w = malloc(strlen(word));
    strcpy(w, word);
    if (! first->word) {
        first->word = w;
        return;
    }
    words* n = first;
    while(n->next) {
        n = n->next;
    }
    n->next = malloc(sizeof(words));
    *(n->next) = (words) {w, 0};
}
//  Prints all words in a wordlist
void print_words(words* list) {
    words* wi = list;
    while(wi) {
        if (wi->word) printf("%s ", (wi->word));
        wi = wi->next;
    }
}
*/

int main (){
	// unsigned char target[HASH_LENGTH] = {0xe6, 0x54, 0x93, 0xcc, 0xde, 0xe9, 0xc4, 0x51, 0x4f, 0xe2, 0x0e, 0x04, 0x04, 0xf3, 0xbc, 0xb8}; "???" - to be used for les_miserables.txt
	unsigned char target[HASH_LENGTH] = {0x1c, 0x01, 0x43, 0xc6, 0xac, 0x75, 0x05, 0xc8, 0x86, 0x6d, 0x10, 0x27, 0x0a, 0x48, 0x0d, 0xec}; // "Les Miserables" - to be used for les_miserables_preface.txt
	time_t start = time(NULL);
	FILE* f;

	f = fopen("les_miserables.txt", "r");
	if(f == NULL){
		return 1;
	}
	const char* delim = " .,;-:0123456789?!\"*+()|&[]#$/%%'";
    
    //MINE::
    
    
    FILE* fp;
    fp = fopen("les_miserables_preface.txt", "r");
    if(fp == NULL) {
        return 1;
    }

    char* match;
    unsigned char hash[HASH_LENGTH] = {0};
	char buffer[1024];
    char* token;
    char* tokenB;
    art_tree words;
    MD5_CTX md5_ctx;
    int wcount = 0;
    
    int init_code = art_tree_init(&words);
    if (init_code) {
        printf("Error: %i\n", init_code);
        exit(1);
    }
    printf("Size: %lu\n", art_size(&words));
    
    while (fgets(buffer, 1024, fp)) {
        //printf("Buffer: %s\n", buffer);
        buffer[strlen(buffer)-1] = '\000';
        token = strtok(buffer, delim);
        while(token) {
            if(art_insert(&words, token, strlen(token), 1)) {
                continue;
            } else {
                //MD5_Init(&md5_ctx);
                //MD5_Update(&md5_ctx, buffer, strlen(buffer));
                //MD5_Final(hash, &md5_ctx);
                
                while (!art_iter(&words, 0, tokenB)) {
                    
                }
                
                wcount++;
            }
            token = strtok(0, delim);
        }
    }
    printf("Size= %lu\n", art_size(&words));
    
    fclose(fp);
    fclose(f);
    
    //::MINE
    
	/*
	 * - find all unique words from the book
	 * - create the hashes of all two-string combinations
	 * - try to speed it up
	 * Usage example (not complete!):
	 *
	 * unsigned char hash[HASH_LENGTH] = {0};
	 * char buffer[1024];
	 * // put something into buffer to hash it
	 * MD5_CTX md5_ctx;
	 * MD5_Init(&md5_ctx);
	 * MD5_Update(&md5_ctx, buffer, strlen(buffer));
	 * MD5_Final(hash, &md5_ctx);
	 */

	time_t end = time(NULL);
	printf("Execution took ~%fs\n", difftime(end, start));
	return 0;
}
