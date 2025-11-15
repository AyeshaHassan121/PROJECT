#include<iostream>
#include<fstream>
#include<string>

using namespace std;

struct Item{
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
void orderItem(Item* menu, int menuCount, Item* &cart, int &cartCount);
void displayCart(Item* cart, int cartCount);
void cancelOrder(Item* &cart, int &cartCount);
void updateCart(Item* cart, int cartCount);
void calculateTotal(Item* cart, int cartCount);



int main(){
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
        cout << "9. Cancel Order\n10. Update Cart\n11. Calculate Total\n";
        cin >> choice;

        switch(choice) {
            case 1: 
            addItem(menu, menuCount); break;
            case 2: 
            displayMenu(menu, menuCount); break;
            case 3: 
            updateItem(menu, menuCount); break;
            case 4: 
            removeItem(menu, menuCount); break;
            case 5: 
            searchItem(menu, menuCount); break;
            case 6: 
            orderItem(menu, menuCount, cart, cartCount); break;
            case 7: 
            displayCart(cart, cartCount); break;
            case 8: 
            cancelOrder(cart, cartCount); break;
            case 9: 
            updateCart(cart, cartCount); break;
            case 10: 
            calculateTotal(cart, cartCount); break;
            default: 
            cout << "Invalid choice!\n";
        }
    }  while(choice >= 1 && choice <= 11);


    delete [] menu;
    delete [] cart;
}


