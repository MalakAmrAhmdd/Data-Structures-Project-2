#include <bits/stdc++.h>
using namespace std;


struct Contact{
    int id;
    string name, phone, email;
    Contact(int new_id , string new_name, string new_phone, string new_email){
        id = new_id;
        name = new_name;
        phone = new_phone;
        email = new_email;
    }
    Contact(){}
};


template <class T>
class Queue {
private:
    struct Node {
        T* data;
        Node* next;
        Node(T* val): data(val), next(NULL){};
    };
    Node *head, *tail;
    int len = 0;

public:
    Queue() : head(NULL), tail(NULL), len(0) {}
    int size() {
        return len;
    }

    void push(T* val) {
        Node* newnode = new Node(val);
        if (head == NULL) {
            head = newnode;
            tail = newnode;
        }
        else {
            tail->next = newnode;
            tail = newnode;
        }
        len++;
    }
    bool isEmpty(){
        return len == 0;
    }

    void pop() {
        if (len == 0) {
            cout << "Queue is empty!" << endl;
        }
        else {
            Node* first = head;
            head = head->next;
            delete first;
            len--;
            if (len == 0) tail = NULL;
        }
    }

    T* front() {
        assert(!isEmpty());
        return head->data;
    }
};


class AVL{
private:
    struct Node{
        Contact info;
        Node* l;
        Node* r;
        int bfactor;
    };
    Node* root;
    int height = 0;
public:
    AVL(): root(nullptr){}

    bool isEmpty() {return root == NULL;}

    void rotateToLeft(Node* &rt){ // RR imbalance
        Node *p;
        if(rt == NULL){
            cout << "Error in the tree" << endl;
        }else if (rt->r == NULL){
            cout << "Error in the tree: \n";
            cout << "No right subtree to rotate.\n";
        }else{
            p = rt->r;
            rt->r = p-> l;
            p->l = rt;
            rt = p;
        }
    }
    void rotateToRight(Node* &rt){ // LL imbalance
        Node *p;
        if(rt == NULL){
            cout << "Error in the tree" << endl;
        }else if (rt->l == NULL){
            cout << "Error in the tree: \n";
            cout << "No left subtree to rotate.\n";
        }else{
            p = rt->l;
            rt->l = p-> r;
            p->r = rt;
            rt = p;
        }
    }
    void balanceFromLeft(Node* &rt){
        Node *p;
        Node *w;
        p = rt->l;
        switch(p->bfactor){
            case -1: // LL single Rotation needed
                rt->bfactor = 0;
                p->bfactor = 0;
                rotateToRight(rt);
                break;
            case 0:
                cout << "Error: Cannot balance from the left." << endl;
                break;
            case 1: // LR Case
                w = p->r;
                switch (w->bfactor) {
                    case -1:
                        rt->bfactor = 1;
                        p->bfactor = 0;
                        break;
                    case 0:
                        rt->bfactor = 0;
                        p->bfactor = 0;
                        break;
                    case 1:
                        rt->bfactor = 0;
                        p->bfactor = -1;
                        break;
                }
                w->bfactor = 0;
                rotateToLeft(p);
                rt->l = p;
                rotateToRight(rt);
                break;
        }
    }

    void balanceFromRight(Node* &rt){
        Node *p;
        Node *w;
        p = rt->r;
        switch(p->bfactor){
            case -1: // RL Case
                w = p->l;
                switch (w->bfactor) {
                    case -1:
                        rt->bfactor = 0;
                        p->bfactor = 1;
                        break;
                    case 0:
                        rt->bfactor = 0;
                        p->bfactor = 0;
                        break;
                    case 1:
                        rt->bfactor = -1;
                        p->bfactor = 0;
                        break;
                }
                w->bfactor = 0;
                rotateToRight(p);
                rt->r = p;
                rotateToLeft(rt);
                break;
            case 0:
                cout << "Error: Cannot balance from the right." << endl;
                break;
            case 1:
                rt->bfactor = 0;
                p->bfactor = 0;
                rotateToLeft(rt);
                break;
        }
    }

void insertionIntoAVL(Node* &rt, Contact data, bool &heightChanged) {
    if (rt == NULL) {
        rt = new Node;
        rt->info = data;
        rt->l = NULL;
        rt->r = NULL;
        rt->bfactor = 0;
        heightChanged = true; // Height of the tree has increased
    } else if (data.id < rt->info.id) {
        insertionIntoAVL(rt->l, data, heightChanged);
        if (heightChanged) {
            if (rt->bfactor == 1) {
                rt->bfactor = 0;
                heightChanged = false;
            } else if (rt->bfactor == 0) {
                rt->bfactor = -1;
            } else {
                balanceFromLeft(rt);
                heightChanged = false;
            }
        }
    } else if (data.id > rt->info.id) {
        insertionIntoAVL(rt->r, data, heightChanged);
        if (heightChanged) {
            if (rt->bfactor == -1) {
                rt->bfactor = 0;
                heightChanged = false;
            } else if (rt->bfactor == 0) {
                rt->bfactor = 1;
            } else {
                balanceFromRight(rt);
                heightChanged = false;
            }
        }
    }
}
    void insertionIntoAVLHelper(Contact data) {
    bool heightChanged = false;
    insertionIntoAVL(root, data, heightChanged);
    }

    void search(Contact data){
        Node* curr;
        curr = root;
        while(curr!=NULL){
            if(data.id > curr->info.id){
                curr = curr->r;
            }
            else if (data.id< curr->info.id){
                curr = curr->l;
            }
            else{
                cout << "Contact found: " << endl;
                cout << "ID: " << curr->info.id << endl;
                cout << "Name: " << curr->info.name << endl;
                cout << "Phone: " << curr->info.phone << endl;
                cout << "Email: " << curr->info.email  << endl;
                return;
            }
        }
        cout << "Contact not found" << endl;
    }


    void listContacts() {
        listContactsHelper(root);
    }
    void listContactsHelper(Node* node) {
        if (node == NULL) return;
        listContactsHelper(node->l);
        cout << "ID: " << node->info.id << ", Name: " << node->info.name
             << ", Phone: " << node->info.phone << ", Email: " << node->info.email << endl;
        listContactsHelper(node->r);
    }

    Node* suc(Node* &rt){
        while(rt->l!=NULL){
            rt = rt->l;
        }
        return rt;
    }

    Node* deleteContact(Node* rt,Contact data){
        if(rt == NULL) return NULL;
        if(data.id < rt->info.id){
            rt->l = deleteContact(rt->l , data);
        }
        else if(data.id > rt->info.id){
            rt->r = deleteContact(rt->r,data);
        }
        else{
            if(rt->l == NULL){
                Node* temp = rt->r;
                delete rt;
                return temp;
            }
            else if (rt->r == NULL){
                Node* temp = rt->l;
                delete rt;
                return temp;
            }
            Node* temp = suc(rt->r);
            rt->info = temp->info;
            rt->r = deleteContact(rt->r,temp->info);
        }
        return balanceAfterDel(rt);
    }


    Node* balanceAfterDel(Node* rt) {
        if (rt == NULL) return NULL;

        
        int leftHeight = treeHeight(rt->l);
        int rightHeight = treeHeight(rt->r);
        rt->bfactor = rightHeight - leftHeight;

        // Check for imbalance
        if (rt->bfactor == 2) { // RR Case
            if (rt->r->bfactor < 0) { // RL case
                balanceFromRight(rt->r);
            }
            rotateToLeft(rt);
        } else if (rt->bfactor == -2) { //LL case
            if (rt->l->bfactor > 0) { // LR case
                balanceFromLeft(rt->l);
            }
            rotateToRight(rt);
        }

        return rt;
    }
    void deleteContactHelper(Contact data){
        root = deleteContact(root , data);
        updateTreeHeight();
    }

    int treeHeight(Node *p)
    {
        if(p == NULL)
            return 0;
        else
            return 1 + max(treeHeight(p->l), treeHeight(p->r));
    }

    void updateTreeHeight() {
        height = treeHeight(root);
    }

void displayBF() {
    if (root == NULL) return;

    Queue<Node> q;
    q.push(root);
    int level = height;

    while (!q.isEmpty()) {
        int sz = q.size();
        Node** currentLevel = new Node*[sz]; // Dynamically allocate array for current level

        // Process the current level
        for (int i = 0; i < sz; i++) {
            Node* curr = q.front();
            q.pop();
            currentLevel[i] = curr;

            // Print spaces for alignment
            if (i == 0) cout << setfill(' ') << setw(5 * level) << ""; // Increased initial spacing
            else cout << setfill(' ') << setw(3 * level) << "";

            // Print node value or empty space
            if (curr != NULL) {
                cout << curr->info.id;
                q.push(curr->l);
                q.push(curr->r);
            } else {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
        }
        cout << endl;

        // Print branches based on parent alignment
        for (int i = 0; i < sz; i++) {
            Node* curr = currentLevel[i];
            if (i == 0) cout << setfill(' ') << setw(5 * level - 3) << ""; // Adjusted branch alignment
            else cout << setfill(' ') << setw(3 * level - 3) << "";

            if (curr != NULL) {
                cout << (curr->l != NULL ? "/" : " ");
                cout << setfill(' ') << setw(6) << ""; // Increased spacing between slashes
                cout << (curr->r != NULL ? "\\" : " ");
            } else {
                cout << "      ";
            }
        }
        cout << endl;
        level--;

        // Stop processing if all nodes in the queue are NULL
        bool allNull = true;
        for (int i = 0; i < q.size(); i++) {
            Node* temp = q.front();
            q.pop();
            if (temp != NULL) allNull = false;
            q.push(temp);
        }
        if (allNull) break;

        delete[] currentLevel; // Free dynamically allocated memory
    }
}

    void display() {
        updateTreeHeight();
        displayBF();
    }


};


void readFromFile(AVL &avl, const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    int id;
    string name, phone, email;
    while (file >> id >> name >> phone >> email) {
        Contact contact(id, name, phone, email);
        avl.insertionIntoAVLHelper(contact);
    }
    file.close();
}

void processOperationsFromFile(AVL &avl, const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening input file: " << filename << endl;
        return;
    }

    int operation;
    while (file >> operation) {
        switch (operation) {
            case 1: { // Add Contact
                cout << "\nOption chosed: " << 1 << " Adding new contact\n";
                int id;
                string name, phone, email;
                file >> id;
                file.ignore(); // Skip newline
                getline(file, name);
                getline(file, phone);
                getline(file, email);

                Contact check(id, "", "", "");
                stringstream buffer;
                streambuf* prevcout = cout.rdbuf(buffer.rdbuf());
                avl.search(check);
                cout.rdbuf(prevcout);

                if (buffer.str().find("Contact found") != string::npos) {
                    cout << "Error: Contact with ID " << id << " already exists." << endl;
                } else {
                    cout << "Inserting contact " << id << " with\n";
                    cout << "Name: " << name << '\n';
                    cout << "Phone number: " << phone << '\n';
                    cout << "Email: " << email << '\n';
                    cout << "Into the address book..." << '\n';
                    Contact contact(id, name, phone, email);
                    avl.insertionIntoAVLHelper(contact);
                    cout << "\nContact added successfully." << endl;
                }
                break;
            }
            case 2: { // Search
                int id;
                file >> id;
                cout << "\nOption chosed: " << 2 << " -> Searching for contact with id " << id << '\n';
                Contact temp(id, "", "", "");
                avl.search(temp);
                break;
            }
            case 3: { // Delete
                int id;
                file >> id;
                cout << "\nOption chosed: " << 2 << " -> Delting contact with id " << id << '\n';
                Contact temp(id, "", "", "");
                stringstream buffer;
                streambuf* prevcout = cout.rdbuf(buffer.rdbuf());
                avl.search(temp);
                cout.rdbuf(prevcout);

                if (buffer.str().find("Contact not found") != string::npos) {
                    cout << "Contact not found." << endl;
                } else {
                    avl.deleteContactHelper(temp);
                    cout << "Contact deleted successfully." << endl;
                }
                break;
            }
            case 4: // List Contacts
                cout << "Option chosed: " << 4 << " -> Listing All ";
                cout << "Contacts in Address Book (sorted by ID):" << endl;
                if (avl.isEmpty()) cout << "Address Book is Empty!" << '\n';
                else avl.listContacts();
                break;

            case 5: // Display Tree
                cout << "\nOption chosed: " << 2 << " -> Displaying Current Tree Structure: " << '\n';
                avl.display();
                break;

            default:
                cout << "Invalid operation in file: " << operation << endl;
                break;
        }
    }

    file.close();
}


int main(){
    cout <<"Address Book Application\n";
    AVL avl;
    // readFromFile(avl, "contacts.txt");
    processOperationsFromFile(avl, "Problem 2.txt");
}
