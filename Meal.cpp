#include "Meal.h"
Meal::Meal(std::string _id, std::string _name, std::string _description, double _price)
        : id(_id), name(std::move(_name)), description(std::move(_description)), price(_price) {}

void Meal::display() const {
    std::cout << std::left << std::setw(10) << id
                  << std::setw(20) << name
                  << "$" << std::setw(8) << std::fixed << std::setprecision(2) << price << std::endl;
    }
