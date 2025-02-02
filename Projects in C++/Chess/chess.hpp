#ifndef CHESS_HPP
#define CHESS_HPP

class Piece {
protected:
    char color;
    int x;
    int y;

public:
    Piece();
    Piece(char color);
    char getColor() const;
    bool setColor(char color);
    void setMove(int x, int y);
    virtual bool permissibleMove(int x, int y) const = 0;
    virtual char getSymbol() const = 0;
};

#endif
