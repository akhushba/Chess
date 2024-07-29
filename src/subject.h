#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>

class Observer;

class Subject {
  std::vector<std::unique_ptr<Observer>> observers;
  public:
    virtual void attach(Observer *o);
    virtual void detach(Observer *o);
    virtual void notifyObservers();
    virtual ~Subject() = 0;
};

#endif
