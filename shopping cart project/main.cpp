#include "ShoppingCart.h"
#include "Inventory.h"

using namespace std;

int main() {
    Inventory<Product>& inventory = Inventory<Product>::getInstance();
    ShoppingCart cart;
    int choice;
    do {
        cout << "\n\t\t INVENTORY AND SHOPPING MANAGEMENT SYSTEM" << endl;
        cout << " \t\t-----------------------------------------" << endl;

        cout << "\n\t1. Inventory Management\n\t2. Shopping Cart\n\t3. Exit\n\n Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: inventory.menu(); break;
        case 2: cart.menu(inventory); break;
        case 3: cout << "\n\tSee you again!" << endl; break;
        default: cout << "Invalid Choice!" << endl;
        }

    } while (choice != 3);

    return 0;
}


