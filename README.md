♟️ C++ Chess Engine Prototype
📌 Overview

This is an early-stage, scalable C++ chess engine prototype.
It works entirely from FEN (Forsyth–Edwards Notation) input and can:

Generate all legal moves for a given position

Apply a move to a given FEN and return the updated FEN

Although currently a standalone engine, it is designed for future Spring Boot backend integration and to serve as the foundation for adding AI search algorithms.

✨ Features

FEN parsing & validation

Legal move generation (all pieces)

Castling & en passant support

Move application with updated FEN

🚧 Current Goals

♙ Add pawn promotion

🔌 Complete Spring Boot integration

🧠 Implement basic evaluation function

⚡ Prepare for search algorithms (minimax, alpha-beta)

🛠 Build & Run
    make test-api
    ./build/test_api

📜 Status

Prototype stage — functional but evolving.
Chess programming is vast, and this is the foundation for bigger things ahead.