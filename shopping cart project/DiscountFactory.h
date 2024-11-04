#ifndef DISCOUNTFACTORY_H
#define DISCOUNTFACTORY_H

#include<iostream>
using namespace std;

class Discount {
public:
    virtual double applyDiscount(double total) = 0;
    virtual ~Discount() {}
};

class NoDiscount : public Discount {
public:
    double applyDiscount(double total) override {
        return total;
    }
};

class PercentageDiscount : public Discount {
private:
    double percentage;
public:
    PercentageDiscount(double p) : percentage(p) {}
    double applyDiscount(double total) override {
        return total - (total * (percentage / 100));
    }
};

class DiscountFactory {
public:
    static Discount* createDiscount(const string& type) {
        if (type == "none") return new NoDiscount();
        else if (type == "percentage") {
            double percentage;
            cout << "Enter discount percentage: ";
            cin >> percentage;
            return new PercentageDiscount(percentage);
        }
        return nullptr;
    }
};


#endif
