class DynamicSegmentTree:
    """
    Dynamic Segment Tree

    It's based on segment tree but nodes are allocated dynamically.
    If the tree is modified N times, then the memory complexity is O(N).
    """

    class Node:
        left: "DynamicSegmentTree.Node | None"
        right: "DynamicSegmentTree.Node | None"
        value: int

        def __init__(self, value: int):
            self.left = None
            self.right = None
            self.value = value

    def __init__(self, size: int):
        self.root = DynamicSegmentTree.Node(0)
        self.size = size

    def modify(self, index: int, value: int):
        """Modify the value at index to `value`"""
        self._modify(self.root, 0, self.size - 1, index, value)

    def _modify(
        self,
        node: "DynamicSegmentTree.Node",
        start: int,
        end: int,
        index: int,
        value: int,
    ):
        if start == end:
            node.value = value
            return

        mid = (start + end) >> 1
        if index <= mid:
            if node.left is None:
                node.left = DynamicSegmentTree.Node(0)
            self._modify(node.left, start, mid, index, value)
        else:
            if node.right is None:
                node.right = DynamicSegmentTree.Node(0)
            self._modify(node.right, mid + 1, end, index, value)

        node.value = 0
        if node.left is not None:
            if node.left.value == 0:
                node.left = None
            else:
                node.value += node.left.value
        if node.right is not None:
            if node.right.value == 0:
                node.right = None
            else:
                node.value += node.right.value

    def get(self, index: int):
        """Return the value at index"""
        return self._get(self.root, 0, self.size - 1, index)

    def _get(
        self, node: "DynamicSegmentTree.Node", start: int, end: int, index: int
    ) -> int:
        if start == end:
            return node.value

        mid = (start + end) >> 1
        if index <= mid:
            if node.left is None:
                return 0
            return self._get(node.left, start, mid, index)
        else:
            if node.right is None:
                return 0
            return self._get(node.right, mid + 1, end, index)

    def get_range(self, left: int, right: int):
        """Return the range sum of values for indices in range [left, right]"""
        return self._get_range(self.root, 0, self.size - 1, left, right)

    def _get_range(
        self,
        node: "DynamicSegmentTree.Node",
        start: int,
        end: int,
        left: int,
        right: int,
    ) -> int:
        if right < start or end < left:
            return 0
        if left <= start and end <= right:
            return node.value

        mid = (start + end) >> 1
        ret = 0
        if node.left is not None:
            ret += self._get_range(node.left, start, mid, left, right)
        if node.right is not None:
            ret += self._get_range(node.right, mid + 1, end, left, right)
        return ret

    def get_kth(self, k: int):
        """Return the index of the k-th element"""
        return self._get_kth(self.root, 0, self.size - 1, k)

    def _get_kth(
        self, node: "DynamicSegmentTree.Node", start: int, end: int, k: int
    ) -> int | None:
        if start == end:
            if node.value:
                return start

        mid = (start + end) >> 1

        if node.left is not None and k <= node.left.value:
            return self._get_kth(node.left, start, mid, k)
        else:
            if node.right is None:
                return None
            if node.left is not None:
                k -= node.left.value
            return self._get_kth(node.right, mid + 1, end, k)


class OrderStatisticTree:
    """
    Order Statistic Tree

    This is an implementation of tree-based set.
    This tree provides O(log N) operations such as add, remove, binary search, etc.
    """

    def __init__(self, min_value: int = -(1 << 31), max_value: int = (1 << 31) - 1):
        self.min = min_value
        self.tree = DynamicSegmentTree(max_value - min_value + 1)

    def add(self, x: int):
        """Add x to the tree"""
        self.tree.modify(x - self.min, 1)

    def remove(self, x: int):
        """Remove x from the tree"""
        self.tree.modify(x - self.min, 0)

    def __contains__(self, x: int):
        return bool(self.tree.get(x - self.min))

    def get_kth(self, k: int):
        """Return k-th smallest element"""

        if k <= 0:
            return None

        kth = self.tree.get_kth(k)
        if kth is not None:
            return kth + self.min
        return kth

    def rank(self, x: int):
        """Return the count of elements in the tree such that element <= x"""
        return self.tree.get_range(0, x - self.min)

    def lower_bound(self, x: int):
        """Return the smallest element such that x <= element"""
        return self.get_kth(self.rank(x - 1) + 1)

    def upper_bound(self, x: int):
        """Return the smallest element such that x < element"""
        return self.get_kth(self.rank(x) + 1)

    def predecessor(self, x: int):
        """Return the largest element such that element < x"""
        return self.get_kth(self.rank(x - 1))

    def successor(self, x: int):
        """Return the smallest element such that x < element"""
        return self.get_kth(self.rank(x) + 1)

    def __len__(self):
        return self.tree.root.value

    def __iter__(self):
        # TODO: optimize to O(N) by traversing segment tree in-order
        self.cur = 1
        return self

    def __next__(self):
        if self.cur <= len(self):
            ret = self.get_kth(self.cur)
            self.cur += 1
            return ret
        raise StopIteration
