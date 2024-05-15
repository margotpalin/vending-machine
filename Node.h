#ifndef NODE_H
#define NODE_H
#include <string> 
#include "Meal.h"

//The length of the id string not counting the nul terminator
#define IDLEN 5

//The maximum length of a food item name not counting the nul terminator
#define NAMELEN 40

//The maximum length of a food item description not counting the nul terminator.
#define DESCLEN 255

//The default coin level to reset the coins to on request
#define DEFAULT_COIN_COUNT 20

//The possible default food stock level that all new stock should start at and that we should reset to on restock
#define DEFAULT_FOOD_STOCK_LEVEL 20

//The number of denominations of currency available in the system 
#define NUM_DENOMS 8
enum Denomination
{
    FIVE_CENTS=5, TEN_CENTS=10, TWENTY_CENTS=20, FIFTY_CENTS=50, ONE_DOLLAR=100, 
    TWO_DOLLARS=200, FIVE_DOLLARS=500, TEN_DOLLARS=1000, TWENTY_DOLLARS=2000, FIFTY_DOLLARS=5000
};


/**
 * the node that holds the data about a food item stored in memory
 **/
class Node
{
public:
    Node(Meal* _data, Node* _next = nullptr);
    ~Node();
    // pointer to the data held for the node 
    Meal* data;
    // pointer to the next node in the list 
    Node* next;
};

#endif // NODE_H
