#include <iostream>     // For input/output
using namespace std;

// ======================
// Structure for Page Node
// ======================
struct Page {
    string url;     // URL of the current page
    Page* prev;     // Pointer to the previous page
    Page* next;     // Pointer to the next page

    // Constructor to initialize a page node
    Page(string url) {
        this->url = url;
        prev = next = nullptr;
    }
};

// =============================
// Browser History Class (DLL)
// =============================
class BrowserHistory {
private:
    Page* current;  // Pointer to the current page

public:
    // Constructor to initialize the browser with a homepage
    BrowserHistory(string homepage) {
        current = new Page(homepage);
    }

    // Function to visit a new page
    void visit(string url) {
        Page* newPage = new Page(url); // Create a new page

        // Break the forward history (if any)
        current->next = nullptr;

        // Link current to the new page
        current->next = newPage;
        newPage->prev = current;

        // Move current to new page
        current = newPage;

        cout << "Visited: " << url << endl;
    }

    // Function to go back to previous page
    void back() {
        if (current->prev) {
            current = current->prev;
            cout << "Moved Back to: " << current->url << endl;
        } else {
            cout << "No previous page!" << endl;
        }
    }

    // Function to go forward to next page
    void forward() {
        if (current->next) {
            current = current->next;
            cout << "Moved Forward to: " << current->url << endl;
        } else {
            cout << "No forward page!" << endl;
        }
    }

    // Function to display the current page
    void showCurrent() {
        cout << "Current Page: " << current->url << endl;
    }
};

// =========================
// Main Function for Testing
// =========================
int main() {
    // Start browser with homepage
    BrowserHistory browser("home.com");

    browser.showCurrent();       // Should print home.com

    // Visit new pages
    browser.visit("page1.com");  // Visit page1
    browser.visit("page2.com");  // Visit page2

    // Navigate back
    browser.back();              // Go to page1
    browser.back();              // Go to home

    // Navigate forward
    browser.forward();           // Go to page1

    // Visit new page, forward history is cleared
    browser.visit("page3.com");  // Visit page3

    // Try to move forward (should fail)
    browser.forward();           // No forward page

    // Final current page
    browser.showCurrent();       // Should print page3.com

    return 0;
}
