# Binary Search (`bsearch`) Implementation

My C implementation of the standard-library-like `bsearch` function, with support for primitive and user-defined types - accompanied by Google Test environment.

## Key Components

* **`bsearch`**\*\* Function\*\* (`src/bsearch.c`)

  * Signature:

    ```c
    void *bsearch(const void *key,
                  const void *base,
                  size_t num,
                  size_t size,
                  int (*compar)(const void *, const void *));
    ```

  * Performs binary search on an array of `num` elements of `size` bytes, located at `base`.

  * Handles empty arrays (`num == 0`) and avoids index underflow when `mid == 0`.

* **Comparator Functions** (`include/search.h`, `src/bsearch.c`)

  * `int compare_int(const void *a, const void *b)`
  * `int compare_float(const void *a, const void *b)`
  * `int compare_string(const void *a, const void *b)`
  * `int compare_struct_item_by_id(const void *a, const void *b)`
  * Each returns `<0`, `0`, or `>0` according to standard contract.

* **Data Types** (`include/search.h`)

  ```c
  typedef struct {
      int         id;
      const char *name;
  } Item;
  ```

* **Test Suite** (`tests/test_bsearch.cpp`)

  * Google Test cases covering:

    * Exact match, no-match, empty array
    * Single-element arrays
    * Repeated elements
    * Min/max integer values, negative and mixed-sign
    * Floating-point comparisons with `EXPECT_FLOAT_EQ`
    * Case-sensitive string search
    * Struct key lookup by `id`

## Directory Layout

```plaintext
Bsearch/
├── include/
│   └── search.h         # Function declarations & type definitions
├── src/
│   └── bsearch.c        # Implementation of binary search & comparators
├── tests/
│   └── test_bsearch.cpp # Google Test suite
├── makefile             # Build and test automation
└── README.md            # Project description
```

## Build & Test

This project uses Google Test included as a third‑party submodule under `third_party/googletest`.

**Prerequisites:**

* GCC (C11) and G++ for compiling tests
* GNU Make

```bash
# Build the project and tests
git clone https://github.com/Nubet/Bsearch.git
cd Bsearch
git clone https://github.com/google/googletest.git third_party/googletest
make            # compiles bsearch.o and test_bsearch executable

# Run the test suite
./test_bsearch  # executes Google Test cases

# Clean build artifacts
make clean      # removes object files and test binary
```

* **Targets:**

  * `all` (default): builds `bsearch.o` and `test_bsearch` executable.
  * `clean`: deletes `*.o` and `test_bsearch`.
