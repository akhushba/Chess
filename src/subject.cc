#include "subject.h"

void Subject::attach(Observer *o) {
    observers.push_back(o);
}

void Subject::detach(Observer *o) {
    
}

void Subject::notifyObservers() {
    
}

Subject::~Subject() {
    
}