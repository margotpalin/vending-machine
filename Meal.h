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
   Meal(std::string _id, std::string _name, std::string _description, double _price);
    // Method to display meal details
    void display() const;
};


#endif // MEAL_H