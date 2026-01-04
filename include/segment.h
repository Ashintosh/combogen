#pragma once

#include "wordlist.h"
#include "number.h"
#include <stddef.h>

/**
 * @brief Type of segment, either a list of words or a numeric segment.
 */
typedef enum {
    SEG_WORDS,  /**< Segment contains words from a wordlist */
    SEG_NUMBER  /**< Segment represents a number (%d or %i) */
} SegmentType;

/**
 * @brief Represents a single segment in the generator.
 */
typedef struct {
    SegmentType type; /**< SEG_WORDS or SEG_NUMBER */
    void *data;       /**< Pointer to the segment data (WordList* or NumberSpec*) */
} Segment;

/**
 * @brief Parse a command-line argument into a segment.
 * 
 * @param arg The argument to parse (file name or number token).
 * @return A Segment respresenting either a word list or number.
 */
Segment parse_segment(const char *arg);

/**
 * @brief Frees the memory used by a segment.
 * 
 * @param seg The segment to free.
 */
void free_segment(Segment *seg);
