#ifndef CARTITEM_H
#define CARTITEM_H

#include "Product.h"

using namespace std;

class CartItem {
private:
    Product product;
    int quantity;

public:
    CartItem(const Product& product, int quantity);

    Product& getProduct();
    int getQuantity() const;
    void ProductDetails(Product& prod)const;
    string getItemName()const;
    double getItemPrice()const;

    void setQuantity(int qty);
    double getTotalPrice() const;

    friend ostream& operator<<(ostream& os, const CartItem& item);
};

#endif
