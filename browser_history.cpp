#include <iostream>
using namespace std;

// Structure representing a web page in the history
struct Page {
    string url;     // The URL of this page
    Page* prev;     // Pointer to the previous page
    Page* next;     // Pointer to the next page

    // Constructor: when a new Page is created, set its URL and initialize pointers
    Page(string url) {
        this->url = url;
        prev = NULL;
        next = NULL;
    }
};

class BrowserHistory {
private:
    Page* current;  // Pointer to the currently active page

public:
    // Constructor: initializes the browser with a homepage (or initial URL)
    BrowserHistory(string url) {
        current = new Page(url);  // Create a new Page and set as current
    }

    // Function to visit a new page (forwards)
    void visit(string url) {
        // Step 1: Delete all forward history (pages after current)
        Page* temp = current->next;
        while (temp) {
            Page* toDelete = temp;
            temp = temp->next;
            delete toDelete;      // Free memory for each forward page
        }
        current->next = NULL;     // Remove forward link from current

        // Step 2: Create new page and link it
        Page* new_page = new Page(url);
        current->next = new_page;  // Link current to new page
        new_page->prev = current;  // Link new page back to current
        current = new_page;        // Move current pointer to new page

        cout << "Visited: " << url << endl;
    }

    // Function to go back to the previous page
    void back() {
        if (current->prev) {        // Check if there’s a previous page
            current = current->prev;  // Move current pointer back
            cout << "Went back to: " << current->url << endl;
        } else {
            cout << "No previous page." << endl;
        }
    }

    // Function to go forward to the next page
    void next() {
        if (current->next) {        // Check if there’s a next page
            current = current->next;  // Move current pointer forward
            cout << "Went forward to: " << current->url << endl;
        } else {
            cout << "No next page." << endl;
        }
    }

    // Function to print the full browsing history (from start to end)
    void printHistory() {
        Page* temp = current;
        // Step 1: Go back to the start of the list
        while (temp->prev) {
            temp = temp->prev;
        }

        // Step 2: Walk through list and print URLs
        cout << "History: ";
        while (temp) {
            if (temp == current) {
                cout << "[" << temp->url << "] ";  // Highlight current page with brackets
            } else {
                cout << temp->url << " ";
            }
            temp = temp->next;
        }
        cout << endl;
    }

    // Destructor: clean up all pages from memory when BrowserHistory object is destroyed
    ~BrowserHistory() {
        // Step 1: Go back to the start
        while (current->prev) {
            current = current->prev;
        }

        // Step 2: Delete all nodes forward
        while (current) {
            Page* toDelete = current;
            current = current->next;
            delete toDelete;        // Free memory of each page
        }
    }
};

int main() {
    // Create a browser history starting with homepage "A"
    BrowserHistory bh("A");

    bh.visit("B");     // Visit page B
    bh.visit("C");     // Visit page C
    bh.back();         // Go back to B
    bh.printHistory(); // Should show: A [B] C

    bh.next();         // Go forward to C
    bh.printHistory(); // Should show: A B [C]

    bh.back();         // Go back to B
    bh.visit("D");     // Visit new page D (erases forward history)
    bh.printHistory(); // Should show: A B [D]

    return 0;
}
