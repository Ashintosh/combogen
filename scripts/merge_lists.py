#!/usr/bin/env python3

import argparse
from pathlib import Path


def merge_wordlists(file1: Path, file2: Path, output: Path) -> None:
    words = set()

    for path in (file1, file2):
        with path.open("r", encoding="utf-8") as f:
            for line in f:
                word = line.strip()
                if word:
                    words.add(word)

    with output.open("w", encoding="utf-8") as out:
        for word in sorted(words):
            out.write(word + "\n")


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Merge two wordlist files into a single deduplicated list."
    )
    parser.add_argument("file1", type=Path, help="First input wordlist")
    parser.add_argument("file2", type=Path, help="Second input wordlist")
    parser.add_argument(
        "-o", "--output",
        type=Path,
        required=True,
        help="Output file path"
    )

    args = parser.parse_args()

    merge_wordlists(args.file1, args.file2, args.output)


if __name__ == "__main__":
    main()
