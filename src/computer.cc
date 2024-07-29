#include "computer.h"

using namespace std;

Computer::Computer(string name, vector<Piece*> *pieceSet, Colour c) : Player(name, pieceSet, c) {}

Computer::~Computer() {}
