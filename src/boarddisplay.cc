#include "boarddisplay.h"

void BoardDisplay::attach(Observer* o) {
    Subject::attach(o);
}

void BoardDisplay::detach(Observer* o) {
    
}

void BoardDisplay::notifyObservers() {
    
}

char BoardDisplay::getState(int row, int col) const {

}

BoardDisplay::~BoardDisplay() {

}