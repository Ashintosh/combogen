#include "segment.h"
#include "generate.h"
#include "permute.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER_CAP 1024

/* Parse command-line arguments and detect if -a flag is set */
static int parse_arguments(int argc, char **argv, int *all_permutations, int *first_arg)
{
    *all_permutations = 0;
    *first_arg = 1;

    if (argc > 1 && strcmp(argv[1], "-a") == 0) {
        *all_permutations = 1;
        *first_arg = 2;
        if (argc < 3) {
            fprintf(stderr, "usage: %s [-a] [segments...]\n", argv[0]);
            return 0;
        }
    } else if (argc < 2) {
        fprintf(stderr, "usage: %s [-a] [segments...]\n", argv[0]);
        return 0;
    }

    return 1;
}

/* Parse segment arguments into an array of Segment structs */
static Segment *parse_segments(int argc, char **argv, int first_arg, size_t *seg_count)
{
    *seg_count = argc - first_arg;
    Segment *segs = malloc(*seg_count * sizeof(*segs));
    if (!segs) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < *seg_count; ++i) {
        segs[i] = parse_segment(argv[first_arg + i]);
    }

    return segs;
}

/* Clean up allocated segments and buffer */
static void cleanup(Segment *segs, size_t seg_count, char *buffer)
{
    free(buffer);
    for (size_t i = 0; i < seg_count; ++i)
        free_segment(&segs[i]);
    free(segs);
}

int main(int argc, char **argv)
{
    int all_permutations;
    int first_arg;

    if (!parse_arguments(argc, argv, &all_permutations, &first_arg))
        return 1;

    size_t seg_count;
    Segment *segs = parse_segments(argc, argv, first_arg, &seg_count);

    size_t buf_cap = INITIAL_BUFFER_CAP;
    char *buffer = malloc(buf_cap);
    if (!buffer) {
        perror("malloc");
        cleanup(segs, seg_count, NULL);
        exit(EXIT_FAILURE);
    }

    if (!all_permutations) {
        generate(segs, seg_count, 0, buffer, 0, buf_cap);
    } else {
        permute_segments(segs, 0, seg_count - 1, buffer, buf_cap);
    }

    cleanup(segs, seg_count, buffer);

    return 0;
}
