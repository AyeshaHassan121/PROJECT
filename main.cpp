#include<iostream>
#include<string>
using namespace std;

struct Item {
    int id;
    string name;
    float price;
    int quantity;
};
void addItem(Item* &menu, int &count);
void displayMenu(Item* menu, int count);
void updateItem(Item* menu, int count);
void removeItem(Item* &menu, int &count);
void searchItem(Item* menu, int count);
void sortMenuByPrice(Item* menu, int count);
void orderItem(Item* menu, int menuCount, Item* &cart, int &cartCount);
void displayCart(Item* cart, int cartCount);
void cancelOrder(Item* &cart, int &cartCount);
void updateCart(Item* cart, int cartCount);
void calculateTotal(Item* cart, int cartCount);
void mainMenu();

int main() {
    mainMenu();
    return 0;
}
void mainMenu() {
    Item* menu = nullptr;
    Item* cart = nullptr;
    int menuCount = 0, cartCount = 0;
    int choice;

    do {
        cout << "\n=== Online Food Ordering System ===\n";
        cout << "1. Add Menu Item\n2. Display Menu\n3. Update Menu Item\n4. Remove Menu Item\n";
        cout << "5. Search Item\n6. Sort Menu by Price\n7. Order Item\n8. Display Cart\n";
        cout << "9. Cancel Order\n10. Update Cart\n11. Calculate Total\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addItem(menu, menuCount); break;
            case 2: displayMenu(menu, menuCount); break;
            case 3: updateItem(menu, menuCount); break;
            case 4: removeItem(menu, menuCount); break;
            case 5: searchItem(menu, menuCount); break;
            case 6: sortMenuByPrice(menu, menuCount); break;
            case 7: orderItem(menu, menuCount, cart, cartCount); break;
            case 8: displayCart(cart, cartCount); break;
            case 9: cancelOrder(cart, cartCount); break;
            case 10: updateCart(cart, cartCount); break;
            case 11: calculateTotal(cart, cartCount); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 0);

    delete[] menu;
    delete[] cart;
}

void displayMenu(Item* menu, int count) {
    if(count == 0) {
        cout << "Menu is empty!\n";
        return;
    }

    cout << "\n--- Menu Items ---\n";
    for(int i = 0; i < count; i++) {
        cout << "ID: " << menu[i].id
             << ", Name: " << menu[i].name
             << ", Price: " << menu[i].price
             << ", Quantity: " << menu[i].quantity << "\n";
    }
}
void updateItem(Item* menu, int count) {
    int id;
    cout << "Enter Item ID to update: ";
    cin >> id;

    for(int i = 0; i < count; i++) {
        if(menu[i].id == id) {
            cout << "Enter new name, price, quantity: ";
            cin >> menu[i].name >> menu[i].price >> menu[i].quantity;
            cout << "Item updated successfully!\n";
            return;
        }
    }
    cout << "Item not found.\n";
}

void sortMenuByPrice(Item* menu, int count) {
    for(int i = 0; i < count-1; i++) {
        for(int j = 0; j < count-i-1; j++) {
            if(menu[j].price > menu[j+1].price) swap(menu[j], menu[j+1]);
        }
    }
    cout << "Menu sorted by price.\n";
}