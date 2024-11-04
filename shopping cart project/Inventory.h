#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

template <typename T>
class Inventory {
private:
    map<string, T> inventoryItems;
    const string fileName = "inventory.txt"; // File to store inventory

    void saveToFile();       // Save inventory to file
    void loadFromFile();     // Load inventory from file

    Inventory() {
        loadFromFile();      // Load inventory on program start
    }

public:
    // Delete copy constructor and assignment operator
    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;

    static Inventory& getInstance() {
        static Inventory instance;
        return instance;
    }

    void addItem(const string& name, T item);
    void addItem();
    void removeItem(const string& name);
    void displayItems() const;
    void sortItemsByPrice();
    void sortItemsByCategory(); // New function to sort by category
    void menu();
    T* getItem(const string& name);
    void updateStock(const string& name, int stock); // New function to update stock
    void addStock(const string& name, int quantity); // Add to stock
    void reduceStock(const string& name, int quantity); // Remove from Stock
};

// Add item with given name and item
template <typename T>
void Inventory<T>::addItem(const string& name, T item) {
    inventoryItems[name] = item;
    saveToFile();  // Update file after adding item
}

// Add item interactively from user input
template <typename T>
void Inventory<T>::addItem() {
    string name;
    double price;
    string category;
    int stock;

    cout << "Enter Item Name: ";
    cin >> name;
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Category: ";
    cin >> category;
    cout << "Enter Stock Quantity: ";
    cin >> stock;

    T item(name, price, category, stock);
    inventoryItems[name] = item;
    saveToFile();
}


template <typename T>
void Inventory<T>::removeItem(const string& name) {
    inventoryItems.erase(name);
    saveToFile();
}


template <typename T>
void Inventory<T>::displayItems() const {
    if (inventoryItems.empty()) {
        cout << "No items in the inventory." << endl;
        return;
    }

    cout << endl << left << setw(20) << "Item Name"
        << setw(10) << "Price"
        << setw(15) << "Category"
        << setw(10) << "Stock" << endl;
    cout << string(55, '-') << endl;

    for (const auto& pair : inventoryItems) {
        const string& name = pair.first;
        const T& item = pair.second;
        cout << left << setw(20) << name
            << setw(10) << item.getPrice()
            << setw(15) << item.getCategory()
            << setw(10) << item.getStock() << endl;
    }
}


// Sort items by price
template <typename T>
void Inventory<T>::sortItemsByPrice() {
    vector<pair<string, T>> items(inventoryItems.begin(), inventoryItems.end());


    sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
        return a.second.getPrice() < b.second.getPrice();
        });

    cout << endl << left << setw(20) << "Item Name"
        << setw(10) << "Price" << endl;
    cout << string(30, '-') << endl;

    for (const auto& pair : items) {
        cout << left << setw(20) << pair.first
            << setw(10) << pair.second.getPrice() << endl;
    }
}


// Sort items by category
template <typename T>
void Inventory<T>::sortItemsByCategory() {
    vector<pair<string, T>> items(inventoryItems.begin(), inventoryItems.end());

    // Sort by category (alphabetically)
    sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
        return a.second.getCategory() < b.second.getCategory();
        });

    cout << endl << left << setw(20) << "Item Name"
        << setw(10) << "Price"
        << setw(15) << "Category"
        << setw(10) << "Stock" << endl;
    cout << string(55, '-') << endl;

    for (const auto& pair : items) {
        cout << left << setw(20) << pair.first
            << setw(10) << pair.second.getPrice()
            << setw(15) << pair.second.getCategory()
            << setw(10) << pair.second.getStock() << endl;
    }
}


template <typename T>
void Inventory<T>::menu() {
    int choice;
    do {
        cout << "\n\t\tInventory Management" << endl;
        cout << "\t\t----------------------" << endl;
        cout << "\n 1. Add Item\n 2. Remove Item\n 3. Display Items\n 4. Sort Items by Price\n 5. Sort Items by Category\n 6. Update Stock\n 7. Exit\n\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            this->addItem();
            break;
        case 2: {
            string name;
            cout << "\nEnter Name of Item to remove: ";
            cin >> name;
            this->removeItem(name);
            break;
        }
        case 3:
            this->displayItems();
            break;
        case 4:
            this->sortItemsByPrice();
            break;
        case 5:
            this->sortItemsByCategory();
            break;
        case 6: {
            string name;
            int stock;
            cout << "\nEnter Item Name: ";
            cin >> name;
            cout << "Enter New Stock Quantity: ";
            cin >> stock;
            this->updateStock(name, stock);
            break;
        }
        case 7:
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 7);
}


template <typename T>
void Inventory<T>::updateStock(const string& name, int stock) {
    auto it = inventoryItems.find(name);
    if (it != inventoryItems.end()) {
        it->second.setStock(stock);  // Update stock
        saveToFile();
    }
    else {
        cout << "Item not found!" << endl;
    }
}

// Get item by name
template <typename T>
T* Inventory<T>::getItem(const string& name) {
    auto it = inventoryItems.find(name);
    if (it != inventoryItems.end()) {
        return &it->second;
    }
    return nullptr;
}

// Save inventory data to a file
template <typename T>
void Inventory<T>::saveToFile() {
    ofstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (const auto& pair : inventoryItems) {
        file << pair.first << ","
            << pair.second.getPrice() << ","
            << pair.second.getCategory() << ","
            << pair.second.getStock() << endl;
    }

    file.close();
}

// Load inventory data from a file
template <typename T>
void Inventory<T>::loadFromFile() {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "File not found, creating a new one." << endl;
        ofstream createFile(fileName);
        createFile.close();
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        double price;
        string category;
        int stock;

        if (getline(ss, name, ',') && ss >> price && ss.ignore() && getline(ss, category, ',') && ss >> stock) {
            T item(name, price, category, stock);
            inventoryItems[name] = item;
        }
    }

    file.close();
}

template <typename T>
void Inventory<T>::addStock(const string& name, int quantity) {
    auto it = inventoryItems.find(name);
    if (it != inventoryItems.end()) {
        int currentStock = it->second.getStock();
        it->second.setStock(currentStock + quantity);
        saveToFile();
        cout << "Stock updated successfully." << endl;
    }
    else {
        cout << "Item not found!" << endl;
    }
}

template <typename T>
void Inventory<T>::reduceStock(const string& name, int quantity) {
    auto it = inventoryItems.find(name);
    if (it != inventoryItems.end()) {
        int currentStock = it->second.getStock();
        if (currentStock >= quantity) {
            it->second.setStock(currentStock - quantity);
            saveToFile();
            cout << "Stock reduced successfully." << endl;
        }
        else {
            cout << "Insufficient stock to reduce!" << endl;
        }
    }
    else {
        cout << "Item not found!" << endl;
    }
}



#endif 
