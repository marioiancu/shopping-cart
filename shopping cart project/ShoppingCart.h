#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <vector>
#include "CartItem.h"
#include "inventory.h"

using namespace std;

class ShoppingCart {
private:
    vector<CartItem> items;

public:
    void addProduct(Product& product, int quantity);
    void removeProduct(Product& product);
    double getTotalPrice() const;
    int searchProduct(Product& prod);
    void displayCart() const;
    void menu(Inventory<Product>& inventory);
};

#endif
