/*PRN: 123B1B221
Name: Pranali Rajendra Patil
Assignment number: 11
Assignment Title: Consider an employee database of N employees.
 Make use of a hash table implementation to quickly look up the employer's id number.*/
#include<iostream>
using namespace std;

#define size 10

class Employee {
    int empID;
    string name;
    long salary;

public:
    Employee() {
        empID=-1;
        name=" ";
        salary=0;
    }

    void read() {
        cout << "Enter employee ID: ";
        cin >> empID;
        cout << "Enter employee name: ";
        cin >> name;
        cout << "Enter employee salary: ";
        cin >> salary;
    }

    void display() {
        if (empID != -1) {
            cout << empID << "\t" << name << "\t" << salary << endl;
        } else {
            cout << "-\t-\t-" << endl;  // For empty slots
        }
    }

    int getID() {
        return empID;
    }

    void clear() {
        empID = -1;
        name = "";
        salary = 0;
    }
};

class Hashtable {
    Employee e[size];
    int flag[size];  // flag array to indicate the status: 0 = empty/deleted, 1 = occupied

public:
    Hashtable() {
        for (int i = 0; i < size; i++) {
            flag[i] = 0;  // Initialize all slots as empty
        }
    }

    void insertID();
    void deleteID();
    void displayTable();
    int hashFunction(int empID);  // Hash function: empID % size
};

// Hash function to map empID to an index
int Hashtable::hashFunction(int empID) {
    return empID % size;
}

// Function to insert employee into the hash table
void Hashtable::insertID() {
    Employee newEmp;
    newEmp.read();
    int empID = newEmp.getID();
    int pos = hashFunction(empID);  // Get the hash index

    // Linear probing for collision resolution
    for (int i = 0; i < size; i++) {
        pos = (pos + i) % size;  // Update pos in case of collision
        if (flag[pos] == 0) {  // Slot is empty or deleted
            e[pos] = newEmp;
            flag[pos] = 1;  // Mark the slot as occupied
            cout << "Employee inserted at position: " << pos << endl;
            return;
        }
    }

    cout << "Hash table is full! Unable to insert employee." << endl;
}

// Function to delete an employee from the hash table by ID
void Hashtable::deleteID() {
    int id;
    cout << "Enter the employee ID to delete: ";
    cin >> id;
    int pos = hashFunction(id);

    for (int i = 0; i < size; i++) {
        pos = (pos + i) % size;
        if (flag[pos] == 1 && e[pos].getID() == id) {
            e[pos].clear();
            flag[pos] = 0;  // Mark the slot as empty
            cout << "Employee with ID " << id << " deleted from position: " << pos << endl;
            return;
        }
    }

    cout << "Employee ID not found!" << endl;
}

// Function to display all employees in the hash table
void Hashtable::displayTable() {
    cout << "Position\tID\tName\tSalary" << endl;
    for (int i = 0; i < size; i++) {
        cout << i << "\t\t";
        if (flag[i] == 1) {  // Slot is occupied
            e[i].display();
        } else {
            cout << "-\t-\t-" << endl;  // Display '-' for empty slots
        }
    }
}

int main() {
    Hashtable ht;
    int choice;

    while(1) {
        cout << "\nEmployee Database Menu:\n";
        cout << "1. Insert employee\n";
        cout << "2. Delete employee\n";
        cout << "3. Display all employees\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                ht.insertID();
                break;
            case 2:
                ht.deleteID();
                break;
            case 3:
                ht.displayTable();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                exit(0);
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
                break;
        }
    }

    return 0;
}
