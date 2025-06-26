#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

struct MenuItem {
    string name;
    double price;
};

struct Customer {
    string name;
    string phone;
    string address;
};

void displayMenu(const vector<MenuItem>& menu) {
    cout << "\n=======================================" << endl;
    cout << "          Welcome to Amna's Kitchen       " << endl;
    cout << "        Your hunger stops here!         " << endl;
    cout << "=======================================\n" << endl;
    cout << "Here's what we offer today:\n" << endl;

    cout << left << setw(5) << "No." << setw(20) << "Item" << "Price ($)" << endl;
    cout << "---------------------------------------" << endl;
    for (size_t i = 0; i < menu.size(); i++) {
        cout << left << setw(5) << i + 1 << setw(20) << menu[i].name << "$" << menu[i].price << endl;
    }
}

void getCustomerDetails(Customer& customer) {
    cout << "\nPlease provide your details:\n";
    cout << "Name: ";
    getline(cin, customer.name);
    cout << "Phone Number: ";
    getline(cin, customer.phone);
    cout << "Delivery Address: ";
    getline(cin, customer.address);
}

void displayOrderSummary(const vector<pair<MenuItem, int>>& order, const Customer& customer) {
    cout << "\n=======================================" << endl;
    cout << "            Order Summary              " << endl;
    cout << "=======================================\n" << endl;
    double total = 0;

    cout << left << setw(20) << "Item" << setw(10) << "Qty" << "Price ($)" << endl;
    cout << "---------------------------------------" << endl;
    for (const auto& item : order) {
        cout << left << setw(20) << item.first.name << setw(10) << item.second << "$" << item.first.price * item.second << endl;
        total += item.first.price * item.second;
    }
    cout << "---------------------------------------" << endl;
    cout << left << setw(30) << "Total" << "$" << total << endl;

    cout << "\nCustomer Details:\n";
    cout << "Name: " << customer.name << endl;
    cout << "Phone: " << customer.phone << endl;
    cout << "Address: " << customer.address << endl;
}

void payment() {
    cout << "\nChoose a payment method:\n";
    cout << "1. Cash on Delivery\n";
    cout << "2. Credit/Debit Card\n";
    cout << "3. Mobile Wallet\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            cout << "You chose Cash on Delivery. Please have the exact amount ready!\n";
            break;
        case 2:
            cout << "You chose Credit/Debit Card. A link will be sent to your phone to complete the payment.\n";
            break;
        case 3:
            cout << "You chose Mobile Wallet. Payment instructions will be sent to your phone.\n";
            break;
        default:
            cout << "Invalid choice. Defaulting to Cash on Delivery.\n";
            break;
    }
}

int main() {
    vector<MenuItem> menu = {
        {"Pizza", 12.0},
        {"Burger", 8.0},
        {"Shawarma", 6.0},
        {"Cold Drinks", 2.0},
        {"Fries", 3.0}
    };

    vector<pair<MenuItem, int>> order;
    Customer customer;
    bool orderPlaced = false;
    bool menuShown = false;

    while (true) {
        cout << "\nHello! What would you like to do?\n";
        cout << "1. View Menu\n";
        cout << "2. Place Order\n";
        cout << "3. View Order Summary\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        int mainChoice;
        cin >> mainChoice;
        cin.ignore();

        switch (mainChoice) {
            case 1:
                displayMenu(menu);
                menuShown = true;
                break;

            case 2: {
                if (!menuShown) {
                    displayMenu(menu);
                    menuShown = true;
                }
                cout << "\nWhat would you like to order? Enter the number (or type 0 to finish): \n";
                while (true) {
                    int choice;
                    cout << "Your choice: ";
                    cin >> choice;

                    if (choice == 0) break;

                    if (choice > 0 && choice <= menu.size()) {
                        int quantity;
                        cout << "Enter quantity: ";
                        cin >> quantity;
                        order.push_back({menu[choice - 1], quantity});
                        orderPlaced = true;
                    } else {
                        cout << "Invalid choice. Please select a valid item.\n";
                    }
                }
                cin.ignore();
                break;
            }

            case 3:
                if (orderPlaced) {
                    getCustomerDetails(customer);
                    displayOrderSummary(order, customer);
                    payment();
                    cout << "\nThank you for ordering from Amna's Kitchen! Your food will be delivered in approximately 30-45 minutes.\n";
                } else {
                    cout << "No order placed yet. Please place an order first.\n";
                }
                break;

            case 4:
                cout << "Thank you for visiting Amna's Kitchen! Have a great day!\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}


