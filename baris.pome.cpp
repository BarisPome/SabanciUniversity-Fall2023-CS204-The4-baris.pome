//Barış Pome A-2 Section 31311  Homework 4
#include <iostream>
#include <algorithm>
using namespace std;
class LinkedListSet {
private:
    struct Node {
        int data;
        Node *next;
    };
    Node *head; // Head pointer
    Node *tail; // Tail pointer

public:
    LinkedListSet() { // Constructor for empty set
        head = nullptr;
        tail = nullptr;
    }

    void insert_in_order(int value) { // Insertion in order (ascending order)
        Node *newNode = new Node{value, nullptr}; // Create a new node in the heap with the given value
        if (!head || value < head->data) { // Insertion at the beginning
            newNode->next = head;
            head = newNode; // Update the head pointer
            if (!tail) {
                tail = newNode;
            }
        } else { // Insertion in the middle or at the end
            Node *current = head;
            while (current->next && value > current->next->data) { // Insertion in the middle
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            if (!newNode->next) { // Insertion at the end
                tail = newNode;
            }
        }
    }

    LinkedListSet& operator+(int value) { // Insertion
        if (!is_there(value)) { // If the value is not in the set to avoid duplicates
            insert_in_order(value);
        }
        return *this; // Return the set itself
    }

    void remove(int value) { // Deletion
        Node *current = head;
        Node *prev = nullptr;
        while (current && current->data != value) { // Search for the value
            prev = current;
            current = current->next;
        }
        if (current) { // If the value is found
            if (prev) { // Deletion in the middle or at the end
                prev->next = current->next;
                if (!prev->next) {
                    tail = prev;
                }
                delete current;
            } else { // Deletion at the beginning
                head = head->next;
                if (!head) {
                    tail = nullptr;
                }
                delete current;
            }
        }
    }

    LinkedListSet& operator-(int value) { // Deletion
        if (is_there(value)) { // If the value is in the set
            remove(value);
        }
        return *this;
    }

    LinkedListSet& operator+=(const LinkedListSet& other) { // Insertion with multiple right-hand values
        Node *current = other.head;
        while (current) { // Insertion of each value
            if (!is_there(current->data)) { // If the value is not in the set to avoid duplicates
                insert_in_order(current->data); // Insertion in order
            }
            current = current->next;
        }
        return *this;
    }

    LinkedListSet& operator-=(const LinkedListSet& other) { // Deletion with multiple right-hand values
        Node *current = other.head;
        while (current) {
            if (is_there(current->data)) { // If the value is in the set
                remove(current->data); // Deletion
            }
            current = current->next;
        }
        return *this;
    }

    LinkedListSet& operator&=(const LinkedListSet& other) { // Intersection
        LinkedListSet result; // Create a new set
        Node *current = other.head;
        while (current) {
            if (is_there(current->data)) { // If the value is in the set in the left-hand side
                result + current->data;  // Insertion
            }
            current = current->next;
        }
        delete head; // Delete the old set
        delete tail; // Delete the old set
        *this = result; // Update the set
        return *this;
    }

    bool is_there(int value) const { // Search for the value in the set
        Node *current = head;
        while (current) { // Search for the value
            if (current->data == value) { // If the value is found
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void display() const { // Display the set
        Node *current = head;
        cout << "LinkedListSet{"; // the format in the homework document expected this
        while (current) {
            cout << current->data; // Display the value
            cout << ", ";
            current = current->next; // Go to the next node
        }
        cout << "}";
        cout << endl;
    }

};

int main() { //the mai part of the code is given in the homework document
    LinkedListSet set1;
    set1 + 1 + 2 + 3 + 17; // Insertion
    set1.display(); // Display the set
    set1 - 2; // Deletion
    set1.display();
    LinkedListSet set2;
    set2 + 3 + 4 + 5;
    set2.display();
    set2 += set1 + 7 + 3 + 19; //Insertion with multiple right-hand values
    set2.display();
    LinkedListSet set3;
    set3 + 3 + 4 + 7 + 17 + 41; // Insertion
    set3.display();
    LinkedListSet set4;
    set4 + 41 + 37+ 7 + 19 + 41; // Insertion
    set4.display();
    // Set Union
    set1 += set2; // Insertion with multiple right-hand values
    set1.display();
    // Set Difference
    set1 -= set3; // Deletion with multiple right-hand values
    set1.display();
    // Set Intersection
    set1 &= set4;
    set1.display();

    return 0;
}

