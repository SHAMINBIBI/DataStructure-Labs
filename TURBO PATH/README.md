# 🚀SHAM'S Turbo-Path File Search Utility

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-green.svg)]()


---

## 📖 1. Project Overview

Turbo-Path is a **high-performance digital archive search utility** designed to index massive directory structures into RAM using a custom **AVL Tree**. It enables **instantaneous file searching**, eliminating the slow real-time disk searches of traditional operating systems.

> ⚡ **Key Benefit:** Search results in milliseconds instead of minutes!

---

## ✨ 2. Features

### 🔍 **Phase 1: Indexing**
- Iterative **Breadth-First Search (BFS)** traversal
- Maps hierarchical structure into memory-efficient RAM storage

### 🎯 **Phase 2: Fast Search**
- **O(log n)** search speed using self-balancing **AVL Tree**
- Instant results regardless of directory size

### 🔄 **Phase 3: Real-Time Updates**
- `refresh` - Re-index current directory
- `cd` - Change target directory without restart

### 🎁 **Bonus Features**
- **Duplicate Handling** - Lists all files with same name across different folders
- **Memory Optimization** - Parent-pointer architecture with O(n) space complexity
- **Smart Search** - Search with or without extensions (e.g., "report" finds "report.pdf")

---

## 📋 3. Prerequisites

| Requirement | Details |

| **Compiler** | C++17 compatible (for `<filesystem>` library) |

| **Recommended** | GCC 7+, Clang 5+, or Visual Studio 2017+ |

| **OS Support** | Windows, Linux, macOS |

---

## 📁 4. File Structure
Turbo-Path/

├── 📄 AVL.h # AVL Tree implementation (required)

├── 🎯 turboPath.cpp # Main program file

└── 📖 README.md # This file

text

---

## 🛠️ 5. Compilation Instructions

### 🐧 Linux / macOS / MinGW

```bash
# Navigate to project folder
cd /path/to/Turbo-Path

# Compile
g++ -std=c++17 turboPath.cpp -o turboPath

# Run
./turboPath
🪟 Windows (MinGW)
bash
g++ -std=c++17 turboPath.cpp -o turbopath.exe
turbopath.exe
🎨 Visual Studio 2022
Step	Action
1	Open Visual Studio → Create new C++ Console Application
2	Add turboPath.cpp and AVL.h to project
3	Right-click project → Properties
4	Set Configuration → "All Configurations"
5	Navigate: C/C++ → Language → C++ Language Standard
6	Select: ISO C++17 Standard (/std:c++17)
7	Click OK → Build → Build Solution (Ctrl+Shift+B)
8	Run with Ctrl+F5
🚀 6. Usage Guide
Starting the Program
text
==================================================
      Welcome to Sham's Turbo-Path Search     
==================================================

Enter the root directory path to index (e.g., . or C:/): ./Documents
Turbo Path is indexing files into RAM.Please wait.
Indexing is complete. TurboPath has indexed 1523 files
Enter file name (or 'refresh' to update, 'cd' to change directory, 'exit' to quit)