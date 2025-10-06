# 📚 Binary Search Tree Dictionary (C)

A simple **command-line dictionary** implemented in **C**, using a **Binary Search Tree (BST)** for fast insert, search, delete, and traversal operations.

Each entry stores a **word** and its **definition**, and the dictionary supports saving/loading to a CSV file for persistence.

---

## 🧠 Features

✅ **Binary Search Tree (BST)**

- Insert, search, delete in average **O(log n)** time.
- Stores (word, definition) pairs alphabetically.

✅ **Command-Line Interface**

- Interactive text-based UI for adding, finding, deleting, and listing entries.

✅ **Persistence**

- Save your dictionary to a `.csv` file.
- Load data from a `.csv` file (updates or merges automatically).

✅ **Clean Modular Design**

- Organized into multiple files for readability:
  - `bst.c / bst.h` — tree logic
  - `io.c / io.h` — CSV file I/O
  - `util.c / util.h` — helper utilities
  - `main.c` — command-line driver

---

## 🗂️ Folder Structure

```text
BinarySearchTree-Dictionary/
│
├── include/
│ ├── bst.h
│ ├── io.h
│ └── util.h
│
├── src/
│ ├── bst.c
│ ├── io.c
│ ├── util.c
│ └── main.c
│
└── Makefile
```

## ⚙️ Build Instructions

Make sure you have **gcc** installed (it comes with Xcode Command Line Tools on macOS).

### 1️⃣ Build

```bash
make
```

### 2️⃣ Run

```bash
./dict
```

You should see:
BST Dictionary (C) — type 'help' for commands.

```text
> 🧾 Commands
> Command Description
> `add <word>	<definition>`
> find <word> Looks up a word’s definition
> del <word> Deletes a word
> list Lists all words alphabetically
> save <file.csv> Saves dictionary to CSV
> load <file.csv> Loads entries from CSV
> help Shows available commands
> quit Exits the program
```

## Example Session

```bash
> add apple|a fruit
OK: added/updated 'apple'
> add array|contiguous memory structure
OK: added/updated 'array'
> find apple
apple: a fruit
> list
- apple: a fruit
- array: contiguous memory structure
> save words.csv
Saved to words.csv
> quit
```

## 💻 Implementation Details

```text
Language: C (C11)
Average complexities:
insert, search, delete: O(log n)
list (inorder): O(n)
Data Structure: Binary Search Tree
Persistence: CSV read/write with simple string parsing
Platform: macOS / Linux / WSL
```
