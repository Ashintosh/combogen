#include "permute.h"
#include "generate.h"

/* Swap two segments in place */
static void swap_segments(Segment *a, Segment *b)
{
    Segment tmp = *a;
    *a = *b;
    *b = tmp;
}

/* 
 * Recursively generates all permutations of segments.
 * Calls generate() on each permutation.
 */
void permute_segments(Segment *segs, size_t start, size_t end, char *buffer, size_t buf_cap)
{
    if (start == end) {
        generate(segs, end + 1, 0, buffer, 0, buf_cap);
        return;
    }

    for (size_t i = start; i <= end; ++i) {
        swap_segments(&segs[start], &segs[i]);
        permute_segments(segs, start + 1, end, buffer, buf_cap);
        swap_segments(&segs[start], &segs[i]); // backtrack
    }
}
