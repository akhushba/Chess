#include "player.h"

using namespace std;

Player::Player(string name, vector<Piece*> pieceSet) : name{name}, pieceSet{pieceSet} {}

bool Player::callSimulateAttack(Piece* p, char newC, int newI, Piece* reference) {
    if (reference) {
        return board->simulateAttack(p, newC, newI, reference);
    }
    return board->simulateAttack(p, newC, newI);
}

Player::~Player() {}