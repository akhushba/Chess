#include "player.h"

using namespace std;

Player::Player(string name, vector<Piece*> ps, Colour c) : name{name}, pieceSet{ps}, colour{c} {
    // if (c == WHITE) {
    //     *pieceSet = board->whitePlayer->activePieces;
    // } else if (c == BLACK) {
    //     *pieceSet = board->blackPlayer->activePieces;
    // }
}

bool Player::callSimulateAttack(Piece* p, char newC, int newI, Piece* reference) {
    if (reference) {
        return board->simulateAttack(p, newC, newI, reference);
    }
    return board->simulateAttack(p, newC, newI);
}

string Player::getName() {
    return name;
}

// bool Player::canCapture(Colour pieceColour, char c, int i) {
//     cout << c << " and " << i << endl;
//     Piece* piece = board->getBoardInfo(c, i);
//     return piece && piece->getColour() != pieceColour;
// }

Player::~Player() {}

