#include <bits/stdc++.h>
using namespace std;

struct Node {
    string url;
    Node* next;
    Node(string u) : url(u), next(nullptr) {}
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(const string& url) {
        Node* newNode = new Node(url);
        newNode->next = top;
        top = newNode;
    }

    string pop() {
        if (isEmpty()) return "";
        Node* temp = top;
        string url = top->url;
        top = top->next;
        delete temp;
        return url;
    }

    string peek() const {
        return isEmpty() ? "" : top->url;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

class BrowserHistory {
private:
    Stack backStack;
    Stack forwardStack;
    string currentUrl;

public:
    BrowserHistory() : currentUrl("") {}

    void visit(const string& url) {
        if (!currentUrl.empty()) {
            backStack.push(currentUrl);
        }
        currentUrl = url;
        forwardStack.clear();
    }

    string goBack() {
        if (backStack.isEmpty()) {
            return "Cannot go back";
        }
        forwardStack.push(currentUrl);
        currentUrl = backStack.pop();
        return currentUrl;
    }

    string goForward() {
        if (forwardStack.isEmpty()) {
            return "Cannot go forward";
        }
        backStack.push(currentUrl);
        currentUrl = forwardStack.pop();
        return currentUrl;
    }

    string getCurrentUrl() const {
        return currentUrl;
    }
};

int main() {
    //doctor test
    BrowserHistory browser;
    string inputFileName = "Problem_1.txt"; 

    ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string command, url;
    while (inputFile >> command) {
        if (command == "visit") {
            inputFile >> url;
            browser.visit(url);
            cout << "Visited: " << browser.getCurrentUrl() << endl;
        } else if (command == "back") {
            cout << "Back: " << browser.goBack() << endl;
        } else if (command == "forward") {
            cout << "Forward: " << browser.goForward() << endl;
        } else {
            cout << "Invalid command" << endl;
        }
    }

    inputFile.close();

    //added test
    cout << "\n========================================================\n";
    cout << "Added test case:\n\n";
    BrowserHistory browserTest;
    string testFileName = "Problem 1 Test Case.txt";

    ifstream testFile(testFileName);

    if (!testFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string commandTest, urlTest;
    while (testFile >> commandTest) {
        if (commandTest == "visit") {
            testFile >> urlTest;
            browserTest.visit(urlTest);
            cout << "Visited: " << browserTest.getCurrentUrl() << endl;
        } else if (commandTest == "back") {
            cout << "Back: " << browserTest.goBack() << endl;
        } else if (commandTest == "forward") {
            cout << "Forward: " << browserTest.goForward() << endl;
        } else {
            cout << "Invalid commandTest" << endl;
        }
    }

    testFile.close();
    return 0;
}
