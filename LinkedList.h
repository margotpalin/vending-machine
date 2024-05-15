#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    void add_front(Meal* meal);
    void add_back(Meal* meal);
    void display() const;
    bool removeMeal(const std::string& mealId);
    Meal* findMealById(const std::string& mealId) const;
    Node* getHead() const;

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H
