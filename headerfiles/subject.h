#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Observer;

class Subject {
  std::vector<Observer*> observers;
 public:
  virtual void attach(Observer *o);
  virtual void detach(Observer *o);
  virtual void notifyObservers();
  virtual ~Subject() = 0;
};

#endif
