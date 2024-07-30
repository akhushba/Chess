#ifndef HUMAN_H
#define HUMAN_H

class Human : public Player {
    public:
        Human(string name, vector<Piece*> pieceSet, Colour c);
        pair<Piece*, pair<char, int>> move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves) override;
        ~Human() override = default;
};

#endif
