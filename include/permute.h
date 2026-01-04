#pragma once
#include "segment.h"

/**
 * @brief Recursively generates all permutations of the given segments.
 * 
 * This function swaps segments recursively to generate all possible
 * orderings and passes each ordering to the generator function
 * that builds the final strings in the provided buffer.
 * 
 * @param segs Array of Segment structures to permute.
 * @param start Index of the segment to start permuting from (usually 0).
 * @param end Index of the last segment in the array (usually seg_count - 1).
 * @param buffer Pointer to the buffer used for concatenating segment strings.
 * @param buf_cap Total allocated size of the buffer.
 */
void permute_segments(Segment *segs, size_t start, size_t end, char *buffer, size_t buf_cap);
