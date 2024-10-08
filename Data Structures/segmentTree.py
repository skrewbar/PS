from math import log2, ceil

class SegmentTree:
    def _init(self, tree: list[int], array: list[int], node: int, start: int, end: int) -> None:
        if start == end:
            tree[node] = array[start]
        else:
            self._init(tree, array, node*2, start, (start+end)//2)
            self._init(tree, array, node*2+1, (start+end)//2+1, end)
            tree[node] = tree[node*2] + tree[node*2+1]
        
    def __init__(self, array: list[int]) -> None:
        self.end = len(array) - 1
        height = ceil(log2(len(array)))
        self.tree = [0] * (1 << (height + 1))
        
        self._init(self.tree, array, 1, 0, self.end)
    
    
    def _updateTree(self, tree: list[int], node: int, start: int, end: int, index: int, value: int) -> None:
        if index < start or end < index:
            return
        if start == end:
            tree[node] = value
            return
        self._updateTree(tree, node*2, start, (start+end)//2, index, value)
        self._updateTree(tree, node*2+1, (start+end)//2+1, end, index, value)
        tree[node] = tree[node*2] + tree[node*2+1]
    
    def updateTree(self, index, value):
        self._updateTree(self.tree, 1, 0, self.end, index-1, value)
    
    
    def _getRangeSum(self, tree: list[int], node: int, start: int, end: int, left: int, right: int) -> int:
        if right < start or end < left:
            return 0
        if left <= start and end <= right:
            return tree[node]
        lsum = self._getRangeSum(tree, node*2, start, (start+end)//2, left, right)
        rsum = self._getRangeSum(tree, node*2+1, (start+end)//2+1, end, left, right)
        return lsum + rsum
    
    def getRangeSum(self, left: int, right: int) -> int:
        return self._getRangeSum(self.tree, 1, 0, self.end, left-1, right-1)

# tree = SegmentTree([1, 2, 3, 4, 5])
# print(tree.getRangeSum(1, 4))
# tree.updateTree(2, 4)
# print(tree.getRangeSum(2, 3))