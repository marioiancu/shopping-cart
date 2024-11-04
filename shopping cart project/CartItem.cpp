#include "CartItem.h"

using namespace std;

CartItem::CartItem(const Product& product, int quantity)
    : product(product), quantity(quantity) {}

Product& CartItem::getProduct() { return product; }
int CartItem::getQuantity() const { return quantity; }

void CartItem::setQuantity(int qty) { quantity = qty; }
double CartItem::getTotalPrice() const { return product.getPrice() * quantity; }

ostream& operator<<(ostream& os, const CartItem& item) {
    os << "\n-Product: " << item.getItemName()
        << "\t-Price: $" << item.getItemPrice()
        << "\t-Quantity: " << item.getQuantity()
        << "\t-Total: $" << item.getTotalPrice();
    return os;
}

string CartItem::getItemName() const { return product.getName(); }
double CartItem::getItemPrice() const { return product.getPrice(); }

void CartItem::ProductDetails(Product& prod)const { prod.displayProductDetails(prod); }
