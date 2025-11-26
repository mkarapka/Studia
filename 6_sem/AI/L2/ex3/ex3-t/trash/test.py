import heapq
import numpy as np
priority_queue = []
heapq.heappush(priority_queue, (1, "A", "B"))
heapq.heappush(priority_queue, (3, "A", "A"))
heapq.heappush(priority_queue, (2, "A", "A"))

while priority_queue:
    print(heapq.heappop(priority_queue))

points = np.array([
    [1, 2],
    [4, 6],
    [7, 8],
    [2, 3]
])
g = np.array((1,6))

print(np.sum(np.abs(points - g), axis=1))
print(frozenset(p for p in points))
