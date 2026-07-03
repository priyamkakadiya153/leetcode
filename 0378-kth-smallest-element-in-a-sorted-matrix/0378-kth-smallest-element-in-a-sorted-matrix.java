class Solution {
    public int kthSmallest(int[][] matrix, int k) {

        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> {
            int r1 = a[0], c1 = a[1];
            int r2 = b[0], c2 = b[1];
            int val1 = matrix[r1][c1];
            int val2 = matrix[r2][c2];
            return val1 - val2;
        });

        int n = matrix.length;

        // add first element of every row
        for (int i = 0; i < n; i++) {
            pq.offer(new int[]{i, 0});
        }

        while (k > 1) {
            int[] curr = pq.poll();
            int r = curr[0];
            int c = curr[1];

            if (c + 1 < n) {
                pq.offer(new int[]{r, c + 1});
            }

            k--;
        }
        int[] ans = pq.poll();
        return matrix[ans[0]][ans[1]];
    }
}