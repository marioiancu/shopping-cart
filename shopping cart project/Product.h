#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>


using namespace std;

class Product {
private:
    string name;
    double price;
    string category;
    int stock;

public:
    Product();
    Product(const string& name, double price, string cat, int stock);
    Product(const Product& copy);
    Product& operator=(const Product& copy);
    ~Product();

    friend ostream& operator<<(ostream& os, const Product& product);
    friend istream& operator>>(istream& is, Product& product);

    bool operator==(const Product& prod) const;
    void displayProductDetails(Product& prod)const;

    double getPrice() const;
    string getName() const;
    string getCategory() const;
    int getStock() const;

    void setPrice(double p);
    void setName(string n);
    void setCategory(string);
    void setStock(int s);
};

#endif
