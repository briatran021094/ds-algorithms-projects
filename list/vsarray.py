from typing import Optional, List

class Object:
    """
    Abstract base class for all objects stored in VSArray.
    """

    def Equals(self, other: 'Object') -> bool:
        """
        Compare this object with another object for equality.
        Parameters: The object to compare with.
        Returns: True if equal, otherwise False.
        """
        raise NotImplementedError()

    def ToString(self) -> str:
        """
        Return a string representation of the object.
        Returns: String representation.
        """
        raise NotImplementedError()


class VSArray:
    """
    A resizable dynamic array for storing Object-derived instances.
    Automatically resizes when capacity is reached.
    """

    def __init__(self, capacity: int = 10, increase_percentage: float = 0.5):
        """
        Initialize the array with a given capacity and growth strategy.

        Parameters: Initial capacity of the array. Default is 10.
            increase_percentage (float): Resize factor (e.g., 0.5 means grow by 50%). Can be >1 for fixed growth.
        """
        self._capacity = capacity
        self._delta = increase_percentage
        self._size = 0
        self._data: List[Optional[Object]] = [None] * self._capacity

    def __copy__(self):
        """
        Create a shallow copy of the array.
        Returns: A new array with copied references to the same objects.
        """
        copy = VSArray(self._capacity, self._delta)
        copy._size = self._size
        copy._data = self._data[:self._size] + [None] * (self._capacity - self._size)
        return copy

    def __eq__(self, rhs: 'VSArray') -> bool:
        """
        Check if two arrays are equal based on element values.sss
        Parameters: Another array to compare with.
        Returns: True if arrays are equal in size and content.
        """
        if self._size != rhs._size:
            return False
        return all(self._data[i].Equals(rhs._data[i]) for i in range(self._size))

    def assign(self, rhs: 'VSArray') -> 'VSArray':
        """
        Assign the contents of another array to this one.
        Parameters: Array to copy from.
        Returns: Self, with updated data.
        """
        if self is not rhs:
            self.Clear()
            self._size = rhs._size
            self._delta = rhs._delta
            self._capacity = rhs._capacity
            self._data = rhs._data[:self._size] + [None] * (self._capacity - self._size)
        return self

    def Resize(self):
        """
        Resize the array when capacity is full.
        Uses either percentage growth or fixed-size growth based on delta.
        """
        if 0 < self._delta <= 1:
            new_capacity = int(self._capacity * (1 + self._delta))
        else:
            new_capacity = self._capacity + int(self._delta)

        new_data = self._data[:self._size] + [None] * (new_capacity - self._size)
        self._data = new_data
        self._capacity = new_capacity

    def Insert(self, element: Object, position: int) -> bool:
        """
        Insert an object at a specific position in the array.
        Parameters: The object to insert.
                    The index at which to insert.
        Returns: True if insertion succeeded, False if invalid position or None element.
        """
        if position > self._size or element is None:
            return False
        if self._size == self._capacity:
            self.Resize()

        # Extend size and shift elements to the right
        self._data[self._size:self._size + 1] = [None]
        for i in range(self._size, position, -1):
            self._data[i] = self._data[i - 1]

        self._data[position] = element
        self._size += 1
        return True

    def IndexOf(self, element: Object) -> int:
        """
        Find the index of the first occurrence of an object.
        Parameters: The object to find.
        Returns: Index if found, -1 if not found or element is None.
        """
        if element is None:
            return -1
        for i in range(self._size):
            if self._data[i] and self._data[i].Equals(element):
                return i
        return -1

    def Remove(self, position: int) -> Optional[Object]:
        """
        Remove an object from a specified position.
        Parameters: Index to remove from.
        Returns: The removed object, or None if index invalid.
        """
        if position >= self._size:
            return None

        removed = self._data[position]

        # Shift elements left
        for i in range(position, self._size - 1):
            self._data[i] = self._data[i + 1]

        self._data[self._size - 1] = None
        self._size -= 1
        return removed

    def Get(self, position: int) -> Optional[Object]:
        """
        Get the object at a specific position.
        Parameters: Index to retrieve.
        Returns: The object at the position, or None if out of bounds.
        """
        if position >= self._size:
            return None
        return self._data[position]

    def ToString(self) -> str:
        """
        Get a string representation of the array and its contents.
        Returns: String version of the array.
        """
        if self._size == 0:
            return "{}"
        return "{" + ", ".join(self._data[i].ToString() for i in range(self._size)) + "}"

    def Clear(self):
        """
        Remove all elements from the array.
        """
        for i in range(self._size):
            self._data[i] = None
        self._size = 0

    def GetCapacity(self) -> int:
        """
        Get the current capacity of the array.
        Returns: Capacity of internal array.
        """
        return self._capacity