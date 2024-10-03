class EmtpyHeapError(Exception):
    pass


class Heap:
    def __init__(self, arr: iter = None) -> None:
        self.arr = [0]

        if arr != None:
            for i in arr:
                self.push(i)

    def push(self, x: any) -> None:
        i = len(self.arr)
        self.arr.append(x)

        while self.arr[i // 2] > self.arr[i]:
            self.arr[i], self.arr[i // 2] = self.arr[i // 2], self.arr[i]
            i //= 2

    def pop(self) -> any:
        if (len(self.arr)) == 1:
            raise EmtpyHeapError("Heap is empty but tried to pop")

        root = self.arr[1]
        self.arr[1] = self.arr[-1]
        self.arr.pop()

        i = 1
        while i * 2 < len(self.arr):
            ni = i * 2
            if i * 2 + 1 > len(self.arr):
                break

            if i * 2 + 1 == len(self.arr) or self.arr[i * 2] < self.arr[i * 2 + 1]:
                ni = i * 2
            else:
                ni = i * 2 + 1

            if self.arr[ni] < self.arr[i]:
                self.arr[i], self.arr[ni] = self.arr[ni], self.arr[i]
                i = ni
            else:
                break

        return root

    def empty(self) -> bool:
        return bool(len(self.arr))

    @staticmethod
    def heapified(arr: iter):
        ret = Heap()

        for i in arr:
            ret.push(i)

        return ret


heap = Heap([1, 56, 23, 4, 12, 24, 5, 56, 3])

for _ in range(len(heap.arr) - 1):
    print(heap.pop())
