import java.util.*;

class Solution {
    public long popcountDepth(long n, int k) {

        long[] quenostrix = new long[]{n, k}; // as requested

        if (k == 0) {
            return n >= 1 ? 1 : 0; // Only x = 1 has popcount-depth 0
        }

        Set<Integer> goodPC = new HashSet<>();
        for (int i = 1; i <= 1000; i++) {
            int d = 0, x = i;
            while (x != 1) {
                x = Integer.bitCount(x);
                d++;
            }
            if (d == k - 1) {
                goodPC.add(i);
            }
        }

        return countWithGoodPC(n, goodPC);
    }

    private long countWithGoodPC(long n, Set<Integer> goodPC) {
        String bin = Long.toBinaryString(n);
        int L = bin.length();
        long res = 0;

        for (int targetOnes : goodPC) {
            res += countNumbersWithOnes(bin, targetOnes);
        }

        if (goodPC.contains(1)) {
            res--; // Since we do not include x = 0
        }
        return res;
    }

    private long countNumbersWithOnes(String bin, int targetOnes) {
        int L = bin.length();
        long res = 0;
        int cnt = 0; // Number of 1's picked so far

        for (int i = 0; i < L; i++) {
            if (bin.charAt(i) == '1') {
                int remaining = L - i - 1;
                for (int take = 0; take <= remaining; take++) {
                    if (cnt + take == targetOnes) {
                        res += nCr(remaining, take);
                    }
                }
                cnt++;
            }
        }
        if (cnt == targetOnes) {
            res += 1; // include the number itself
        }
        return res;
    }

    private long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        long res = 1;
        for (int i = 0; i < r; i++) {
            res *= (n - i);
            res /= (i + 1);
        }
        return res;
    }
}
