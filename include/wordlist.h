#pragma once

#include <stddef.h>

/**
 * @brief Represents a list of words loaded from a file.
 */
typedef struct {
    char **words;  /**< Array of words */
    size_t count;  /**< Number of words in the array */
} WordList;

/**
 * @brief Loads words from a file (one word per line) into a WordList.
 * 
 * @param filename Path to the text file containing words.
 * @return WordList containing all words from the file.
 */
WordList load_words(const char *filename);

/**
 * @brief Frees memory allocated for a WordList.
 * 
 * @param list Pointer to the WordList to free.
 */
void free_words(WordList *list);
