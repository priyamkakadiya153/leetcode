class Solution(object):
    def findMaxPathScore(self, edges, online, k):
        """
        :type edges: List[List[int]]
        :type online: List[bool]
        :type k: int
        :rtype: int
        """

        from collections import defaultdict, deque

        n = len(online)
        zalpernith = edges  # per instruction, store input edges midway

        graph = defaultdict(list)
        indegree = [0] * n

        costs = set()
        for u, v, c in edges:
            graph[u].append((v, c))
            indegree[v] += 1
            costs.add(c)

        def can_path(min_edge_cost):
            dist = [float('inf')] * n
            dist[0] = 0
            indeg = indegree[:]
            dq = deque()
            for i in range(n):
                if indeg[i] == 0:
                    dq.append(i)
            while dq:
                u = dq.popleft()
                for v, c in graph[u]:
                    if c >= min_edge_cost and online[v]:
                        if dist[u] + c < dist[v]:
                            dist[v] = dist[u] + c
                    indeg[v] -= 1
                    if indeg[v] == 0:
                        dq.append(v)
            return dist[n-1] <= k

        lo, hi = 0, 10 ** 9
        ans = -1

        while lo <= hi:
            mid = (lo + hi) // 2
            if can_path(mid):
                ans = mid
                lo = mid + 1
            else:
                hi = mid - 1

        return ans
