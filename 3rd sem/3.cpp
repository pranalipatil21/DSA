/*
PRN: 123B1B221
Name: Pranali Rajendra Patil
Assignment number: 3
Assignment Title: Singly linked list
Consider the playlist in a music player. Implement a playlist feature in music player application 
using singly linked list. Each song in the playlist is represented as a node in the linked list. Each 
node contains information about the song (such as title or artist or duration, etc.).  
The playlist should allow users to:  
a. Add songs 
b. Remove songs 
c. Display the entire playlist 
d. Play specific songs*/
#include <iostream>
using namespace std;

class Song
{
    string title;
    string artist;
    string duration;

public:
    Song *next; // Pointer to the next song in the list
    Song() { next = NULL; } 

    // Function to read song details from user input
    void read()
    {
        cout << "Enter song title: ";
        cin >> title; 
        cout << "Enter artist name: ";
        cin >> artist;
        cout << "Enter duration : ";
        cin >> duration;
    }

    void display()
    {
        cout << "Title: " << title << ", Artist: " << artist << ", Duration: " << duration << endl;
    }

    string getTitle() { return title; }
};

class Playlist
{
    Song *head;

public:
    Playlist() { head = NULL; }

    // Function to add a song to the end of the playlist
    void addSong()
    {
        Song *nn = new Song; // Create a new song node
        nn->read();
        // If the playlist is empty, set head to the new song
        if (head == NULL)
        {
            head = nn;
        }
        else
        {
            Song *cn;
            for (cn = head; cn->next != NULL; cn = cn->next)
                ;
            cn->next = nn; // Link the new song at the end
        }
        cout << "Song added to the playlist." << endl; 
    }

    // Function to insert a song at the beginning of the playlist
    void insertAtBeginning()
    {
        Song *nn = new Song; // Create a new song node
        nn->read();

        // If the playlist is empty, set head to the new song
        if (head == NULL)
        {
            head = nn;
        }
        else
        {
            nn->next = head; // Link new song to the current head
            head = nn; // Update head to the new song
        }
        cout << "Song inserted at the beginning of the playlist." << endl; // Confirmation message
    }

    // Function to display the entire playlist
    void displayPlaylist()
    {
        if (head == NULL) // Check if the playlist is empty
        {
            cout << "Playlist is empty." << endl; // Message if empty
        }
        else
        {
            cout << "Playlist:" << endl;
            // Traverse through the linked list and display each song
            for (Song *cn = head; cn != NULL; cn = cn->next)
            {
                cn->display(); // Display song details
            }
        }
    }

    // Function to delete a song from the playlist
    void deleteSong()
    {
        if (head == NULL) // Check if the playlist is empty
        {
            cout << "Playlist is empty, nothing to delete." << endl; 
            return; 
        }

        string delTitle; 
        cout << "Enter the title of the song to delete: ";
        cin >> delTitle; 

        Song *prev = NULL; // Pointer to track the previous song
        bool found = false; // Flag to check if the song is found

        // Traverse the linked list to find the song to delete
        for (Song *cn = head; cn != NULL; prev = cn, cn = cn->next)
        {
            if (cn->getTitle() == delTitle) // Check if the current song matches the title
            {
                found = true; // Mark song as found
                if (prev == NULL) // If the song is at the head
                {
                    head = cn->next; // Update head to the next song
                }
                else
                {
                    prev->next = cn->next; // Bypass the deleted song
                }
                delete cn; // Free memory of the deleted song
                cout << "Song deleted from the playlist." << endl; 
                break; 
            }
        }

        // If song was not found, print a message
        if (!found)
        {
            cout << "Song not found in the playlist." << endl;
        }
    }

    // Function to play a specific song from the playlist
    void playSong()
    {
        if (head == NULL) // Check if the playlist is empty
        {
            cout << "Playlist is empty, nothing to play." << endl;
            return;
        }

        string playTitle;
        cout << "Enter the title of the song to play: ";
        cin >> playTitle;
        bool found = false; 

        // Traverse the linked list to find the song to play
        for (Song *cn = head; cn != NULL; cn = cn->next)
        {
            if (cn->getTitle() == playTitle) // Check if the current song matches the title
            {
                found = true; // Mark song as found
                cout << "Now playing: "; // Play the song
                cn->display(); 
                break;
            }
        }

        // If song was not found, print a message
        if (!found)
        {
            cout << "Song not found in the playlist." << endl;
        }
    }
};

int main()
{
    Playlist myPlaylist;
    int choice;

    do
    {
        cout << "\nPlaylist Menu:\n";
        cout << "1. Add song\n";
        cout << "2. Insert song at beginning\n";
        cout << "3. Display playlist\n";
        cout << "4. Delete song\n";
        cout << "5. Play specific song\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; 

       
        switch (choice)
        {
        case 1:
            myPlaylist.addSong(); 
            break;
        case 2:
            myPlaylist.insertAtBeginning(); 
            break;
        case 3:
            myPlaylist.displayPlaylist(); 
            break;
        case 4:
            myPlaylist.deleteSong(); 
            break;
        case 5:
            myPlaylist.playSong(); 
            break;
        case 6:
            cout << "Exiting..." << endl; 
            break;
        default:
            cout << "Invalid choice, please try again." << endl; 
        }
    } while (choice != 6); 
    return 0; 
}
