#include<iostream>
#include<string>
using namespace std;

struct Item {
    int id;
    string name;
    float price;
    int quantity;
};
void mainMenu();
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
            case 0: cout << "Exiting!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 0);

    delete[] menu;
    delete[] cart;
}
void addItem(Item* &menu, int &count) {
    Item* temp = new Item[count + 1];
    for(int i = 0; i < count; i++) 
    temp[i] = menu[i];
    delete [] menu;
    menu = temp;

    cout << "Enter item ID: "; 
    cin >> menu[count].id; 
    cin.ignore();
    cout << "Enter item name: "; 
    getline(cin, menu[count].name);
    cout << "Enter price: "; 
    cin >> menu[count].price;
    cout << "Enter quantity: "; 
    cin >> menu[count].quantity;
    count++;
    cout << "Item added to menu successfully.\n";
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
void removeItem(Item* &menu, int &count) {
    int id; 
    cout << "Enter item ID to remove: "; 
    cin >> id;
    int index = -1;
    for(int i = 0; i < count; i++) 
    if(menu[i].id == id) 
    index = i;
    if(index == -1) { 
        cout << "Item not found.\n"; 
        return; }
    Item* temp = new Item[count - 1];
    for(int i = 0, j = 0; i < count; i++) 
    if(i != index) 
    temp[j++] = menu[i];
    delete [] menu;
    menu = temp;
    count--;
    cout << "Item removed from menu.\n";
}
void searchItem(Item* menu, int count) {
    string name; 
    cout << "Enter item name to search: "; 
    cin.ignore(); 
    getline(cin, name);
    for(int i = 0; i < count; i++) {
        if(menu[i].name == name) {
            cout << "Found: ID=" << menu[i].id << ", Price=" << menu[i].price << ", Quantity=" << menu[i].quantity << "\n";
            return;
        }
    }
    cout << "Item not found.\n";
}

void sortMenuByPrice(Item* menu, int count) {
    for(int i = 0; i < count-1; i++) {
        for(int j = 0; j < count-i-1; j++) {
            if(menu[j].price > menu[j+1].price) 
            swap(menu[j], menu[j+1]);
        }
    }
    cout << "Menu sorted by price.\n";
}
void orderItem(Item* menu, int menuCount, Item* &cart, int &cartCount) {
    int id, qty; 
    cout << "Enter item ID to order: "; 
    cin >> id;
    cout << "Enter quantity: "; 
    cin >> qty;
    for(int i = 0; i < menuCount; i++) {
        if(menu[i].id == id) {
            if(qty > menu[i].quantity) { 
                cout << "Not enough stock.\n"; 
                return; }
            Item* temp = new Item[cartCount + 1];
            for(int j = 0; j < cartCount; j++) 
            temp[j] = cart[j];
            delete [] cart; 
            cart = temp;
            cart[cartCount] = menu[i];
            cart[cartCount].quantity = qty;
            cartCount++;
            menu[i].quantity -= qty;
            cout << "Item added to cart.\n"; 
            return;
        }
    }
    cout << "Item not found.\n";
}