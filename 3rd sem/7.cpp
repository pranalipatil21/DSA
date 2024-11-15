/*PRN: 123B1B221
Name: Pranali Rajendra Patil
Assignment number: 7
Assignment Title: Stack using linkedlist
Implement a browser history management system using a stack data structure to track the user's browsing history. 
The system should support the following functionalities: 
a. Add visited page 
b. Navigate back
c. View current page
d. Check if history is empty or not Assume no upper bound on number of pages visited.*/




#include <iostream>
using namespace std;

class Node {
public:
    string siteaddr;
    Node *next; 

    Node() { next = NULL; }
    ~Node() { next = NULL; }
    void readaddr(); 
    void displayaddr(); 
};

void Node::readaddr() {
    cout << "Enter the site address: ";
    cin >> siteaddr;
}

void Node::displayaddr() {
    cout << "Current page: " << siteaddr << endl;
}

class BrowserHistoryStack {
    Node *top;
public:
    BrowserHistoryStack() { top = NULL; }
    ~BrowserHistoryStack() { top = NULL; }
    
    void VisitNewPage(); // Push a new page to the stack
    void NavigateBack(); // Pop the top page from the stack
    void ViewCurrentPage(); //peek View the top page (current page)
    void isHistoryEmpty(); // Check if the history stack is empty
};

// Push operation to visit a new page
void BrowserHistoryStack::VisitNewPage() {
    Node *nn = new Node();
    nn->readaddr();
    if (top == NULL) {
        top = nn;
    } else {
        nn->next = top;
        top = nn;
    }
    cout << "Page added to history." << endl;
}

// Pop operation to go back in history
void BrowserHistoryStack::NavigateBack() {
    if (top != NULL) {
        Node *temp = top;
        cout << "Going back from: ";
        temp->displayaddr();
        top = top->next;
        delete temp;
        if (top != NULL) {
            cout << "Now on: ";
            top->displayaddr();
        } else {
            cout << "No more pages in history." << endl;
        }
    } else {
        cout << "History is empty. No page to go back to." << endl;
    }
}

// Peek operation to view the current page
void BrowserHistoryStack::ViewCurrentPage() {
    if (top != NULL) {
        top->displayaddr();
    } else {
        cout << "No pages in history." << endl;
    }
}

// Check if the history stack is empty
void BrowserHistoryStack::isHistoryEmpty() {
    if (top == NULL) {
        cout << "History is empty." << endl;
    } else {
        cout << "History is not empty." << endl;
    }
}

int main() {
    BrowserHistoryStack browserHistory;
    int choice;

    do {
        cout << "\n=== Browser History Menu ===\n";
        cout << "1. Visit a new page\n";
        cout << "2. Go back\n";
        cout << "3. View current page\n";
        cout << "4. Check if history is empty\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                browserHistory.VisitNewPage();
                break;
            case 2:
                browserHistory.NavigateBack();
                break;
            case 3:
                browserHistory.ViewCurrentPage();
                break;
            case 4:
                browserHistory.isHistoryEmpty();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, try again." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}
