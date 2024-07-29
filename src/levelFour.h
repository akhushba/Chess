#ifndef LEVELONE_H
#define LEVELONE_H

class LevelFour : public Computer {
public:
    LevelFour(string name, vector<Piece*> pieceSet);
    void move(Piece* p = nullptr, char c = '\0', int i = -1) override;
    int getMaxPieceValue(vector<pair<Piece*, tuple<char, int>>>) override;
    ~LevelFour() override;
};

#endif