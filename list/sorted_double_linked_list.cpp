/** Title: SortedDoubleLinkedList
 * Class: CSC2431 Data Structures II
 * Purpose: A double linked list that keeps its elements sorted at all times
 * Author: Bria Tran
 * Date: April 30th, 2025
*/

#include "sorted_double_linked_list.h"

// Parameter: NONE
// Return: NONE
// Constructor for SortedDoubleLinkedList
SortedDoubleLinkedList::SortedDoubleLinkedList() : DoubleLinkedList(){}

// Parameter: a Comparable object element
// Return: True if inserted
// Inserts Comparable element into the doubly linked list in sorted order.
// The list maintains ascending order based on the result of CompareTo.
bool SortedDoubleLinkedList::Insert(Comparable* element) {
    Node* neo = new Node{element, nullptr, nullptr};

    if (!_head) _head = _tail = neo;     // Empty list
    else {
        Node* tmp = _head;                                                                      // Traverse the list to find the first node with data >= element,
        while (tmp && element->CompareTo(dynamic_cast<const Comparable*>(tmp->data)) > 0)       // Use CompareTo to maintain sorted order (casting data to Comparable*)
        tmp = tmp->next;

        if (!tmp) {                      // Insert at the end
            neo->previous = _tail;
            _tail->next = neo;
            _tail = neo;
        } else if (!tmp->previous) {     // Insert at the beginning
            neo->next = _head;
            _head->previous = neo;
            _head = neo;
        } else {                         // Insert in the middle
            neo->previous = tmp->previous;
            neo->next = tmp;
            tmp->previous->next = neo;
            tmp->previous = neo;
        }
    }

    _size++;
    return true;
}