/*PRN: 123B1B221
Name: Pranali Rajendra Patil
Assignment number: 9a
Assignment Title:  Implement a restaurant waitlist system using the queue data structure. Restaurant waitlist 
 provide following facility: 
  a. Add Party to Waitlist 
  b. Seat Party 
  c. Display Waitlist (using linkedlist)*/

#include <iostream>
#include <string>
using namespace std;

class Customer {
public:
    string name;
    string contact; 
    Customer* next;

    // Constructor
    Customer() {
        next = NULL;
    }

    // Method to read customer details
    void read() {
        cout << "Enter name of party: ";
        cin >> name;
        cout << "Enter contact number of party: ";
        cin >> contact; 
    }

    // Method to display customer details (without const)
    void display() {
        cout << "Name of party: " << name << endl;
        cout << "Contact details: " << contact << endl; 
    }
};

class Waitlist {
    Customer* front;
    Customer* rear;

public:
    Waitlist() {
        front = rear = NULL;
    }

    ~Waitlist() {
        while (front != NULL) {
            Customer* temp = front;
            front = front->next;
            delete temp;
        }
    }

    // Method to add a party to the waitlist (enqueue)
    void addParty();

    // Method to seat a party (dequeue)
    void seatParty();

    // Method to display the current waitlist
    void display();
};

void Waitlist::addParty() {
    Customer* nn = new Customer;  // Dynamically allocate a new Customer
    nn->read();  // Read the customer details

    if (front == NULL) {  // If the queue is empty
        front = rear = nn;  // Both front and rear point to the new customer
    } else {
        rear->next = nn;  // Link the new customer to the end of the list
        rear = nn;  // Move rear to point to the new customer
    }
    cout << nn->name << " added to the waitlist!" << endl;
}

// Method to seat a party (remove the first party from the waitlist)
void Waitlist::seatParty() {
    if (front == NULL) {  // If the waitlist is empty
        cout << "Waitlist is empty!" << endl;
    } else {
        Customer* temp = front;
        cout << "Seating the following party: " << endl;
        temp->display();
        front = front->next;  // Move front to the next customer
        delete temp;  // Free the memory of the seated customer

        if (front == NULL) {  // If the waitlist is now empty
            rear = NULL;  // Reset rear to NULL as well
        }
    }
}

// Method to display the current waitlist
void Waitlist::display() {
    if (front == NULL) {  // If the waitlist is empty
        cout << "Waitlist is empty!" << endl;
    } else {
        cout << "Current waitlist:" << endl;
        Customer* current = front;
        int position = 1;
        while (current != NULL) {
            cout << position << ". ";
            current->display();
            current = current->next;
            position++;
        }
    }
}

int main() {
    Waitlist restaurant;  // Create a waitlist for the restaurant
    int choice;

    do {
        cout << "\n--- Restaurant Waitlist System ---\n";
        cout << "1. Add Party to Waitlist\n";
        cout << "2. Seat Party\n";
        cout << "3. Display Waitlist\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                restaurant.addParty();
                break;
            case 2:
                restaurant.seatParty();
                break;
            case 3:
                restaurant.display();
                break;
            case 4:
                cout << "Exiting system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4); 

    return 0;
}
