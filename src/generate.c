#include "generate.h"
#include "number.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Ensures the buffer has enough capacity for `required_len` characters.
 * If not, reallocates to double the needed size.
 */
static char *ensure_buffer(char *buffer, size_t *cap, size_t required_len)
{
    if (required_len >= *cap) {
        *cap = required_len * 2; // Grow buffer to reduce future reallocs
        char *tmp = realloc(buffer, *cap);
        if (!tmp) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        buffer = tmp;
    }
    return buffer;
}

/**
 * Generate all combinations for a word segment by iterating through the word list.
 * Recursively calls `generate` for the next segment.
 */
static void generate_word_segment(Segment *segments, size_t seg_count, size_t idx,
                                  char *buffer, size_t len, size_t *buf_cap)
{
    WordList *wl = segments[idx].data;

    for (size_t i = 0; i < wl->count; ++i) {
        size_t l = strlen(wl->words[i]);
        buffer = ensure_buffer(buffer, buf_cap, len + l);

        memcpy(buffer + len, wl->words[i], l);

        generate(segments, seg_count, idx + 1, buffer, len + l, *buf_cap);
    }
}

/**
 * Generate all combinations for a numeric segment based on its NumberSpec.
 * Computes the maximum value based on the number of digits and zero-padding.
 */
static void generate_number_segment(Segment *segments, size_t seg_count, size_t idx,
                                    char *buffer, size_t len, size_t *buf_cap)
{
    NumberSpec *ns = segments[idx].data;

    // Maximum value this segment can represent (10^digits)
    size_t max = 1;
    for (size_t d = 0; d < ns->digits; ++d)
        max *= 10;

    for (size_t i = 0; i < max; ++i) {
        char *numbuf = format_number(ns, i);
        size_t n = strlen(numbuf);

        buffer = ensure_buffer(buffer, buf_cap, len + n);
        memcpy(buffer + len, numbuf, n);
        free(numbuf);

        generate(segments, seg_count, idx + 1, buffer, len + n, *buf_cap);
    }
}

/* Generates all combinations for a list of segments recursively */
void generate(Segment *segments, size_t seg_count, size_t idx,
              char *buffer, size_t len, size_t buf_cap)
{
    if (idx == seg_count) {
        buffer[len] = '\0'; // Null-terminate and output the completed string
        puts(buffer);
        return;
    }

    Segment *s = &segments[idx];

    if (s->type == SEG_WORDS)
        generate_word_segment(segments, seg_count, idx, buffer, len, &buf_cap);
    else
        generate_number_segment(segments, seg_count, idx, buffer, len, &buf_cap);
}
