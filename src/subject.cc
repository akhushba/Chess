#include "subject.h"
#include "observer.h"

void Subject::attach(Observer *o) {
    observers.emplace_back(o); 
}

void Subject::detach(Observer *o) {
    auto it = std::remove_if(observers.begin(), observers.end(),
                             [o](const std::unique_ptr<Observer>& observer) {
                                 return observer.get() == o;
                             });
    if (it != observers.end()) {
        observers.erase(it, observers.end());
    }
}

void Subject::notifyObservers() {
    for (const auto& observer : observers) {
        observer->notify(); 
    }
}

Subject::~Subject() = default;
