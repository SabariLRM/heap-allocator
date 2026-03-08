# Custom Heap Allocator

A custom heap allocator written in C.  
It provides basic heap initialization, allocation, and deallocation functionality without using `malloc`.

---

## Usage

Include the allocator header in your program:

```c
#include "my_alloc.h"
```

Compile with:

```bash
gcc yourfile.c my_alloc.c -o run
```

Or using the provided Makefile:

```bash
make yourfile.c
```

If your program uses `argc` and `argv`, arguments can be passed as:

```bash
make yourfile.c 5 6
```

---

## API

### `heap_init(N)`
Initializes the heap with size **N bytes**.  
This function **must be called before any other allocator function**.

### `alloc(N)`
Allocates a memory chunk of size **N bytes**.  
The returned memory is **aligned to 32 bytes**.

### `freec(p)`
Frees the previously allocated chunk pointed to by `p` with no fragmentation problem.

### `freeh()`
Releases the entire heap allocated by `heap_init()`.

---

## Memory Alignment

- Heap is **page aligned (4096 bytes)**.
- Allocated chunks are **aligned to 32 bytes**.
- The **minimum chunk size is 32 bytes which is aligned automatically, meaning alloc(3) gives a chunk of size 32**.

---

## Notes

- `heap_init()` must be called before using other functions.
- `freeh()` should be called when the heap is no longer needed.
- The allocator manages its own heap and **does not rely on `malloc`**.

---

## Example

Run the provided test file:

```bash
make test.c 5
```

(You can replace `5` with any integer argument.)
