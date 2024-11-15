/*PRN: 123B1B221
Name: Pranali Rajendra Patil
Assignment number: 5
Assignment Title: Circular linked list
Implement a navigation system for a delivery service using a circular linked list to represent 
routes. The navigation system should support the following functionalities: 
a. Add route 
b. Remove route 
c. Display route*/

#include <iostream>
using namespace std;

class Navigation {
public:
    string source;
    string destination;
    float distance;
    float time;
    int charges;
    Navigation *next;

    void input() {
        cout << "Enter source: ";
        cin >> source;
        cout << "Enter destination: ";
        cin >> destination;
        cout << "Enter distance (in km): ";
        cin >> distance;
        cout << "Enter time (in hours): ";
        cin >> time;
        cout << "Enter delivery charges: ";
        cin >> charges;
        next = NULL; 
    }

    // Display function to show route details
    void display() {
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Distance: " << distance << " km" << endl;
        cout << "Time: " << time << " hours" << endl;
        cout << "Charges: " << charges << " Rs" << endl;
        cout << "-------------------------" << endl;
    }
};

class Navigationsystem {
    Navigation *head; 

public:
    Navigationsystem() { head = NULL; } 

    // Add route to the circular linked list
    void Add_route() {
        Navigation *nn = new Navigation; // Create a new Navigation node
        nn->input(); // Get route details from user

        if (head == NULL) { // Check if the list is empty
            head = nn; // Set head to the new node
            nn->next = head; // Point to itself to maintain circularity
        } else {
            Navigation *cn = head; // Create a temporary node to traverse the list
            while (cn->next != head) { // Find the last node in the list
                cn = cn->next;
            }
            cn->next = nn; // Link last node to new node
            nn->next = head; // Make it circular by linking new node to head
        }
        cout << "Route added to the system." << endl; 
    }

    // Display all routes in the system
    void display_route() {
        if (head == NULL) { // Check if the list is empty
            cout << "No routes available." << endl; // Inform the user
            return;
        }

        Navigation *cn = head; // Create a temporary node to traverse the list
        do {
            cn->display(); // Display details of the current node
            cn = cn->next; // Move to the next node
        } while (cn != head); // Continue until we reach the head again
    }

    // Delete a route based on the source and destination
    void del_route(string src, string dest) {
        if (head == NULL) { // Check if the list is empty
            cout << "No routes to delete." << endl; // Inform the user
            return;
        }

        Navigation *prev = NULL, *curr = head; // Pointers to keep track of current and previous nodes

        // If the head node needs to be deleted
        if (head->source == src && head->destination == dest) {
            if (head->next == head) { // Only one route in the list
                delete head; // Delete head
                head = NULL; // Set head to NULL
            } else {
                // Find the last node to maintain circular property
                while (curr->next != head) {
                    curr = curr->next; // Move to the last node
                }
                curr->next = head->next; // Bypass the head
                delete head; // Delete the head
                head = curr->next; // Update head to the next node
            }
            cout << "Route deleted successfully." << endl; // Confirm deletion
            return;
        }

        // Traverse the list to find the route to be deleted
        curr = head; // Reset current to head
        do {
            prev = curr; // Store previous node
            curr = curr->next; // Move to the next node

            // Check if the current node matches the source and destination
            if (curr->source == src && curr->destination == dest) {
                prev->next = curr->next; // Bypass the current node
                delete curr; // Delete the current node
                cout << "Route deleted successfully." << endl; 
                return;
            }

        } while (curr != head); // Continue until we reach the head again

        cout << "Route not found." << endl; 
    }
};

int main() {
    Navigationsystem system; 
    int choice; 
    string src, dest; 

    do {
        cout << "\nNavigation System Menu:\n";
        cout << "1. Add Route\n";
        cout << "2. Display Routes\n";
        cout << "3. Delete Route\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; 

        switch (choice) {
        case 1:
            system.Add_route(); 
            break;
        case 2:
            system.display_route(); 
            break;
        case 3:
            cout << "Enter source to delete: ";
            cin >> src; 
            cout << "Enter destination to delete: ";
            cin >> dest; 
            system.del_route(src, dest); 
            break;
        case 4:
            cout << "Exiting navigation system." << endl; 
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4); 

    return 0;
}
