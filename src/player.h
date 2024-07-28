#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "piece.h"
#include "gameinfo.h"

using namespace std;

class Player {
protected:
    string name;
    BoardDisplay *board;
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
    vector<Piece*> pieceSet; 
    Player() {}
    Player(string name, vector<Piece*> pieceSet) : name{name}, pieceSet{pieceSet} {}
    virtual void move(Piece* p = nullptr, char c = '\0', int i = -1) = 0;
    bool callSimulateAttack(Piece*, char newC, int newI, Piece* reference = nullptr);
    virtual ~Player() {}
};

#endif
