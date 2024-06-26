#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "LinkedList.h"

class Menu {
private:
    LinkedList mealList;
    int nextId=1;
public:
    std::string previewNextMealId() const;
    std::string getNextMealId();
    // Adds a meal to the menu
    void addMeal(const std::string& name, const std::string& description, double price);

    // Removes a meal from the menu by ID
    void removeMeal(std::string mealId);

    // Displays all meals in the menu
    void displayMeals() const;
    Meal findMeal(const std::string& mealId) const; 

    // Loads meals from a file
    bool loadFromFile(const std::string& filename);

    // Saves meals to a file
    bool saveToFileMeal(const std::string& filename) const;
};

#endif // MENU_H
