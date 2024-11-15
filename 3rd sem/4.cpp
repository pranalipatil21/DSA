/*PRN: 123B1B221
Name: Pranali Rajendra Patil
Assignment number: 4
Assignment Title: Doubly linked list
Implement a simple text editor application using a doubly linked list to manage the text buffer. 
Text editor should support the following functionalities:  
a. Insert text 
b. Delete text 
c. Display text 
d. Search text 
e. Print text in reverse  */
#include <iostream>
using namespace std;

class Node {
public:
    string text;  
    Node *next, *prev;  

    Node() {
        text = "";
        next = NULL;
        prev = NULL;
    }
};

class TextEditor {
    Node *start;  

public:
    TextEditor() {
        start = NULL; 
    }

    // Method to create text by inserting nodes at the end
    void create() {
        Node *newNode;
        Node *currentNode;
        char choice;

        do {
            newNode = new Node;  
            cout << "Enter the text to be stored: ";
            cin >> newNode->text;

            // If the list is empty, set start to the new node
            if (start == NULL) {
                start = newNode;
            } else {
                currentNode = start;

                // Traverse to the end of the list
                while (currentNode->next != NULL) {
                    currentNode = currentNode->next;
                }
                currentNode->next = newNode;  // Link the new node at the end
                newNode->prev = currentNode;   // Set previous pointer
            }

            cout << "Do you have more data? (y/n): ";
            cin >> choice;  
        } while (choice == 'y');  
    }

    // Method to display the stored text
    void display() {
        Node *currentNode;
        cout << "\nStored text: ";
        
        // Traverse and print each node's text
        for (currentNode = start; currentNode != NULL; currentNode = currentNode->next) {
            cout << currentNode->text << "\t";
        }
        cout << endl;
    }

    // Method to display the text in reverse order
    void display_reverse() {
        Node *currentNode = start;

        // Check if the list is empty
        if (start == NULL) {
            cout << "List is empty!" << endl;
            return;
        }

        // Move to the last node
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }

        cout << "\nReversed text: ";
        
        // Traverse backward and print each node's text
        for (; currentNode != NULL; currentNode = currentNode->prev) {
            cout << currentNode->text << "\t";
        }
        cout << endl;
    }

    // Method to insert text at the beginning of the list
    void insert_begin() {
        Node *newNode = new Node;
        cout << "\nEnter the text to be inserted at the beginning: ";
        cin >> newNode->text;

        // Link the new node to the start
        newNode->next = start;
        if (start != NULL) {
            start->prev = newNode;  // Update the previous pointer of the old start
        }
        start = newNode;  // Update start to the new node

        // Display updated list
        display();
        display_reverse();
    }

    // Method to insert text between existing nodes
    void insert_between() {
        Node *newNode = new Node;
        Node *currentNode;
        string afterText;
        cout << "\nEnter the text to be inserted: ";
        cin >> newNode->text;
        cout << "Enter the text after which you want to insert: ";
        cin >> afterText;

        // Traverse the list to find the node after which to insert
        for (currentNode = start; currentNode != NULL; currentNode = currentNode->next) {
            if (currentNode->text == afterText) {
                // Link the new node in between
                newNode->next = currentNode->next;
                newNode->prev = currentNode;
                if (currentNode->next != NULL) {
                    currentNode->next->prev = newNode;  // Update next node's previous pointer
                }
                currentNode->next = newNode;  // Link current node to the new node
                break;
            }
        }

        if (currentNode == NULL) {
            cout << "Text not found!" << endl;  // Handle case where the text is not found
        }

        // Display updated list
        display();
        display_reverse();
    }

    // Method to insert text at the end of the list
    void insert_end() {
        Node *newNode = new Node;
        Node *currentNode = start;

        cout << "\nEnter the text to be inserted at the end: ";
        cin >> newNode->text;

        // If the list is empty, set start to the new node
        if (start == NULL) {
            start = newNode;
        } else {
            // Traverse to the end of the list
            while (currentNode->next != NULL) {
                currentNode = currentNode->next;
            }
            currentNode->next = newNode;  // Link the new node at the end
            newNode->prev = currentNode;   // Set previous pointer
        }

        // Display updated list
        display();
        display_reverse();
    }

    // Method to delete the first node in the list
    void delete_begin() {
        if (start == NULL) {
            cout << "List is empty!" << endl;
            return;
        }
        Node *temp = start;  // Temporary pointer to the start node
        start = start->next;  // Move start to the next node
        if (start != NULL) {
            start->prev = NULL;  // Update the previous pointer of the new start
        }
        delete temp;  // Free memory

        // Display updated list
        display();
        display_reverse();
    }

    // Method to delete a specified text from the list
    void delete_between() {
        string textToDelete;
        Node *currentNode;

        cout << "Enter the text you want to delete: ";
        cin >> textToDelete;

        // Traverse the list to find the node with the specified text
        for (currentNode = start; currentNode != NULL; currentNode = currentNode->next) {
            if (currentNode->text == textToDelete) {
                // Link surrounding nodes to remove current node
                if (currentNode->prev != NULL) {
                    currentNode->prev->next = currentNode->next;  // Update previous node's next pointer
                } else {
                    start = currentNode->next;  // Update start if deleting the first node
                }
                if (currentNode->next != NULL) {
                    currentNode->next->prev = currentNode->prev;  // Update next node's previous pointer
                }
                delete currentNode;  // Free memory
                break;
            }
        }

        if (currentNode == NULL) {
            cout << "Text not found!" << endl;  // Handle case where the text is not found
        }

        // Display updated list
        display();
        display_reverse();
    }

    // Method to delete the last node in the list
    void delete_end() {
        if (start == NULL) {
            cout << "List is empty!" << endl;
            return;
        }

        Node *currentNode = start;
        // Traverse to the last node
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }

        // Update the previous node's next pointer to NULL
        if (currentNode->prev != NULL) {
            currentNode->prev->next = NULL;
        } else {
            start = NULL;  // If the list had only one node, set start to NULL
        }

        delete currentNode;  // Free memory

        display();
        display_reverse();
    }

    // Method to search for text in the list
    void search_text() {
        string textToSearch;
        Node *currentNode;

        cout << "Enter the text you want to search: ";
        cin >> textToSearch;

        // Traverse the list to find the specified text
        for (currentNode = start; currentNode != NULL; currentNode = currentNode->next) {
            if (currentNode->text == textToSearch) {
                cout << "Text found: " << currentNode->text << endl;  // Print found text
                return;  // Exit after finding the text
            }
        }

        cout << "Text not found!" << endl;  // If not found
    }
};

int main() {
    TextEditor e;
    int choice;

    do {
        cout << "\nMenu:\n1. Create Text\n2. Display Text\n3. Display Reversed Text\n4. Insert at Beginning\n5. Insert Between\n6. Insert at End\n7. Delete from Beginning\n8. Delete Between\n9. Delete from End\n10. Search Text\n11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                e.create();
                break;
            case 2: 
                e.display();
                break;
            case 3: 
                e.display_reverse();
                break;
            case 4: 
                e.insert_begin();
                break;
            case 5: 
                e.insert_between();
                break;
            case 6: 
                e.insert_end();
                break;
            case 7: 
                e.delete_begin();
                break;
            case 8: 
                e.delete_between();
                break;
            case 9: 
                e.delete_end();
                break;
            case 10: 
                e.search_text();
                break;
            case 11: 
                cout << "Exiting program." << endl;
                break;
            default: 
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 11);

    return 0;
}
