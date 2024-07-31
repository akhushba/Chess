#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "piece.h"
#include "boarddisplay.h"

using namespace std;

class BoardDisplay;
class Piece;

class Player {
protected:
    string name;
    Colour colour;
    class CustomException : public std::exception {
        private:
            std::string message;

        public:
            explicit CustomException(const std::string& msg) : message(msg) {}

            // Override the what() function to return the exception message
            const char* what() const noexcept override {
                return message.c_str();
            }
    };
public:
    Player(string name, Colour c);
    string getName();
    
    // virtual void move(Piece* p = nullptr, char c = '\0', int i = -1) = 0;
    virtual pair<Piece*, pair<char, int>> move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves, vector<pair<Piece*, vector<pair<char, int>>>> opponentPieceAndMoves) = 0;
    virtual ~Player() = 0;
};

#endif

