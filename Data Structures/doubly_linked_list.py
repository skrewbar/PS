from typing import TypeVar, Generic, Iterable, Self

T = TypeVar("T")


class ListNode(Generic[T]):
    def __init__(self, value: T, prev: Self | None, next_: Self | None):
        self.value = value
        self.prev = prev
        self.next = next_

    def __del__(self):
        if self.prev is not None:
            self.prev.next = self.next
        if self.next is not None:
            self.next.prev = self.prev


class LinkedList(Generic[T]):
    def __init__(self, iterable: Iterable[T] = None):
        self.head: ListNode[T] = None
        self.tail: ListNode[T] = None

        if iterable is not None:
            for i in iterable:
                self.append(i)

    def __str__(self):
        return f"LinkedList([{", ".join(map(lambda x: str(x), self))}])"

    def append(self, value: T):
        if self.head is None:
            self.head = ListNode(value, None, None)
            self.tail = self.head
            return

        new = ListNode(value, self.tail, None)
        self.tail.next = new
        self.tail = new

    def appendleft(self, value: T):
        if self.head is None:
            self.head = ListNode(value, None, None)
            self.tail = self.head
            return

        new = ListNode(value, None, self.head)
        self.head.prev = new
        self.head = new

    def __iter__(self) -> Iterable[T]:
        self.iter = self.head
        return self

    def __next__(self) -> T:
        if self.iter is None:
            raise StopIteration
        ret = self.iter.value
        self.iter = self.iter.next
        return ret


linkedlist = LinkedList([1, 2, 3, 4])
print(linkedlist)
