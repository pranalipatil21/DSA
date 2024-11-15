/*PRN: 123B1B221
Name: Pranali Rajendra Patil
Assignment number: 10
Assignment Title:  : Implement a job scheduling system for a manufacturing plant using a double-ended queue. 
The system needs to efficiently manage the processing of jobs on various machines throughout the plant.
 Each job has a Job_priority. The system should support the following operations: 
 a. Add Job b. Remove Job c. Display Job d. Search Job*/
#include <iostream>
#include <string>

using namespace std;

class Job {
private:
    int id;
    int priority;

public:
    Job *next;
    Job *prev;

    Job(int id, int priority) {
        this->id = id;
        this->priority = priority;
        next = nullptr;
        prev = nullptr;
    }

    int getPriority() {
        return priority;
    }

    int getID() {
        return id;
    }
};

class JobScheduler {
private:
    Job *front;
    Job *rear;  
    int count;  // Total number of jobs in the queue

public:
    JobScheduler() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    // Add a job to the queue based on its priority
    void addJob(int id, int priority) {
        Job *newJob = new Job(id, priority);

        if (rear == nullptr) { // Case: Queue is empty
            front = rear = newJob;
        } else {
            // Insert based on priority
            if (front->getPriority() >= newJob->getPriority()) {
                rear->next = newJob;
                newJob->prev = rear;
                rear = newJob;
            } else {
                newJob->next = front;
                front->prev = newJob;
                front = newJob;
            }
        }
        count++;
        cout << "Job added: " << id << endl;
    }

    // Remove the highest-priority job from the queue
    void performJob() {
        if (front == nullptr) { // Case: Queue is empty
            cout << "No jobs to remove." << endl;
            return;
        }

        Job *temp = front;
        front = front->next;

        cout << "Job removed: " << temp->getID() << " with priority: " << temp->getPriority() << endl;
        delete temp;
        count--;
    }

    // Display all jobs in the queue from front to rear
    void displayJobs() {
        if (front == nullptr) { // Case: Queue is empty
            cout << "No jobs in the queue." << endl;
            return;
        }

        Job *temp = front;
        cout << "Jobs in the queue:" << endl;
        while (temp != nullptr) {
            cout << "Job ID: " << temp->getID() << ", Priority: " << temp->getPriority() << endl;
            temp = temp->next;
        }
    }
};

int main() {
    JobScheduler scheduler;
    int choice = 0;

    while (true) {
        cout << "1. Add Job." << endl
             << "2. Perform Job" << endl
             << "3. Display Jobs" << endl
             << "4. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        int id, priority;
        switch (choice) {
            case 1:
                cout << "Enter Job ID: ";
                cin >> id;
                cout << "Enter Priority: ";
                cin >> priority;
                scheduler.addJob(id, priority);
                break;

            case 2:
                scheduler.performJob();
                break;

            case 3:
                scheduler.displayJobs();
                break;

            case 4:
                cout << "Exiting!" << endl;
                return 0;

            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }

    return 0;
}
