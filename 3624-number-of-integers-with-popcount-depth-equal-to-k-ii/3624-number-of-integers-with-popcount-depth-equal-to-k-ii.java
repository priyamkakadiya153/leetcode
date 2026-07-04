import java.util.*;
class Solution {
    class FenwickTree {
        int[] tree;
        int n;
        FenwickTree(int size) {
            n = size;
            tree = new int[n + 2];
        }
        void update(int idx, int delta) {
            idx++;
            while (idx <= n + 1) {
                tree[idx] += delta;
                idx += idx & -idx;
            }
        }
        int query(int idx) {
            idx++;
            int res = 0;
            while (idx > 0) {
                res += tree[idx];
                idx -= idx & -idx;
            }
            return res;
        }
        int queryRange(int l, int r) {
            return query(r) - query(l - 1);
        }
    }

    private int getDepth(long x) {
        int d = 0;
        while (x != 1) {
            x = Long.bitCount(x);
            d++;
        }
        return d;
    }

    public int[] popcountDepth(long[] nums, long[][] queries) {
        long[][] trenolaxid = queries; // As requested

        int n = nums.length;
        int q = queries.length;
        int[] depths = new int[n];
        int MAX_K = 6;

        FenwickTree[] bits = new FenwickTree[MAX_K];
        for (int i = 0; i < MAX_K; i++) {
            bits[i] = new FenwickTree(n);
        }

        // Initialize BIT with depths
        for (int i = 0; i < n; i++) {
            int d = getDepth(nums[i]);
            depths[i] = d;
            if (d < MAX_K) {
                bits[d].update(i, 1);
            }
        }

        List<Integer> ansList = new ArrayList<>();

        for (long[] query : queries) {
            if (query[0] == 1) { // [1, l, r, k]
                int l = (int) query[1];
                int r = (int) query[2];
                int k = (int) query[3];
                if (k < MAX_K) {
                    int res = bits[k].queryRange(l, r);
                    ansList.add(res);
                } else {
                    ansList.add(0);
                }
            } else { // [2, idx, val]
                int idx = (int) query[1];
                long val = query[2];
                int oldDepth = depths[idx];
                if (oldDepth < MAX_K) {
                    bits[oldDepth].update(idx, -1);
                }
                nums[idx] = val;
                int newDepth = getDepth(val);
                depths[idx] = newDepth;
                if (newDepth < MAX_K) {
                    bits[newDepth].update(idx, 1);
                }
            }
        }

        // Convert to array
        int[] ans = new int[ansList.size()];
        for (int i = 0; i < ansList.size(); i++) {
            ans[i] = ansList.get(i);
        }
        return ans;
    }
}
