#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Represents a numeric segment specification.
 */
typedef struct {
    int zero_padded;  /**< 1 = zero-padded (%d), 0 = plain (%i) */
    size_t digits;    /**< Number of digits for the segment */
} NumberSpec;

/**
 * @brief Formats a number according to a NumberSpec.
 * 
 * Allocates a new string containing the formatted number. Caller must free().
 * 
 * @param ns Pointer to NumberSpec defining padding and digits.
 * @param value The number to format.
 * @return A newly allocated string containing the formatted number.
 */
static inline char *format_number(NumberSpec *ns, size_t value)
{
    // Determine required length of format string: "%0<digits>d" or "%zu"
    size_t fmt_len = 3 + snprintf(NULL, 0, "%zu", ns->digits);
    char *fmt = malloc(fmt_len + 1);
    if (!fmt) { 
        perror("malloc"); 
        exit(EXIT_FAILURE); 
    }

    if (ns->zero_padded) {
        snprintf(fmt, fmt_len + 1, "%%0%zud", ns->digits);
    } else {
        strcpy(fmt, "%zu");
    }

    // Allocate string to hold the number
    size_t num_len = ns->digits + 2; // digits + null + safety margin
    char *numbuf = malloc(num_len);
    if (!numbuf) { 
        perror("malloc"); 
        free(fmt);
        exit(EXIT_FAILURE); 
    }

    snprintf(numbuf, num_len, fmt, value);
    free(fmt);

    return numbuf;
}