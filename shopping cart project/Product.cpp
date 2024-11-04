#include "Product.h"

using namespace std;

Product::Product()
    : name(""), price(0), category(""), stock(0) {}

Product::Product(const string& name, double price, string cat, int stock)
    : name(name), price(price), category(cat), stock(stock) {}

Product::Product(const Product& copy)
    : name(copy.name), price(copy.price), category(copy.category), stock(copy.stock) {}

Product& Product::operator=(const Product& copy) {
    if (this != &copy) {
        name = copy.name;
        price = copy.price;
        category = copy.category;
        stock = copy.stock;
    }
    return *this;
}

Product::~Product() {}

ostream& operator<<(ostream& os, const Product& product) {
    os << "\n -Product: " << product.name << "\t\t-Price: $" << product.price
        << "\t-Category: " << product.category << "\t-Stock: " << product.stock;
    return os;
}

istream& operator>>(istream& is, Product& product) {
    cout << "\nEnter product name: ";
    is >> product.name;
    cout << "Enter price: ";
    is >> product.price;
    cout << "Enter Item Category: ";
    is >> product.category;
    cout << "Enter Available Stock: ";
    is >> product.stock;
    return is;
}

bool Product::operator==(const Product& prod) const {
    return name == prod.name && price == prod.price;
}

void Product::displayProductDetails(Product& prod) const {
    cout << "\t--------------------------------";
    cout << "\n\tProduct Details:\n\n";
    cout << " \tName: " << prod.getName() << endl;
    cout << " \tCategory: " << prod.getCategory() << endl;
    cout << " \tPrice: $" << prod.getPrice() << endl;
    cout << " \tAvailable Stock: " << prod.getStock() << endl;
    cout << "\n\t--------------------------------" << endl << endl;
}


double Product::getPrice() const { return price; }
string Product::getName() const { return name; }
string Product::getCategory() const { return category; }
int Product::getStock() const { return stock; }  // Getter for stock

void Product::setPrice(double p) { price = p; }
void Product::setName(string n) { name = n; }
void Product::setCategory(string cat) { category = cat; }
void Product::setStock(int s) { stock = s; }  // Setter for stock
