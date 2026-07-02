class Solution(object):
    def countIslands(self, grid, k):
        """
        :type grid: List[List[int]]
        :type k: int
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        visited = [[False] * n for _ in range(m)]
        res = 0

        def dfs(i, j):
            stack = [(i, j)]
            total = 0
            visited[i][j] = True
            while stack:
                x, y = stack.pop()
                total += grid[x][y]
                for dx, dy in [(-1,0),(1,0),(0,-1),(0,1)]:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] > 0 and not visited[nx][ny]:
                        visited[nx][ny] = True
                        stack.append((nx, ny))
            return total

        for i in range(m):
            for j in range(n):
                if grid[i][j] > 0 and not visited[i][j]:
                    total = dfs(i, j)
                    if total % k == 0:
                        res += 1

        return res
