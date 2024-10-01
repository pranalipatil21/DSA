#include<iostream>
using namespace std;

struct stud {
    int roll;
    string name;
    float sgpa;
};

class student {

public:
    stud s[15]; // array of 15 student records
    int n;

    void read() {
        cout << "Enter the number of students: ";
        cin >> n;

        for(int i = 0; i < n; i++) {
            cout << "Enter the name of student " << i + 1 << ": ";
            cin >> s[i].name;
            cout << "Enter the roll number of student " << i + 1 << ": ";
            cin >> s[i].roll;
            cout << "Enter the SGPA of student " << i + 1 << ": ";
            cin >> s[i].sgpa;
        }
    }

    void write() {
        for(int i = 0; i < n; i++) {
            cout << "NAME: " << s[i].name << "\n";
            cout << "ROLL NUMBER: " << s[i].roll << "\n";
            cout << "SGPA: " << s[i].sgpa << "\n\n";
        }
    }

    // (a) Insertion Sort based on SGPA
    void insertionSort() {
        for(int i = 1; i < n; i++) {
            stud key = s[i];
            int j = i - 1;
            while(j >= 0 && s[j].sgpa < key.sgpa) { // Sort in descending order
                s[j + 1] = s[j];
                j--;
            }
            s[j + 1] = key;
        }
    }

    // (b) Radix Sort based on roll numbers
    void radixSort() {
        int maxRoll = s[0].roll;
        for(int i = 1; i < n; i++) {
            if(s[i].roll > maxRoll) {
                maxRoll = s[i].roll;
            }
        }

        // Implement counting sort for each digit
        for(int exp = 1; maxRoll / exp > 0; exp *= 10) {
            countingSort(exp);
        }
    }

    void countingSort(int exp) {
        stud output[15];
        int count[10] = {0};

        for(int i = 0; i < n; i++) {
            int index = (s[i].roll / exp) % 10;
            count[index]++;
        }

        for(int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for(int i = n - 1; i >= 0; i--) {
            int index = (s[i].roll / exp) % 10;
            output[count[index] - 1] = s[i];
            count[index]--;
        }

        for(int i = 0; i < n; i++) {
            s[i] = output[i];
        }
    }

    // (c) Shell Sort based on names
    void shellSort() {
        for(int gap = n / 2; gap > 0; gap /= 2) {
            for(int i = gap; i < n; i++) {
                stud temp = s[i];
                int j;
                for(j = i; j >= gap && s[j - gap].name > temp.name; j -= gap) {
                    s[j] = s[j - gap];
                }
                s[j] = temp;
            }
        }
    }
};

int main() {
    student cls;
    cls.read();

    cout << "\nOriginal list of students:\n";
    cls.write();

    // (a) List of first 3 toppers based on SGPA
    cls.insertionSort();
    cout << "\nTop 3 students based on SGPA:\n";
    for(int i = 0; i < 3 && i < cls.n; i++) {
        cout << "NAME: " << cls.s[i].name << "\n";
        cout << "ROLL NUMBER: " << cls.s[i].roll << "\n";
        cout << "SGPA: " << cls.s[i].sgpa << "\n\n";
    }

    // (b) Roll call list in ascending order by roll number
    cls.radixSort();
    cout << "\nStudents sorted by roll number:\n";
    cls.write();

    // (c) List of students alphabetically
    cls.shellSort();
    cout << "\nStudents sorted alphabetically by name:\n";
    cls.write();

    return 0;
}
