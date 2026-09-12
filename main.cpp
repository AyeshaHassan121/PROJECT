#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
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
void checkout(Item* &cart, int &cartCount);
void saveMenuToText(Item* menu, int count);
void loadMenuFromText(Item* &menu, int &count);
void saveMenuToBinary(Item* menu, int count);
void loadMenuFromBinary(Item* &menu, int &count);
void saveCartToText(Item* cart, int cartCount);
void loadCartFromText(Item* &cart, int &cartCount);


int main() {
    mainMenu();
    return 0;
}
void mainMenu() {
    Item* menu = nullptr;
    Item* cart = nullptr;
    int menuCount = 0, cartCount = 0;
    int choice;

    loadMenuFromText(menu, menuCount);
    loadCartFromText(cart, cartCount);


    

    do {
        cout << "\n=== Online Food Ordering System ===\n";
        cout << "1. Add Menu Item\n2. Display Menu\n3. Update Menu Item\n4. Remove Menu Item\n";
        cout << "5. Search Item\n6. Sort Menu by Price\n7. Order Item\n8. Display Cart\n";
        cout << "9. Cancel Order\n10. Update Cart\n11. Calculate Total\n12. Checkout\n";
        cout << "13. Save Menu to Text File\n14. Load Menu from Text File\n15. Save Menu to Binary\n16. Load Menu from Binary\n";
        cout << "17. Save Cart\n18. Load Cart\n0. Exit.\nEnter your choice: ";
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
            case 12: checkout(cart, cartCount); break;
            case 13: saveMenuToText(menu, menuCount); break;
            case 14: loadMenuFromText(menu, menuCount); break;
            case 15: saveMenuToBinary(menu, menuCount); break;
            case 16: loadMenuFromBinary(menu, menuCount); break;
            case 17: saveCartToText(cart, cartCount); break;
            case 18: loadCartFromText(cart, cartCount); break;

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
           cin.ignore(); 
            cout << "Enter new name: ";
            getline(cin, menu[i].name); 
            cout << "Enter new price and quantity: ";
            cin >> menu[i].price >> menu[i].quantity;
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
    for(int i = 0; i < count; i++) {
    if(menu[i].id == id) {
    index = i;
    break;
    }
}
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
    cin.ignore(); 
    string name;
    cout << "Enter item name to search: ";
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
    if(count == 0) {
        cout << "Menu is empty!\n";
        return;
    }
     for(int i = 0; i < count-1; i++) {
        for(int j = 0; j < count-i-1; j++) {
            if(menu[j].price > menu[j+1].price) {
                swap(menu[j], menu[j+1]);
            }
        }
    }
    
    cout << "Menu sorted by price.\n";
    displayMenu(menu, count);  
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
void displayCart(Item* cart, int cartCount) {
    if(cartCount == 0) {
        cout << "Cart is empty.\n";
        return;
    }

    cout << "\n--- Cart Items ---\n";
    cout << "ID\tName\t\tPrice\tQuantity\n";
    for(int i = 0; i < cartCount; i++) {
        cout << cart[i].id << "\t" << cart[i].name << "\t\t"
             << cart[i].price << "\t" << cart[i].quantity << "\n";
    }
}
void cancelOrder(Item* &cart, int &cartCount) {
    int id;
    cout << "Enter item ID to remove from cart: ";
    cin >> id;

    int index = -1;
    for(int i = 0; i < cartCount; i++) {
        if(cart[i].id == id) {
        index = i;
        break;
        }
    }

    if(index == -1) {
        cout << "Item not in cart.\n";
        return;
    }

    Item* temp = new Item[cartCount - 1];
    for(int i = 0, j = 0; i < cartCount; i++) {
        if(i != index) 
        temp[j++] = cart[i];
    }
    delete[] cart;
    cart = temp;
    cartCount--;
    cout << "Item removed from cart.\n";
}
void updateCart(Item* cart, int cartCount) {
    int id;
    cout << "Enter item ID to update quantity: ";
    cin >> id;

    for(int i = 0; i < cartCount; i++) {
        if(cart[i].id == id) {
            cout << "Enter new quantity: ";
            cin >> cart[i].quantity;
            cout << "Cart updated.\n";
            return;
        }
    }

    cout << "Item not found in cart.\n";
}
void calculateTotal(Item* cart, int cartCount) {
    float total = 0;
    for(int i = 0; i < cartCount; i++)
        total += cart[i].price * cart[i].quantity;

    cout << "Total amount: " << total << "\n";
}
void checkout(Item* &cart, int &cartCount) {
    calculateTotal(cart, cartCount);
    delete [] cart;
    cart = nullptr;
    cartCount = 0;
    cout << "Checkout complete. Cart cleared.\n";
}
void saveMenuToText(Item* menu, int count) {
    if (count == 0) {
        cout << "No items to save.\n";
        return; 
    }
    ofstream out("menu.txt");
    for(int i = 0; i < count; i++)
        out << menu[i].id << " " << menu[i].price << " " << menu[i].quantity << " " << menu[i].name << "\n";
    out.close();
    cout << "Menu saved to menu.txt\n";
}
void loadMenuFromText(Item* &menu, int &count) {
    ifstream in("menu.txt");
    if (!in) {
        cout << "menu.txt not found.\n";
        return;
    }

    Item* temp = nullptr;
    int itemCount = 0;
    int id, quantity;
    float price;
    string name;

    while (in >> id >> price >> quantity) {
        in.ignore(); 
        getline(in, name); 

        Item item;
        item.id = id;
        item.price = price;
        item.quantity = quantity;
        item.name = name;

        Item* newMenu = new Item[itemCount + 1];
        for (int i = 0; i < itemCount; i++) newMenu[i] = temp[i];
        delete[] temp;
        temp = newMenu;

        temp[itemCount] = item;
        itemCount++;
    }

    delete[] menu;
    menu = temp;
    count = itemCount;
    in.close();

    cout << "Menu loaded from menu.txt (" << count << " items).\n";
}

void saveMenuToBinary(Item* menu, int count) {
    ofstream out("menu.dat", ios::binary);
    if (!out) {
        cout << "Failed to open menu.dat for writing.\n";
        return;
    }

    out.write((char*)&count, sizeof(int)); 

    for (int i = 0; i < count; i++) {
        out.write((char*)&menu[i].id, sizeof(int));
        out.write((char*)&menu[i].price, sizeof(float));
        out.write((char*)&menu[i].quantity, sizeof(int));

        int nameLen = menu[i].name.size();
        out.write((char*)&nameLen, sizeof(int));  
        for (int j = 0; j < nameLen; j++) {
            char ch = menu[i].name[j];
            out.write(&ch, sizeof(char));  
        }
    }

    out.close();
    cout << "Menu saved to menu.dat\n";
}

void loadMenuFromBinary(Item* &menu, int &count) {
    ifstream in("menu.dat", ios::binary);
    if (!in) {
        cout << "menu.dat not found.\n";
        menu = nullptr;
        count = 0;
        return;
    }

    in.read((char*)&count, sizeof(int));
    if (count <= 0) {
        cout << "Binary file empty or corrupted.\n";
        menu = nullptr;
        count = 0;
        in.close();
        return;
    }

    delete[] menu;
    menu = new Item[count];

    for (int i = 0; i < count; i++) {
        in.read((char*)&menu[i].id, sizeof(int));
        in.read((char*)&menu[i].price, sizeof(float));
        in.read((char*)&menu[i].quantity, sizeof(int));

        int nameLen;
        in.read((char*)&nameLen, sizeof(int));

        menu[i].name.resize(nameLen);  
        for (int j = 0; j < nameLen; j++) {
            char ch;
            in.read(&ch, sizeof(char));
            menu[i].name[j] = ch;     
        }
    }

    in.close();
    cout << "Menu loaded from menu.dat (" << count << " items).\n";
}

void saveCartToText(Item* cart, int cartCount) { 
    ofstream out("cart.txt"); 
    for(int i = 0; i < cartCount; i++) 
        out << cart[i].id << " " << cart[i].price << " " << cart[i].quantity << " " << cart[i].name << "\n"; 
    out.close(); 
    cout << "Cart saved to cart.txt\n";
}
void loadCartFromText(Item* &cart, int &cartCount) {
    ifstream in("cart.txt");
    if (!in) {
        cout << "cart.txt not found.\n";
        return;
    }

    Item* temp = nullptr;
    int count = 0;
    int id, quantity;
    float price;
    string name;

    while (in >> id >> price >> quantity) {
        in.ignore(); 
        getline(in, name); 

        Item item;
        item.id = id;
        item.price = price;
        item.quantity = quantity;
        item.name = name;

        Item* newCart = new Item[count + 1];
        for (int i = 0; i < count; i++) newCart[i] = temp[i];
        delete[] temp;
        temp = newCart;

        temp[count] = item;
        count++;
    }

    delete[] cart;
    cart = temp;
    cartCount = count;
    in.close();

    cout << "Cart loaded from cart.txt (" << cartCount << " items).\n";
}