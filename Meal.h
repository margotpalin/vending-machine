#ifndef MEAL_H
#define MEAL_H

#include <iostream>
#include <string>
#include <iomanip>

class Meal {
public:
    std::string id;
    std::string name;
    std::string description;
    double price;

    // Constructor to initialize the meal
   Meal(const std::string& id, const std::string& name, const std::string& description, double _price);
    // Method to display meal details
    void display() const;
};


#endif // MEAL_H
