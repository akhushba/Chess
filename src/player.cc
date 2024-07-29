#include "player.h"

using namespace std;

bool Player::callSimulateAttack(Piece* p, char newC, int newI, Piece* reference) {
    if (reference) {
        return board->simulateAttack(p, newC, newI, reference);
    }
    return board->simulateAttack(p, newC, newI);
}
