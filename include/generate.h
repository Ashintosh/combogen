#pragma once

#include "segment.h"

/**
 * @brief Recursively generates all combinations of segments into the buffer.
 * 
 * @param segments Array of segments (words or number tokens).
 * @param seg_count Number of segments.
 * @param idx Current index in recursion (start with 0).
 * @param buffer Output buffer.
 * @param len Current length used in buffer (start with 0).
 * @param buf_cap Total allocated capacity of buffer.
 */
void generate(
    Segment *segments,
    size_t seg_count,
    size_t idx,
    char *buffer,
    size_t len,
    size_t buf_cap
);
