#include "player.h"

using namespace std;

Player::Player(string name, Colour c) : name{name}, colour{c} {}

string Player::getName() { return name; }

Player::~Player() {}

