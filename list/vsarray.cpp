/** Title: VSArray
 * Class: CSC2431 Data Structures II
 * Purpose: Create a variable sized array with all the ADT operations
 * Author: Bria Tran
 * Date: May 1st, 2025
*/

#include "object.h"
#include "list.h"
#include "vsarray.h"
#include <sstream>

// Parameter: another list array
// Return: NONE
// Constructor of VSArray
VSArray::VSArray(const VSArray& other) : _capacity(other._capacity), _delta(other._delta){
    _size = other._size;
    _data = new Object*[_capacity];
    for(size_t i = 0; i < _size; i++) _data[i] = other._data[i];           // Copies data from other
    for(size_t i = _size; i < _capacity; i++) _data[i] = nullptr;          // Sets remaining list to nullptr
}

// Parameter: the rhs list array
// Return: NONE
// Copy constructor for VSArray
const VSArray& VSArray::operator=(const VSArray& rhs) {
    if (&rhs == this) return *this;
    Clear();
    delete[] _data;
    _size = rhs._size;                                                     // Sets new variable values from rhs
    _delta = rhs._delta;
    _capacity = rhs._capacity;
    _data = new Object *[_capacity];

    for (size_t i = 0; i < rhs.Size(); i++) _data[i] = rhs._data[i];       // Copies the data from rhs to _data
    return *this;
}

// Parameter: NONE
// Return: NONE
// Resizes the list by increasing capacity by delta
void VSArray::Resize() {
    size_t newCap;
    if(_delta >= 0 && _delta <= 1) {          // Determines if delta was a percentage or fixed number
        double growth = 1.0 + _delta;
        newCap = _capacity * growth;
    } else newCap = _capacity + _delta;

    Object** newData = new Object*[newCap];
    for(size_t i = 0; i < _size; i++) newData[i] = _data[i];                // Copies elements from data to newData array
    for(size_t i = _size; i < newCap; i++) newData[i] = nullptr;            // Sets remaining list to nullptr

    delete[] _data;
    _data = newData;
    _capacity = newCap;
}

// Parameters: capacity of the list, percentage to increase the capacity by
// Return: NONE
// Constructor for VSArray
VSArray::VSArray(size_t capacity, double increasePercentage) : _capacity(capacity), _delta(increasePercentage){
    _data = new Object*[_capacity];
    for(size_t i = 0; i < _capacity; i++) _data[i] = nullptr;
}

// Parameter: NONE
// Return: NONE
// Destructor for the VSArray
VSArray::~VSArray() {
    Clear();
    delete[] _data;
}

// Parameter: object element to insert, position to insert in
// Returns: True if inserted
// Inserts the given Object at a designated position in VSArray
bool VSArray::Insert(Object* element, size_t position) {
    if(position > _size) {                                               // Checks if position is out of bounds/needs to be resized
        return false;
    } else if (_capacity == _size) Resize();

    for(size_t i = _size; i > position; i--) _data[i] = _data[i - 1];    // Shifts elements to the right to insert the element
    _data[position] = element;
    _size++;
    return true;
}

// Parameter: element object
// Return: Int of the element's index
// Finds index of element in the list
int VSArray::IndexOf(const Object* element)const {
    if(element == nullptr) return -1;
    for(size_t index = 0; index < _size; index++ ) {
        if(_data[index]->Equals(*element)) return static_cast<size_t>(index); // Check if objects are the same
    }
    return -1;
}

// Parameter: the position to remove an Object
// Return: the Object to be removed
// Removes an element at a certain position in the list
Object* VSArray::Remove(size_t position) {
    if(position >= _size) return nullptr;
    Object* removed = _data[position];

    for(size_t i = position; i < _size - 1; i++) _data[i] = _data[i + 1]; // Removes an element and shifts elements to the left
    _data[_size - 1] = nullptr;
    _size--;
    return removed;
}

// Parameter: the position to find the object
// Return: the Object found at position
// Finds the element at given position in the list
Object* VSArray::Get(size_t position)const {
    if (position >= _size) return nullptr;
    return _data[position];
}

// Parameter: NONE
// Return: the linked list as a string
// Formats the linked list as a string
string VSArray::ToString()const {
    std::stringstream output;
    if(_size == 0) return "{}";
    output << "{";

    for(size_t i = 0; i < _size - 1; i++) output << _data[i]->ToString() << ", ";
    output << _data[_size - 1]->ToString() << "}";
    return output.str();
}

// Parameter: NONE
// Return: NONE
// Clears list
void VSArray::Clear() {
    for(size_t i = 0; i < _size; i++) delete _data[i], _data[i] = nullptr;
    _size = 0;
}

// Parameter: NONE
// Return: a size_t value for the capacity of the list
size_t VSArray::GetCapacity()const {
    return _capacity;
}