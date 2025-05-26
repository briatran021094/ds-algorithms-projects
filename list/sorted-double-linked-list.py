from double_linked_list import DoubleLinkedList, Node
from comparable import Comparable  # Interface that requires compare_to method


class SortedDoubleLinkedList(DoubleLinkedList):
    """
    A subclass of DoubleLinkedList that maintains its elements in sorted order.
    """

    def __init__(self):
        """
        Constructor: Initializes an empty sorted doubly linked list.
        Inherits attributes (_head, _tail, _size) from DoubleLinkedList.
        """
        super().__init__()

    def insert(self, element: Comparable) -> bool:
        """
        Inserts a Comparable element into the list such that the list
        remains in ascending sorted order.

        Parameters: The item to be inserted. Must support compare_to().
        Returns: True if insertion is successful, False if the element is None.
        """
        if element is None:
            return False  # Reject null elements

        # Create a new node to hold the element
        neo = Node(element)

        # Case 1: If the list is empty, the new node becomes both head and tail
        if not self._head:
            self._head = self._tail = neo

        else:
            tmp = self._head  # Start from the beginning of the list

            # Traverse until we find the insertion point
            # We stop at the first node whose data is not less than the new element
            while tmp and element.compare_to(tmp.data) > 0:
                tmp = tmp.next

            if not tmp:
                # Case 2: Reached the end of the list => insert at the tail
                neo.previous = self._tail
                self._tail.next = neo
                self._tail = neo

            elif not tmp.previous:
                # Case 3: Inserting before the current head => insert at the beginning
                neo.next = self._head
                self._head.previous = neo
                self._head = neo

            else:
                # Case 4: Inserting somewhere in the middle
                # Connect neo between tmp.previous and tmp
                neo.previous = tmp.previous
                neo.next = tmp
                tmp.previous.next = neo
                tmp.previous = neo

        # Increase the size of the list after successful insertion
        self._size += 1
        return True