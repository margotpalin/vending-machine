#include "Meal.h"
Meal::Meal(const std::string& id, const std::string& name, const std::string& description, double price) {
    if (!isValidNameOrDescription(name) || !isValidNameOrDescription(description)) {
        throw std::invalid_argument("Name or description cannot contain the '|' character.");
    }
    if (!isValidPrice(price)) {
        throw std::invalid_argument("Price must be a multiple of 5.");
    }
    this->id = id;
    this->name = name;
    this->description = description;
    this->price = price;
}

bool Meal::isValidNameOrDescription(const std::string& str) {
    return str.find('|') == std::string::npos;
}

bool Meal::isValidPrice(double price) {
    return static_cast<int>(price*100) % 5 == 0;
}

void Meal::display() const {
    std::cout << std::left << std::setw(5) << id << "|"
                  << std::setw(50) << name
                  << "|$" <<std::setw(8)<< std::fixed << std::setprecision(2) << price<< std::endl;
    }


