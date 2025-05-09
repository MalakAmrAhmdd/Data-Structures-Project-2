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
                }
                w->bfactor = 0;
                rotateToLeft(p);
                rt->l = p;
                rotateToRight(rt);
        }
    }

    void balanceFromRight(Node* &rt){
        Node *p;
        Node *w;
        p = rt->r;
        switch(p->bfactor){
            case -1:
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
                }
                w->bfactor = 0;
                rotateToRight(p);
                rt->r = p;
                rotateToLeft(rt);
            case 0:
                cout << "Error: Cannot balance from the right." << endl;
            case 1:
                rt->bfactor = 0;
                p->bfactor = 0;
                rotateToLeft(rt);
        }
    }

    void insertionIntoAVL(Node* &rt, Contact data) {
        if (rt == NULL) {
            rt = new Node;
            rt->info = data;
            rt->l = NULL;
            rt->r = NULL;
            rt->bfactor = 0;
        } else if (data.id < rt->info.id) {
            insertionIntoAVL(rt->l, data);
            if (rt->bfactor == 1) {
                rt->bfactor = 0;
            } else if (rt->bfactor == 0) {
                rt->bfactor = -1;
            } else {
                balanceFromLeft(rt);
            }
        } else if (data.id > rt->info.id) {
            insertionIntoAVL(rt->r, data);
            if (rt->bfactor == -1) {
                rt->bfactor = 0;
            } else if (rt->bfactor == 0) {
                rt->bfactor = 1;
            } else {
                balanceFromRight(rt);
            }
        }
    }
    void insertionIntoAVLHelper(Contact data){
        insertionIntoAVL(root, data);
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

    Node* balanceAfterDel(Node* rt){
        if(rt->bfactor == 2){
            if(rt->r->bfactor == -1){
                balanceFromRight(rt);
            }
            rt->bfactor = 0;
        }
        else if (rt->bfactor == -2){
            if (rt->r->bfactor == 1){
                balanceFromLeft(rt);
            }
            rt->bfactor = 0;
        }
        return rt;
    }

    void deleteContactHelper(Contact data){
        root = deleteContact(root , data);
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

    void displayBFS() {
        Node *curr = root;
        if (root == NULL) return;

        Queue<Node> q;
        int lev = height;
        q.push(root);
        while (!q.isEmpty()){
            q.push(curr);
            int sz = q.size();
            while (sz--) {
                curr = q.front();
                q.pop();
                for (int i = 0; i < 3*lev; i++) cout << " ";
                cout << curr->info.id;
                if(curr->l != NULL){
                    q.push(curr->l);
                }
                if(curr->r != NULL){
                    q.push(curr->r);
                }
            }
            cout << endl;
            for (int i = 0; i < q.size(); i++) {
                for (int j = 0; j < 3 * (lev) - 2; j++) {
                    cout << " ";
                }
                cout << "/" << "   " << "\\";
            }
            cout << endl;
            lev--;

        }
    }

    void display() {
        updateTreeHeight();
        displayBFS();
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

int main(){

    cout <<"Address Book Application\n";

    AVL avl;
    int choice;
    while(true){
        cout << "=========================\n";
        cout << "1. Add Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. List Contacts\n";
        cout << "5. Display Current Tree Structure\n";
        cout << "6. Exit\n";
        cout << "=========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:{
                int id;
                string name, phone, email;
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Phone: ";
                cin >> phone;
                cout << "Enter Email: ";
                cin >> email;
                Contact newContact(id, name, phone, email);
                avl.insertionIntoAVLHelper(newContact);
                break;
            }
            case 2:{
                int id;
                cout << "Enter ID to search: ";
                cin >> id;
                Contact searchContact(id, "", "", "");
                avl.search(searchContact);
                break;
            }
            case 3: {
                int idToDelete;
                cout << "Enter ID to delete: ";
                cin >> idToDelete;
                Contact deleteContact(idToDelete, "", "", "");
                avl.deleteContactHelper(deleteContact);
                cout << "Contact deleted successfully.\n";
                break;
            }
            case 4:
                cout<< "List of Contacts:\n";
                avl.listContacts();
                break;
            case 5:
                cout <<"Tree structure: " << endl << endl;
                avl.display();
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}
