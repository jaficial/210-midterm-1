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
       the node in position. If the user chooses the position after the last node, then the next 
       node of this new node points to null. */
    void insert_after(int value, int position) {
        if (position < 0) { // The position must be at least at 0, as the doubly linked list starts at index 0.
                            // If the a position < 0 is given, it is invalid and the function returns the user back to main.
            cout << "Position must be >= 0." << endl;
            return;
        }

        // if position is less than 0, a new node the provided value assigned to it's data.
        Node* newNode = new Node(value);
        if (!head) { // Tests if it is the first node of the doubly linked list. If it is, the new node 
                     // is head as well as the tail node. The function then returns to main.
            head = tail = newNode;
            return;
        }

        // if it isn't the first node in the doubly linked list, a new node pointer, "temp" points to
        // the head node, and temp is used to traverse the doubly linked list. 
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i) // for each iteration, temp pointer is assigned to the pointer that is 
                                                   // pointing to the node after temp
            temp = temp->next;

        if (!temp) { // if the provided position is greater than the size of the linked list, the node does not 
                     // get inserted into the list, and it is deallocated. The function then returns the user to main
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // newNode gets deallocated
            return;
        }
        
        // newNode's pointer to the next node is assigned the node pointer after temp, and
        // newNode's pointer to the previous node is assigned the node pointer to temp 
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next) // if the pointer to the next node of temp is a node
            temp->next->prev = newNode; // the pointer to the previous node of temp->next is assigned the pointer to newNode
        else // if there isn't a node after the position, then it is a tail
            tail = newNode; // the new node becomes the tail node
        temp->next = newNode; // the pointer to the next node of the tail's previous node now points to tail which holds the new node
    }

    // delete_val takes in an int type parameter which represents the data within a node. This method
    // deletes a node based on being given the data in the node
    void delete_val(int value) {
        if (!head) return; // if there is no head node, the doubly linked list is empty and the method returns back to main

        Node* temp = head; // node pointer temp that is assigned the head node, is used to traverse the doubly linked list
        
        while (temp && temp->data != value) // if the data in temp, is not the same as the provided value from the parameter,
                                            // temp is assigned the node pointer to the next node in front of it
            temp = temp->next;

        if (!temp) return; // if the provided value is not in the linked list, the method returns back to main

        if (temp->prev) // if a node exists before the temp node,
            temp->prev->next = temp->next; // the next node pointer of the temp's previous node now points to temp's pointer to the next node
        else // if a node doesn't exist before temp node, then the node to delete is the head node.
            head = temp->next; // the pointer to the head node now points it's next node

        if (temp->next) // if a node exists after the temp node, 
            temp->next->prev = temp->prev; // the pointer to the previous node of temp's next node is assigned the pointer to temp's previous node
        else // else a node doesn't exist after temp node, meaning the node to be deleted is the tail node
            tail = temp->prev;  // tail node now points to it's previous node.

        delete temp; // temp node is now deallocated
    }

    // delete_pos takes in an int type parameter which represents the index position of a node. This method 
    // deletes a node based on being given the index position of a node
    void delete_pos(int pos) {
        if (!head) { // if there is no head node, the doubly linked list is empty and the method returns back to main
            cout << "List is empty." << endl;
            return;
        }
        // if the index position given is the first position of the doubly linked list,
        // delete_pos utilizes the "pop_front" method to pop the head of the doubly linked list and returns back to main.
        if (pos == 1) {
            pop_front();
            return;
        }
        
        // temporary node pointer is created to traverse the doubly linked list. It is assigned the head node
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){ // traversing the linked list
            if (!temp) { // if provided position doesn't exist in the list, delete_pos returns user back to main.
                cout << "Position doesn't exist." << endl;
                return;
            }
            else // temp traverses the linked list by assigning temp to the pointer it's next node
                temp = temp->next;
        }

        if (!temp) { // if temp isn't a valid node after traversing the doubly linked list, it returns back to main
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) { // if the pointer of temp's next node points to null, the tail is to be deleted
                           // and the "pop_back" method is used
            pop_back();
            return;
        }

        // Else if the temp node isn't the head or tail node, a temp node pointer is created to represent the node 
        // pointing to temp's previous node. 
        Node* tempPrev = temp->prev; 
        tempPrev->next = temp->next; // tempPrev pointer to the next node is assigned the pointer to temp's next node. 
        temp->next->prev = tempPrev; // The pointer to the previous node of temp's next node is now assigned the tempPrev node
        delete temp; // temp node gets deallocated
    }
    
    // push_back appends a node to the tail end of the doubly linked list, containing data from the provided int parameter, "v"
    void push_back(int v) { // v represents data for the new node
        Node* newNode = new Node(v); // new node is initialized for the new value 
        if (!tail) // if a tail doesn't exist, then it's an empty list
            head = tail = newNode; // the new node is now the head and tail of the list
        else { // if tail does exist
            tail->next = newNode; // the original tail node points to the new node,
            newNode->prev = tail; // the pointer to the previous node of the new node points to the original tail node
            tail = newNode; // the tail node is now assigned the new node
        }
    }
    // push_front appends a node to the head end of the doubly linked list, containing data form the provided int parameter, "v" 
    void push_front(int v) { // v represents data for the new node
        Node* newNode = new Node(v); // new node is initialized for the new value
        if (!head) // if there isn't a head, it's an empty list,
            head = tail = newNode; // head and tail nodes are assigned the new node
        else { // if there is a head,
            newNode->next = head; // the pointer to the next node of the new node, points to the original head pointer
            head->prev = newNode; // the pointer to the previous node of the original head node now points to the new node
            head = newNode; // the head node is assigned the new node
        }
    }
    
    // pop_front deletes the head node of the doubly linked list and, makes the head->next the new head node
    void pop_front() {

        if (!head) { // if there is now head, the linked list is empty, and returns back to main
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head; // temp node is created assigned to head

        if (head->next) { // if there is a node after head, the new head node is assigned the pointer to the original head's next node
            head = head->next;
            head->prev = nullptr; // pointer to head's previous node points to null
        }
        else // if there isn't a valid node after head, it means it is the last node in the list
            head = tail = nullptr; // becomes empty list
        delete temp; // deallocates temp node
    }

    // 
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