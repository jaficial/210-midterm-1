// COMSC-210 | Midterm 1 | Jed Aficial
// github link: https://github.com/jaficial/210-midterm-1
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList { // DoublyLinkedList is the class for initializing/creating a double linked list
private:
    // Node is a struct that is created to represent a node in the linked list.
    struct Node {
        int data; // The data type that Node holds is an integer data type
        Node* prev; // prev is a pointer to the node that is in one spot before the specified node
        Node* next; // next is a pointer to the node that is in one spot after the specified node
        
        /* Node(...) is a parameter constructor
               if the constructor is not given parameters, the pointer to the previous and next nodes are assigned
               to nullptr, as well as val remains an initialized integer variable

               if the constructor is provided parameters, the Node pointer p is assigned to prev, representing the 
               previous node, the Node pointer n is assigned to next, representing the next node, and val is assigned
               to the data variable*/
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    /* Node* head is a pointer to the head node, which represents the first node of the doubly linked list.
       The head's previous node should point to null.
       Node* tail is a pointer to the tail node, which represents the last node of the doubly linked list. 
       The next node pointer of the tail node should point to nullptr. */
    Node* head;
    Node* tail;

public:
    // default constructor of a doubly linked list which assigns the head and tail node pointers to null
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    /* insert_after is a class method which takes two int values, "value" and "position"
       position represents an index position in the linked list, while value represents the data that will
       be inserted into the linked list. The method then traverses the doubly linked list ,"position", 
       amount of times, then inserts the "value" in a new node at that position. The next node of this
       new node points to the node in position + 1, and the previous node of this new node points to 
       the node in position - 1. If the user chooses the position after the last node, then the next 
       node of this new node points to null. */
    void insert_after(int value, int position) {
        if (position < 0) { // The position must be at least at 0, as the doubly linked list starts at index 0.
                            // If the a position 
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}