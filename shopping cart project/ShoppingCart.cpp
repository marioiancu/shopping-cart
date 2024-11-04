#include "ShoppingCart.h"
#include "DiscountFactory.h"
#include <iostream>
#include <algorithm>

using namespace std;

void ShoppingCart::addProduct(Product& product, int quantity) {
    Inventory<Product>& inventory = Inventory<Product>::getInstance();

    if (product.getStock() < quantity) {
        cout << "Insufficient stock available for " << product.getName() << ".\n";
        return;
    }

    for (auto& item : items) {
        if (item.getProduct() == product) {
            item.setQuantity(item.getQuantity() + quantity);
            inventory.reduceStock(product.getName(), quantity);
            return;
        }
    }

    items.push_back(CartItem(product, quantity));
    inventory.reduceStock(product.getName(), quantity);
}

void ShoppingCart::removeProduct(Product& product) {
    auto it = find_if(items.begin(), items.end(),
        [&product](CartItem& item) {
            return item.getProduct() == product;
        });

    if (it != items.end()) {
        int quantityToRemove = it->getQuantity();
        Inventory<Product>& inventory = Inventory<Product>::getInstance();
        inventory.addStock(product.getName(), quantityToRemove);

        items.erase(it);
        cout << "Removed " << product.getName() << " from the cart.\n";
    }
    else {
        cout << "Product not found in the cart.\n";
    }
}

double ShoppingCart::getTotalPrice() const {
    double total = 0;
    for (const auto& item : items) {
        total += item.getTotalPrice();
    }
    return total;
}

int ShoppingCart::searchProduct(Product& prod) {
    for (auto& item : items) {
        if (prod == item.getProduct()) {
            return item.getQuantity();
        }
    }
    return 0;
}

void ShoppingCart::displayCart() const {
    cout << "\n\t\tYour Cart:\n";
    cout << "----------------------------------------------" << endl;
    for (const auto& item : items) {
        cout << item << endl;
    }
    cout << "----------------------------------------------" << endl;
    cout << "\n\tTotal Cart Price: $" << getTotalPrice() << endl;
}

void ShoppingCart::menu(Inventory<Product>& inventory) {
    int choice;
    do {
        cout << "\n\t\tShopping Cart & Products Management" << endl;
        cout << "\t\t------------------------------------" << endl;
        cout << "\n 1. View Available Products\n 2. Add Product to Cart\n 3. Remove Product from Cart\n 4. Display Cart\n 5. Pay Bill\n 6. Check Product Details\n 7. Return Back\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "\nAvailable Products in Inventory:\n";
            inventory.displayItems();
            break;
        }
        case 2: {
            string productName;
            int quantity;
            cout << "\nEnter product name: ";
            cin >> productName;

            Product* product = inventory.getItem(productName);
            if (product == nullptr) {
                cout << "Product not found in inventory.\n";
                break;
            }

            cout << "\nEnter quantity to add (Available Stock: " << product->getStock() << "): ";
            cin >> quantity;

            if (quantity <= product->getStock()) {
                addProduct(*product, quantity);
                product->setStock(product->getStock() - quantity);
            }
            else {
                cout << "Not enough stock available.\n";
            }
            break;
        }
        case 3: {
            string productName;
            cout << "\nEnter product name to remove from cart: ";
            cin >> productName;

            Product* product = inventory.getItem(productName);
            if (product == nullptr) {
                cout << "Product not found in inventory.\n";
                break;
            }

            int currentQuantity = searchProduct(*product);
            if (currentQuantity > 0) {
                removeProduct(*product);
                product->setStock(product->getStock() + currentQuantity);
            }
            else {
                cout << "Product not found in cart.\n";
            }
            break;
        }
        case 4:
            displayCart();
            break;

        case 5: {
            double totalPrice = getTotalPrice();
            string discountType;
            do {

                cout << "\nEnter discount type (none/percentage): ";
                cin >> discountType;
            } while (discountType != "none" && discountType != "percentage");

            Discount* discount = DiscountFactory::createDiscount(discountType);
            if (discount) {
                totalPrice = discount->applyDiscount(totalPrice);
                delete discount;
            }
            cout << "Total after discount: $" << totalPrice << endl;
            break;
        }
        case 6: {
            string productName;
            cout << "\nEnter product name to view details: ";
            cin >> productName;

            Product* product = inventory.getItem(productName);
            if (product == nullptr) {
                cout << "Product not found in inventory.\n";
            }
            else {
                product->displayProductDetails(*product);
            }
            break;
        }
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 7);
}


