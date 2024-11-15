/*PRN: 123B1B221
Name: Pranali Rajendra Patil
Assignment number: 6
Assignment Title: 
Consider two polynomial expressions of any degree.
Design solution to perform addition of these two polynomials with suitable data structure and display results.*/
#include <iostream>
using namespace std;

class Polynomial;

class Node {
public:
    int coeff, pow;  
    Node *next;      

    Node() { next = NULL; }
    ~Node() { next = NULL; }

    void read();      
    void display();  

    friend class Polynomial;  
    friend void addPolynomial(Polynomial P1, Polynomial P2);  
    friend void mulPolynomial(Polynomial P1, Polynomial P2);
    friend void subPolynomial(Polynomial P1, Polynomial P2);
};

class Polynomial {
    Node *head;  
public:
    Polynomial() { head = NULL; }  
    ~Polynomial() { head = NULL; } 

    void insertNode();
    void displayNode();
    friend void addPolynomial(Polynomial P1, Polynomial P2);
    friend void mulPolynomial(Polynomial P1, Polynomial P2);
    friend void subPolynomial(Polynomial P1, Polynomial P2);
};

void Polynomial::insertNode() {
    Node* temp = new Node();
    temp->read();          

    if (head == NULL) {
        head = temp;
    } else {
        Node* cn = head;
        // Traverse to the end of the list and append the new term
        while (cn->next != NULL) {
            cn = cn->next;
        }
        cn->next = temp;
    }
}
// display method
void Polynomial::displayNode() {
    Node* cn = head;
    // Traverse the linked list and display each term
    while (cn != NULL) {
        cn->display();  
        if (cn->next != NULL) cout << " + ";  
        cn = cn->next;  // Move to the next term
    }
    cout << endl;  
}

// Function to add two polynomials
void addPolynomial(Polynomial P1, Polynomial P2) {
    Node* cn1 = P1.head;  // Current node for the first polynomial
    Node* cn2 = P2.head;  // Current node for the second polynomial
    Polynomial P3;        // Resultant polynomial for sum

    Node* cn3 = NULL;     // Current node for the resultant polynomial

    // Traverse both polynomials and add terms based on their power
    while (cn1 != NULL && cn2 != NULL) {
        Node* nn = new Node();  // New node for the resultant polynomial

        // If it's the first term, set it as head
        if (P3.head == NULL) {
            P3.head = nn;
            cn3 = nn;
        } else {
            cn3->next = nn;  // Link the new term to the resultant polynomial
            cn3 = cn3->next; // Move to the new term
        }

        // Compare powers and assign values accordingly
        if (cn1->pow > cn2->pow) {
            nn->pow = cn1->pow;     // Assign power from P1
            nn->coeff = cn1->coeff; // Assign coefficient from P1
            cn1 = cn1->next;        // Move to the next term in P1
        } else if (cn1->pow < cn2->pow) {
            nn->pow = cn2->pow;     // Assign power from P2
            nn->coeff = cn2->coeff; // Assign coefficient from P2
            cn2 = cn2->next;        // Move to the next term in P2
        } else {
            nn->pow = cn1->pow;     // Assign power from either polynomial (equal)
            nn->coeff = cn1->coeff + cn2->coeff; // Add coefficients
            cn1 = cn1->next;        // Move to the next term in P1
            cn2 = cn2->next;        // Move to the next term in P2
        }
    }

    // Append remaining terms from P1
    while (cn1 != NULL) {
        Node* nn = new Node();
        nn->pow = cn1->pow;
        nn->coeff = cn1->coeff;
        cn1 = cn1->next;

        if (P3.head == NULL) {
            P3.head = nn;  // Set as head if P3 is empty
            cn3 = nn;      // Set current node
        } else {
            cn3->next = nn; // Link the new term
            cn3 = cn3->next; // Move to the new term
        }
    }

    // Append remaining terms from P2
    while (cn2 != NULL) {
        Node* nn = new Node();
        nn->pow = cn2->pow;
        nn->coeff = cn2->coeff;
        cn2 = cn2->next;

        if (P3.head == NULL) {
            P3.head = nn; // Set as head if P3 is empty
            cn3 = nn;     // Set current node
        } else {
            cn3->next = nn; // Link the new term
            cn3 = cn3->next; // Move to the new term
        }
    }

    cout << "Sum: "; // Display the result
    P3.displayNode(); // Show the resultant polynomial
}

// Helper function to add nodes for multiplication result
Node* addNode(Node* head, int coeff, int pow) {
    Node* temp = new Node(); // Create a new node
    temp->coeff = coeff;     // Set coefficient
    temp->pow = pow;         // Set power
    temp->next = NULL;

    // If head is NULL, set the new node as head
    if (head == NULL) {
        return temp;
    }

    Node* current = head;   // Current node for traversal
    Node* prev = NULL;      // Previous node for linking
    
    // Traverse to find the correct position based on power
    while (current != NULL && current->pow > pow) {
        prev = current;      // Keep track of previous node
        current = current->next; // Move to the next node
    }

    // If the same power exists, add the coefficients
    if (current != NULL && current->pow == pow) {
        current->coeff += coeff;
        delete temp;  // Delete temporary node
    } else {
        // Insert the new node in the correct position
        if (prev == NULL) {
            temp->next = head; // Insert at the beginning
            head = temp;
        } else {
            prev->next = temp; // Insert between nodes
            temp->next = current;
        }
    }

    return head; // Return the updated head of the list
}

// Function to multiply two polynomials
void mulPolynomial(Polynomial P1, Polynomial P2) {
    Node* ptr1 = P1.head;
    Node* ptr2 = P2.head;
    Polynomial P3;
    
    // Traverse each term in the first polynomial
    while (ptr1 != NULL) {
        // Traverse each term in the second polynomial
        while (ptr2 != NULL) {
            int coeff = ptr1->coeff * ptr2->coeff; // Multiply coefficients
            int pow = ptr1->pow + ptr2->pow;       // Add powers
            
            P3.head = addNode(P3.head, coeff, pow); // Add product to resultant polynomial
            ptr2 = ptr2->next; // Move to the next term in P2
        }
        ptr2 = P2.head; // Reset ptr2 for next term in P1
        ptr1 = ptr1->next; // Move to the next term in P1
    }

    cout << "Product: ";
    P3.displayNode(); 
}

// Function to subtract two polynomials
void subPolynomial(Polynomial P1, Polynomial P2) {
    Node* cn1 = P1.head;
    Node* cn2 = P2.head;
    Polynomial P3;       // Resultant polynomial for difference

    Node* cn3 = NULL;    // Current node for the resultant polynomial

    // Traverse both polynomials and subtract terms based on their power
    while (cn1 != NULL && cn2 != NULL) {
        Node* nn = new Node(); // New node for the resultant polynomial
        
        // If it's the first term, set it as head
        if (P3.head == NULL) {
            P3.head = nn;
            cn3 = nn;
        } else {
            cn3->next = nn; // Link the new term
            cn3 = cn3->next; // Move to the new term
        }

        // Compare powers and assign values accordingly
        if (cn1->pow > cn2->pow) {
            nn->pow = cn1->pow;     // Assign power from P1
            nn->coeff = cn1->coeff; // Assign coefficient from P1
            cn1 = cn1->next;        // Move to the next term in P1
        } else if (cn1->pow < cn2->pow) {
            nn->pow = cn2->pow;     // Assign power from P2
            nn->coeff = -cn2->coeff; // Subtract coefficient from P2
            cn2 = cn2->next;        // Move to the next term in P2
        } else {
            nn->pow = cn1->pow;     // Assign power from either polynomial (equal)
            nn->coeff = cn1->coeff - cn2->coeff; // Subtract coefficients
            cn1 = cn1->next;        // Move to the next term in P1
            cn2 = cn2->next;        // Move to the next term in P2
        }
    }

    // Append remaining terms from P1
    while (cn1 != NULL) {
        Node* nn = new Node();
        nn->pow = cn1->pow;
        nn->coeff = cn1->coeff;
        cn1 = cn1->next;

        if (P3.head == NULL) {
            P3.head = nn;  // Set as head if P3 is empty
            cn3 = nn;      // Set current node
        } else {
            cn3->next = nn; // Link the new term
            cn3 = cn3->next; // Move to the new term
        }
    }

    // Append remaining terms from P2 (with negated coefficients)
    while (cn2 != NULL) {
        Node* nn = new Node();
        nn->pow = cn2->pow;
        nn->coeff = -cn2->coeff; // Negate coefficient for subtraction
        cn2 = cn2->next;

        if (P3.head == NULL) {
            P3.head = nn; // Set as head if P3 is empty
            cn3 = nn;     // Set current node
        } else {
            cn3->next = nn; // Link the new term
            cn3 = cn3->next; // Move to the new term
        }
    }

    cout << "Difference: "; 
    P3.displayNode(); 
}

// Function to read polynomial term details from user
void Node::read() {
    cout << "Enter coefficient: ";
    cin >> coeff; 
    cout << "Enter power: ";
    cin >> pow;   
}

void Node::display() {
    cout << coeff << "x^" << pow; // Display in 'coefficient x^power' format
}

int main() {
    Polynomial P1, P2;
    int choice;
    do {
        cout << "\nPolynomial Operations Menu:\n";
        cout << "1. Insert Polynomial 1\n";
        cout << "2. Insert Polynomial 2\n";
        cout << "3. Display Polynomial 1\n";
        cout << "4. Display Polynomial 2\n";
        cout << "5. Add Polynomials\n";
        cout << "6. Subtract Polynomials\n";
        cout << "7. Multiply Polynomials\n";
        cout << "8. Exit\n";
        cout << "Choose an option: ";
        cin >> choice; 

        switch (choice) {
            case 1:
                P1.insertNode();
                break;
            case 2:
                P2.insertNode();
                break;
            case 3:
                cout << "Polynomial 1: ";
                P1.displayNode();
                break;
            case 4:
                cout << "Polynomial 2: ";
                P2.displayNode();
                break;
            case 5:
                addPolynomial(P1, P2); 
                break;
            case 6:
                subPolynomial(P1, P2); 
                break;
            case 7:
                mulPolynomial(P1, P2);
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);
    return 0;
}
