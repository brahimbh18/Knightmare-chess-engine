#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <memory>
#include <cctype>

class Piece {
    private:
        std::string type;
        std::string color;
        
    public:
        Piece(const std::string& type, const std::string& color);
        static std::unique_ptr<Piece> generatePieceByFENCHAR(const char c);
        
        std::string getType() const;
        std::string getColor() const;
};

#endif