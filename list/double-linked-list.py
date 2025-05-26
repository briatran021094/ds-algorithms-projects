class Node:
    def __init__(self, data, prev=None, next=None):
        # Node stores the actual data and pointers to the previous and next nodes in the list
        self.data = data
        self.prev = prev
        self.next = next


class DoubleLinkedList:
    def __init__(self):
        # Initialize an empty list with head and tail set to None, and size set to 0
        self._head: Node | None = None
        self._tail: Node | None = None
        self._size: int = 0

    def __copy__(self):
        """
        Creates a deep copy of the list by duplicating each node's data
        into a new DoubleLinkedList instance.
        """
        new_list = DoubleLinkedList()
        current = self._head
        while current:
            new_list.insert(current.data.copy(), new_list._size)
            current = current.next
        return new_list

    def __eq__(self, other):
        """
        Checks equality between two doubly linked lists by comparing
        the data in each corresponding node.
        Returns False if the other object is not a DoubleLinkedList or if
        any node's data does not match.
        """
        if not isinstance(other, DoubleLinkedList):
            return False

        a = self._head
        b = other._head

        while a and b:
            if not a.data.equals(b.data):
                return False
            a = a.next
            b = b.next

        # Both pointers should reach the end simultaneously
        return a is None and b is None

    def insert(self, element, position: int) -> bool:
        """
        Inserts a new node with the given element at the specified position.
        Returns True if successful, False if the element is None or the position is invalid.
        Handles all edge cases: empty list, front, end, and middle insertion.
        """
        if position > self._size or element is None:
            return False

        new_node = Node(element)

        if self._size == 0:
            # Insert into an empty list
            self._head = self._tail = new_node

        elif position == 0:
            # Insert at the front
            new_node.next = self._head
            self._head.prev = new_node
            self._head = new_node

        elif position == self._size:
            # Insert at the end
            new_node.prev = self._tail
            self._tail.next = new_node
            self._tail = new_node

        else:
            # Insert in the middle
            current = self._head
            for _ in range(position):
                current = current.next

            new_node.prev = current.prev
            new_node.next = current

            if current.prev:
                current.prev.next = new_node
            current.prev = new_node

        self._size += 1
        return True

    def index_of(self, element) -> int:
        """
        Searches for the first occurrence of an element in the list.
        Compares using the element’s .equals() method.
        Returns the index if found, or -1 if not found.
        """
        index = 0
        current = self._head

        while current:
            if current.data.equals(element):
                return index
            current = current.next
            index += 1

        return -1

    def remove(self, position: int):
        """
        Removes and returns the data of the node at the specified position.
        Returns None if the position is invalid.
        Handles removal from front, end, and middle.
        """
        if position >= self._size or position < 0:
            return None

        if position == 0:
            # Remove from front
            tmp = self._head
            self._head = tmp.next
            if self._head:
                self._head.prev = None
            if tmp == self._tail:  # Only one element in the list
                self._tail = None

        elif position == self._size - 1:
            # Remove from end
            tmp = self._tail
            self._tail = tmp.prev
            if self._tail:
                self._tail.next = None
            if tmp == self._head:
                self._head = None

        else:
            # Remove from middle
            tmp = self._head
            for _ in range(position):
                tmp = tmp.next
            tmp.prev.next = tmp.next
            tmp.next.prev = tmp.prev

        removed = tmp.data
        self._size -= 1
        return removed

    def get(self, position: int):
        """
        Returns the data of the node at the specified index.
        Returns None if the index is out of bounds.
        """
        if position >= self._size or position < 0:
            return None

        current = self._head
        for _ in range(position):
            current = current.next

        return current.data

    def to_string(self) -> str:
        """
        Returns a human-readable string representation of the list
        """
        elements = []
        current = self._head
        while current:
            elements.append(str(current.data))
            current = current.next
        return "{" + ", ".join(elements) + "}"

    def clear(self):
        """
        Clears the list by deallocating all nodes and resetting head, tail, and size.
        """
        current = self._head
        while current:
            next_node = current.next
            del current.data  # Optional cleanup
            del current
            current = next_node

        self._head = None
        self._tail = None
        self._size = 0