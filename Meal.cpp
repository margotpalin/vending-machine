#include "Meal.h"
Meal::Meal(std::string _id, std::string _name, std::string _description, double _price)
        : id(_id), name(std::move(_name)), description(std::move(_description)), price(_price) {}

void Meal::display() const {
    std::cout << "ID: " << id << ", Name: " << name << ", Price: $" << std::setprecision(2) << std::fixed << price << std::endl;
    std::cout << "Description: " << description << std::endl;
}
