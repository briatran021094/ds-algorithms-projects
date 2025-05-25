/** Title: DoubleLinkedList
 * Class: CSC2431 Data Structures II
 * Purpose: Create a double linked list with all the ADT operations
 * Author: Bria Tran
 * Date: April 30th, 2025
*/

#include "object.h"
#include "dlinkedlist.h"
#include <sstream>

// Parameter: the other list
// Return: NONE
// Constructor for DoubleLinkedList
DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& other) : _head(nullptr), _tail(nullptr){
    Node* tmp = other._head;
    while (tmp != nullptr){
        Insert(new Object(*tmp->data), _size);
        tmp = tmp->next;
    }
}

// Parameter: Rhs list
// Return: Copied version of rhs Object* list
// Copy assignment operator for DoubleLinkedList
DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& rhs) {
    if(this != &rhs) {
        Clear();
        Node* tmp = rhs._head;
        while(tmp != nullptr) {
            Insert(new Object(*tmp->data), _size);
            tmp = tmp->next;
        }
    }
    return *this;
}

// Parameter: NONE
// Return: NONE
// Constructor for DoubleLinkedList
DoubleLinkedList::DoubleLinkedList() : _head(nullptr), _tail(nullptr) {}

// Parameter: NONE
// Return: NONE
// Destructor for DoubleLinkedList
DoubleLinkedList::~DoubleLinkedList() {
    Clear();
}

// Parameters: Object element, position of element
// Return: True if inserted
// Inserts the given Object at a designated position in the double linked list
bool DoubleLinkedList::Insert(Object* element, size_t position) {
    if (position > _size || element == nullptr) return false;
    Node* neo = new Node{element, nullptr, nullptr};

    if (_size == 0) _head = _tail = neo;       // Insert in an empty list
    else if (position == 0) {                  // Insert at Head
        neo->next = _head;
        _head->previous = neo;
        _head = neo;
    } else if (position == _size) {            // Insert at Tail
        neo->previous = _tail;
        _tail->next = neo;
        _tail = neo;
    } else {                                   // Inserting in the middle
        Node* tmp = _head;
        for (size_t i = 0; i < position; i++) tmp = tmp->next;
        neo->next = tmp;
        neo->previous = tmp->previous;
        tmp->previous->next = neo;
        tmp->previous = neo;
    }
    _size++;
    return true;
}

// Parameter: an Object element
// Return: Int value of element index
// Finds the index of the given element
int DoubleLinkedList::IndexOf(const Object* element)const {
    int index = 0;
    Node* tmp = _head;

    while(tmp != nullptr) {
        if((tmp->data)->Equals(*element)) return index;   // Checks if the objects are the same
        tmp = tmp->next;
        index++;
    }
    return -1;
}

// Parameter: position of element
// Return: the Object that was removed
// Finds and removes the Object at given position
Object* DoubleLinkedList::Remove(size_t position) {
    if (position >= _size) return nullptr;
    Node* tmp;

    if (position == 0) {                                  // Remove from head
        tmp = _head;
        _head = _head->next;
        if (_head != nullptr) _head->previous = nullptr;
        else _tail = nullptr;                             // List is empty
    } else if (position == _size - 1) {                   // Remove from tail
        tmp = _tail;
        _tail = _tail->previous;
        if (_tail != nullptr) _tail->next = nullptr;
        else _head = nullptr;                             // List is empty
    } else {                                              // Remove from middle
        tmp = _head;
        for (size_t i = 0; i < position; i++) tmp = tmp->next;
        tmp->previous->next = tmp->next;
        tmp->next->previous = tmp->previous;
    }

    Object* removed = tmp->data;
    delete tmp;
    --_size;
    return removed;
}

// Parameter: position of element
// Return: Object found at position
// Finds the Object pointer at the given position
Object* DoubleLinkedList::Get(size_t position)const {
    if(position > _size) return nullptr;
    Node* tmp = _head;
    for(size_t i = 0; i < position; i++) tmp = tmp->next;
    return tmp->data;
}

// Parameter: NONE
// Return: the list as a string
// Formats the list as a string
string DoubleLinkedList::ToString()const {
    std::stringstream linkedList;
    linkedList << "{";
    Node* tmp = _head;
    while(tmp != nullptr) {
        linkedList << tmp->data->ToString();
        if(tmp->next != nullptr) linkedList << ", ";
        tmp = tmp->next;
    }
    linkedList << "}";
    return linkedList.str();
}

// Parameter: NONE
// Return: NONE
// Clears all elements in the list
void DoubleLinkedList::Clear() {
    Node* tmp = _head;
    while(tmp != nullptr) {
        Node* next = tmp->next;
        delete tmp->data;
        delete tmp;
        tmp = next;
    }
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}