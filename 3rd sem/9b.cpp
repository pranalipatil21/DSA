/*PRN: 123B1B221
Name: Pranali Rajendra Patil
Assignment number: 9b
Assignment Title: Implement a checkout system for a supermarket to efficiently manage customer queues during 
peak hours. The system should support the following operations using a circular queue data 
structure: 
a. Customer arrival 
b. Customer checkout 
c. Close Checkout Counter 
d. View customer  */
#include <iostream>
using namespace std;

class Supermarket {
    string name;
    string contact; 
    
public:
    void read() {
        cout << "Enter name of customer: ";
        cin >> name;
        cout << "Enter contact number of customer: ";
        cin >> contact; 
    } 

    void display() const {
        cout << "Name of customer: " << name << endl;
        cout << "Contact details: " << contact << endl; 
    }
};

class SupermarketQueue {
    Supermarket list[500];  // Array of Supermarket objects
    int front, rear;   
    int size;

public:
    SupermarketQueue(int s = 500) {
        size = s;
        front = rear = -1;  
    }

    void arrival();         // Customer Arrival (enqueue)
    void checkout();        // Customer Checkout (dequeue)
    void closeCheckout();   // Close the checkout counter
    void view();            // View customers in queue
};

void SupermarketQueue::arrival() {
    if ((rear + 1) % size == front) {  // Queue is full
        cout << "Supermarket queue is full!" << endl;
    } else {
        if (front == -1) {  // Queue is empty
            front = 0;
        }

        rear = (rear + 1) % size; 
        list[rear].read();  // Read customer details
        
        cout << "Customer added to the supermarket queue!" << endl;
    }
}

void SupermarketQueue::checkout() {
    if (front == -1) {  // Queue is empty
        cout << "Supermarket queue is empty!" << endl;
    } else {
        cout << "Checking out customer: " << endl;
        list[front].display();  // Display customer being checked out
        
        if (front == rear) {  // Only one customer in the queue
            front = rear = -1;  // Reset the queue to empty state
        } else {
            front = (front + 1) % size; 
        }
    }
}

void SupermarketQueue::closeCheckout() {
    if (front == -1) {
        cout << "No customers left in the queue. Checkout counter is closed!" << endl;
    } else {
        cout << "Closing checkout counter..." << endl;
        front = rear = -1;  // Reset the queue
        cout << "All customers have been checked out. Counter closed." << endl;
    }
}

void SupermarketQueue::view() {
    if (front == -1) {  // Queue is empty
        cout << "Supermarket queue is empty!" << endl;
    } else {
        cout << "Customers currently in the queue: " << endl;
        int i = front;
        while (i != rear) {  // Traverse from front to rear
            list[i].display();
            i = (i + 1) % size;  // Circular increment
        }
        list[rear].display();  // Display the last customer (at rear)
    }
}

int main() {
    SupermarketQueue market(5);  // Initialize queue with capacity 5
    int choice;
    
    do {
        cout << "\n--- Supermarket Checkout System ---\n";
        cout << "1. Customer Arrival\n";
        cout << "2. Customer Checkout\n";
        cout << "3. Close Checkout Counter\n";
        cout << "4. View Customers in Queue\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                market.arrival();  
                break;
            case 2:
                market.checkout();  
                break;
            case 3:
                market.closeCheckout();  
                break;
            case 4:
                market.view();  
                break;
            case 5:
                cout << "Exiting the system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);  

    return 0;
}
