# URL Shortener (C++)

A high-performance, console-based URL Shortener written in C++. This application utilizes optimized memory mapping and standard encoding techniques to generate compact, unique short codes and retrieve original URLs instantly.

---

## Features

- **Base62 Short Codes**: Converts auto-incrementing ID sequences into highly compact Base62 alphanumeric codes (characters `0-9`, `a-z`, `A-Z`).
- **Bi-directional Memory Mapping**: Caches both short-to-long and long-to-short URL mappings to prevent duplicate entries and optimize lookups.
- **Input Validation**: Ensures only valid URLs containing structure (e.g. domain endings) and no spaces are shortened.
- **Interactive CLI Menu**: Enables continuous shortening and retrieval operations within a single application runtime.
- **Optimized STL Lookups**: Passes parameter arguments by constant references (`const std::string&`) to prevent copy overhead, and uses cached iterators to avoid double-lookup penalties in `std::unordered_map`.

---

## How It Works Under the Hood

1. **URL Validation**: Before processing, the application inspects the structure of the long URL.
2. **Lookup Checks**: It checks the reverse lookup map (`longToShort`) to see if the URL has already been shortened. If so, it returns the existing code immediately.
3. **Base62 Generation**: If it is a new URL, the system increments the internal counter and converts the value to a Base62 string representation.
4. **Storage**: It registers both mapping paths (`short -> long` and `long -> short`) in `std::unordered_map` instances.
5. **Retrieval**: Uses `unordered_map::find` once, caching the iterator to verify existence and return the target value in $O(1)$ average time without searching twice.

---

## Getting Started

### Prerequisites

You will need a C++ compiler supporting C++11 or higher (e.g. `g++`, `clang++`, or MSVC `cl`).

### Compilation

Compile the C++ source code using your terminal:

```bash
# Using g++ (GCC)
g++ -std=c++17 url_shortener.cpp -o url_shortener.exe

# Using clang++
clang++ -std=c++17 url_shortener.cpp -o url_shortener.exe
```

### Execution

Run the compiled executable:

```bash
./url_shortener.exe
```

---

## CLI Usage Example

```text
=== URL Shortener Menu ===
1. Shorten URL
2. Retrieve Original URL
3. Exit
Enter your choice (1-3): 1
Enter long URL: google.com
Shortened URL: short.ly/1

=== URL Shortener Menu ===
1. Shorten URL
2. Retrieve Original URL
3. Exit
Enter your choice (1-3): 2
Enter short code (or full shortened URL): short.ly/1
Original URL: google.com
```

---

## Complexity Analysis

| Operation | Time Complexity (Average) | Space Complexity (Worst) |
| :--- | :--- | :--- |
| **Shorten URL (New)** | $O(1)$ | $O(N)$ where $N$ is total shortened URLs |
| **Shorten URL (Duplicate)** | $O(1)$ | $O(1)$ |
| **Retrieve URL** | $O(1)$ | $O(1)$ |