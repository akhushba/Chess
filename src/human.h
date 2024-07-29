#ifndef HUMAN_H
#define HUMAN_H

class Human : public Player {
    public:
        Human(string name, vector<Piece*> pieceSet);
        void move(Piece*p, char c, int i) override;
        ~Human() override = default;
};

#endif
