from typing import Generic, TypeVar, runtime_checkable, Protocol, Iterable
from copy import deepcopy


@runtime_checkable
class Comparable(Protocol):
    def __lt__(self, other: object) -> bool: ...
    def __gt__(self, other: object) -> bool: ...


T = TypeVar("T", bound=Comparable)


class PriorityQueue(Generic[T]):
    heap: list[T]

    def __init__(self, data: Iterable[T] | None = None) -> None:
        if data is None:
            self.heap = []
        else:
            self.heap = list(deepcopy(data))

        n = len(self.heap)
        for i in range((n >> 1) - 1, -1, -1):
            now = i
            while True:
                best = now
                left = (now << 1) + 1
                right = (now << 1) + 2

                if left < n and self.heap[best] < self.heap[left]:
                    best = left
                if right < n and self.heap[best] < self.heap[right]:
                    best = right

                if best == now:
                    break
                else:
                    self.heap[best], self.heap[now] = self.heap[now], self.heap[best]
                    now = best

    def push(self, x: T) -> None:
        now = len(self.heap)
        self.heap.append(x)

        while (parent := (now - 1) >> 1) >= 0:
            if self.heap[parent] < self.heap[now]:
                self.heap[parent], self.heap[now] = self.heap[now], self.heap[parent]
                now = parent
            else:
                break

    def pop(self) -> T:
        if not self.heap:
            raise IndexError("pop from empty PriorityQueue")

        ret = self.heap[0]
        self.heap[0] = self.heap.pop()

        now = 0
        n = len(self.heap)
        while True:
            best = now
            left = (now << 1) + 1
            right = (now << 1) + 2

            if left < n and self.heap[best] < self.heap[left]:
                best = left
            if right < n and self.heap[best] < self.heap[right]:
                best = right

            if best == now:
                break
            else:
                self.heap[best], self.heap[now] = self.heap[now], self.heap[best]
                now = best

        return ret
