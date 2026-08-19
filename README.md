# URL Shortener

Small C++17 URL shortener core built around a custom AVL tree.

The project maintains two indexes:
- short code -> original URL
- original URL -> short code

This allows lookup, reverse lookup and deletion in O(log n).

## Features

- URL shortening
- reverse lookup
- duplicate prevention
- deletion and URL updates
- access counters
- most frequently used URL
- substring search with KMP

## Implementation

The main data structure is a generic AVL tree implemented from scratch.
Two AVL trees are used to keep both lookup directions efficient.

Short codes are generated from [a-zA-Z0-9].

## Build

cmake -S . -B build
cmake --build build
./build/url_shortener