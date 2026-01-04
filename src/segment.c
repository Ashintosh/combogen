#include "segment.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h> // for perror

// Check if a string represents a number token, e.g. "%d2"
static int is_number_token(const char *s)
{
    return s[0] == '%' && (s[1] == 'd' || s[1] == 'i') && isdigit((unsigned char)s[2]);
}

// Parse a command-line segment argument into a Segment struct
Segment parse_segment(const char *arg)
{
    Segment seg = {0};

    if (is_number_token(arg)) {
        // Allocate NumberSpec
        NumberSpec *ns = malloc(sizeof(*ns));
        if (!ns) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        ns->zero_padded = (arg[1] == 'd');
        ns->digits = atoi(arg + 2);

        seg.type = SEG_NUMBER;
        seg.data = ns;

        return seg;
    }

    // Otherwise treat as a word list
    WordList *wl = malloc(sizeof(*wl));
    if (!wl) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    *wl = load_words(arg);

    seg.type = SEG_WORDS;
    seg.data = wl;

    return seg;
}

// Free memory associated with a Segment
void free_segment(Segment *seg)
{
    if (seg->type == SEG_WORDS) {
        free_words((WordList *)seg->data);
        free(seg->data);
    } else if (seg->type == SEG_NUMBER) {
        free(seg->data);
    }
}
