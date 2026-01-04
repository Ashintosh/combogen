#include "wordlist.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_BUF_SIZE 256

// Read a single line from a file, dynamically allocated
static char *read_line(FILE *fp) {
    if (!fp) return NULL;

    size_t cap = INITIAL_BUF_SIZE;
    size_t len = 0;

    char *buf = malloc(cap);
    if (!buf) { perror("malloc"); exit(EXIT_FAILURE); }

    int c;
    while ((c = fgetc(fp)) != EOF && c != '\n') {
        if (len + 1 >= cap) {
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) { perror("realloc"); exit(EXIT_FAILURE); }
            buf = tmp;
        }
        buf[len++] = c;
    }

    if (c == EOF && len == 0) {
        free(buf);
        return NULL;
    }

    buf[len] = '\0';
    return buf;
}

// Load words from a file into a dynamically allocated WordList
WordList load_words(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    WordList list = {0};
    size_t cap = 16;

    list.words = malloc(cap * sizeof(char *));
    if (!list.words) { perror("malloc"); exit(EXIT_FAILURE); }

    char *line;
    while ((line = read_line(fp))) {
        if (list.count == cap) {
            cap *= 2;
            char **tmp = realloc(list.words, cap * sizeof(char *));
            if (!tmp) { perror("realloc"); exit(EXIT_FAILURE); }
            list.words = tmp;
        }

        list.words[list.count++] = line;
    }

    fclose(fp);
    return list;
}

// Free all memory allocated for a WordList
void free_words(WordList *list) {
    for (size_t i = 0; i < list->count; ++i)
        free(list->words[i]);

    free(list->words);
}
