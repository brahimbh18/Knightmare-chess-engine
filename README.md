# ♟️ C++ Chess Engine Prototype

A scalable, FEN-based chess engine written in modern C++.
Generates legal moves or applies a move to return the new FEN.
Designed for backend API integration (Spring Boot, Go, etc.) and built with a clean, extensible architecture for future search algorithms.

## ✨ Features

- **🎯 Move Validation** – Validates chess moves using FEN positions
- **🚀 Legal Move Generation** – Generates all legal moves for any piece position
- **🔒 King Safety** – Checks attacks and ensures king safety rules
- **🏰 Castling Support** – Validates and manages castling rights
- **♟️ En Passant** – Implements en passant capture logic
- **📊 FEN Parsing** – Reads and generates Forsyth–Edwards Notation
- **🔧 API Ready** – Stateless design for backend integration
- **⚡ Performance** – Efficient move generation and memory usage

## 🚀 Quick Start

### Prerequisites
- C++ compiler (C++17 or later)
- GNU Make
- Linux/macOS (tested on Arch Linux)

### Build & Run
```bash
# Build
make

# Test API functions
make test-api
```


## 🛠️ Current Goals

- **♙ Add pawn promotion**
- **🔌 Finish Spring Boot integration**
- **🧠 Implement basic evaluation function**
- **⚡ Prepare framework for search algorithms**

## 📜 Status

Prototype stage — functional but evolving.
Core move generation and validation are implemented, but promotions, backend connectivity, and advanced AI are still planned.

---

**Built with ❤️ for the chess programming community**