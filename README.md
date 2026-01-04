# combogen

`combogen` is a command-line tool for generating combinatorial wordlists from multiple word sources and numeric patterns.

It is written in C for performance and designed to efficiently generate combinatorial wordlists for testing, automation, fuzzing, and security tasks.

---

## Features

- Combine multiple wordlists into generated output
- Support numeric segments with configurable digit length
- Optional zero-padded numbers
- Generate combinations in fixed order or all permutations
- Stream output to stdout (easy piping to files or other tools)

---

## Building

Requires a C compiler (GCC or Clang).

```sh
make
```

The resulting binary will be located at:

```
build/combogen
```

---

## Usage

```sh
combogen [-a] [segments...]
```

### Segments

Each segment may be one of the following:

- A **wordlist file** (one word per line)
- A **numeric token**:
  - `%dN` → zero-padded number with `N` digits
  - `%iN` → non-zero-padded number with up to `N` digits

### Options

| Option | Description |
|--------|-------------|
| `-a` | Generate all permutations of the provided segments |

---

## Examples

### Basic wordlist combination

```sh
combogen adjectives.txt nouns.txt
```

If:

```
adjectives.txt:
fast
slow

nouns.txt:
car
train
```

Output:

```
fastcar
fasttrain
slowcar
slowtrain
```

---

### Adding a numeric segment

```sh
combogen adjectives.txt nouns.txt %d2
```

Output:

```
fastcar00
fastcar01
...
slowtrain99
```

---

### Non-zero-padded numbers

```sh
combogen adjectives.txt %i2
```

Output:

```
fast0
fast1
...
fast99
```

---

### Generate all permutations

```sh
combogen -a adjectives.txt nouns.txt
```

This generates all combinations for each ordering of the segments.

---

### Save output to a file

```sh
combogen adjectives.txt nouns.txt %d2 > output.txt
```

---

### Custom Segment Order & Repeating Wordlists

You can change the order of the segments to control how the output is generated.  
You can also repeat the same wordlist multiple times if desired.

#### Example 1 — Numeric segment first

```sh
combogen nouns.txt %d2 adjectives.txt
```

If:

```
nouns.txt:
car
train

adjectives.txt:
fast
slow
```

Output:

```
car00fast
car00slow
car01fast
car01slow
train00fast
train00slow
train01fast
train01slow
...
```

#### Example 2 — Repeating the same wordlist

```sh
combogen adjectives.txt adjectives.txt
```

If:

```
adjectives.txt:
fast
slow
```

Output:

```
fastfast
fastslow
slowfast
slowslow
```

> `combogen` respects the segment order and allows repeated segments, giving you full control over the combinatorial output.

## Wordlist Format

Wordlists are plain text files:

- One word per line
- Empty lines are ignored
- No normalization is applied

Example:

```
admin
guest
test
```

---

## Helper Scripts

### Merge wordlists (Python)

Located in `scripts/merge_lists.py`.

```sh
python3 scripts/merge_lists.py list1.txt list2.txt output.txt
```

This merges two wordlists into one, removing duplicates and sorting the result.

---

## Notes

- Output is streamed to stdout — large wordlists can grow very quickly
- Output size grows exponentially with the number of segments
- Memory usage is bounded by the longest generated string, not total output size

---

## To Do

- Add support for Windows OS
- Better error handling

