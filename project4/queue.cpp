/*
queue.cpp

Author: Jiwoo Lee

Short description of this file: defines functions of class Queue
*/

#include "queue.h"

// constructor. maxlen must be as large as the total number
// of Locations that will ever be entered into this Queue.
// this is complete, you don't need to change it.
Queue::Queue(int maxlen) {
   contents = new Location[maxlen];
   head = 0;
   tail = 0;
}

// destructor. releases resources. C++ will call it automatically.
// this is complete, you don't need to change it.
Queue::~Queue() {
   delete[] contents;
}

// insert a new Location at the end/back of our list
void Queue::push(Location loc) {
  contents[tail] = loc;
  tail++;
}

// return and "remove" the oldest Location not already extracted
Location Queue::pop() {
  Location oldestLoc = contents[head];
  head++;
  return oldestLoc;
}

// is this Queue empty? (did we extract everything added?)
bool Queue::is_empty() {

  if (head == tail) {
    return true;
  }
  else {
    return false;
  }

}
