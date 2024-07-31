#include "subject.h"
#include "observer.h"

#include <algorithm>
#include <iostream>

using namespace std;

void Subject::attach(Observer *o) {
    observers.emplace_back(o); 
}

void Subject::notifyObservers() {
    for (const auto& observer : observers) {
        observer->notify(); 
    }
}
//using unique ptrs so we don't have to do any clean up
Subject::~Subject() = default;

