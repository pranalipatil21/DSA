#include<iostream>
using namespace std;

class Student {
    int roll;
    string name;
    float sgpa;

public:
    void read() {
        cout << "Enter the name: ";
        cin >> name;
        cout << "Enter the roll number: ";
        cin >> roll;
        cout << "Enter the SGPA: ";
        cin >> sgpa;
    }

    void write() {
        cout << "NAME: " << name << "\n";
        cout << "ROLL NUMBER: " << roll << "\n";
        cout << "SGPA: " << sgpa << "\n\n";
    }

    int getRoll() {
        return roll;
    }

    string getName() {
        return name;
    }

    float getSGPA() {
        return sgpa;
    }

    void setRoll(int r) {
        roll = r;
    }

    void setName(string n) {
        name = n;
    }

    void setSGPA(float s) {
        sgpa = s;
    }
};

class StudentRecords {
    Student students[15]; // array of 15 student records
    int n;

public:
    void read() {
        cout << "Enter the number of students: ";
        cin >> n;

        for(int i = 0; i < n; i++) {
            cout << "Enter details of student " << i + 1 << ":\n";
            students[i].read();
        }
    }

    void write() {
        for(int i = 0; i < n; i++) {
            students[i].write();
        }
    }

    // (a) Insertion Sort based on roll numbers
    void insertionSort() {
        for(int i = 1; i < n; i++) {
            Student key = students[i];
            int j = i - 1;
            while(j >= 0 && students[j].getRoll() > key.getRoll()) {
                students[j + 1] = students[j];
                j--;
            }
            students[j + 1] = key;
        }
    }

    // (b) Shell Sort based on names
    void shellSort() {
        for(int gap = n / 2; gap > 0; gap /= 2) {
            for(int i = gap; i < n; i++) {
                Student temp = students[i];
                int j;
                for(j = i; j >= gap && students[j - gap].getName() > temp.getName(); j -= gap) {
                    students[j] = students[j - gap];
                }
                students[j] = temp;
            }
        }
    }

    // (c) Radix Sort based on SGPA
    void radixSort() {
        float maxSGPA = students[0].getSGPA();
        for(int i = 1; i < n; i++) {
            if(students[i].getSGPA() > maxSGPA) {
                maxSGPA = students[i].getSGPA();
            }
        }
        
        // Implement counting sort for each digit
        for(float exp = 1; maxSGPA / exp > 0; exp *= 10) {
            countingSort(exp);
        }
    }

    void countingSort(float exp) {
        Student output[15];
        int count[10] = {0};

        for(int i = 0; i < n; i++) {
            int index = int(students[i].getSGPA() * exp) % 10;
            count[index]++;
        }

        for(int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for(int i = n - 1; i >= 0; i--) {
            int index = int(students[i].getSGPA() * exp) % 10;
            output[count[index] - 1] = students[i];
            count[index]--;
        }

        for(int i = 0; i < n; i++) {
            students[i] = output[i];
        }
    }
};

int main() {
    StudentRecords records;
    records.read();

    cout << "\nOriginal list of students:\n";
    records.write();

    // (a) Roll call list in ascending order by roll number
    records.insertionSort();
    cout << "\nStudents sorted by roll number:\n";
    records.write();

    // (b) List of students alphabetically
    records.shellSort();
    cout << "\nStudents sorted alphabetically by name:\n";
    records.write();

    // (c) List of first 10 toppers based on SGPA
    records.radixSort();
    cout << "\nTop 10 students based on SGPA:\n";
    records.write();

return 0;
}
