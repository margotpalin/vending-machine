#include "Meal.h"
Meal::Meal(const std::string& id, const std::string& name, const std::string& description, double _price)
        : id(id), name(name), description(description), price(_price) {}

void Meal::display() const {
    std::cout << std::left << std::setw(5) << id << "|"
                  << std::setw(50) << name
                  << "|$" <<std::setw(8)<< std::fixed << std::setprecision(2) << price<< std::endl;
    }

