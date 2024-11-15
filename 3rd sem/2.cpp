/*
PRN: 123B1B221
Name: Pranali Rajendra Patil
Assignment number: 2
Assignment Title: Sorting Techniques on employee database
Consider Employee database of PCCOE (at least 20 records). Database contains different fields of 
every employee like EMP-ID, EMP-Name and EMP-Salary.  
a. Arrange list of employees according to EMP-ID in ascending order using Quick Sort 
b. Arrange list of Employee alphabetically using Merge Sort */
#include <iostream>
#include <string>
using namespace std;

const int MAX_EMPLOYEES = 100; // Adjust based on expected maximum number of employees

class Employee
{
public:
    int empID;
    string empName;
    float empSalary;

    void getData();
    void showData();
    friend void mergeSort(Employee arr[], int start, int end);
    friend void quickSort(Employee arr[], int low, int high);
};

// Function to input employee data
void Employee::getData()
{
    cout << "Enter the ID of the employee: ";
    cin >> empID;
    cout << "Enter the name of the employee: ";
    cin.ignore(); // Clear the newline character left in the input buffer
    getline(cin, empName);
    cout << "Enter the salary of the employee: ";
    cin >> empSalary;
    cout << "---------------------------------" << endl;
}

// Function to display employee data
void Employee::showData()
{
    cout << "Employee ID: " << empID << endl
         << "Employee Name: " << empName << endl
         << "Employee Salary: " << empSalary << endl
         << "---------------------------------" << endl;
}

// Merge Sort
void merge(Employee arr[], int start, int mid, int end)
{
    Employee tempArr[MAX_EMPLOYEES]; // Temporary array for merging

    int left = start, right = mid + 1;
    int index = 0;

    while (left <= mid && right <= end)
    {
        if (arr[left].empName < arr[right].empName)
        {
            tempArr[index] = arr[left];
            left++;
        }
        else
        {
            tempArr[index] = arr[right];
            right++;
        }
        index++;
    }

    while (left <= mid)
    {
        tempArr[index] = arr[left];
        left++;
        index++;
    }

    while (right <= end)
    {
        tempArr[index] = arr[right];
        right++;
        index++;
    }

    for (left = start, index = 0; left <= end; left++, index++)
    {
        arr[left] = tempArr[index];
    }
}

void mergeSort(Employee arr[], int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

// Quick Sort
int partition(Employee arr[], int low, int high)
{
    int pivot = arr[high].empID; // Pivot based on employee ID
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j].empID < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(Employee arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    Employee empArr[20];
    int empCount;
    int choice;

    cout << "Enter the number of employees (max 20): ";
    cin >> empCount;
    if (empCount > 20)
    {
        cout << "Error: Number of employees exceeds the limit of 20. Exiting..." << endl;
        return -1;  // Error code -1 if employee count exceeds limit
    }

    for (int i = 0; i < empCount; i++)
    {
        empArr[i].getData();
    }

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Sort by Employee ID (Quick Sort)\n";
        cout << "2. Sort by Employee Name (Merge Sort)\n";
        cout << "3. Display Employee Records\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                quickSort(empArr, 0, empCount - 1);
                cout << "\nEmployees sorted by ID:\n";
                for (int i = 0; i < empCount; i++)
                {
                    empArr[i].showData();
                }
                break;

            case 2:
                mergeSort(empArr, 0, empCount - 1);
                cout << "\nEmployees sorted alphabetically by Name:\n";
                for (int i = 0; i < empCount; i++)
                {
                    empArr[i].showData();
                }
                break;

            case 3:
                cout << "\nEmployee Records:\n";
                for (int i = 0; i < empCount; i++)
                {
                    empArr[i].showData();
                }
                break;

            case 4:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Error: Invalid choice! Please try again.\n";
                break;
        }

    } while (choice != 4);

    return 0;
}
