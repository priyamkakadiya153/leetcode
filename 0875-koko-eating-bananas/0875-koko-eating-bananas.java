class Solution {
    public int minEatingSpeed(int[] piles, int h) {
        int l = 1, r = (int)1e9, ans = -1;

        while (l <= r) {
            int mid = (l + r) / 2;

            if (canEatInTime(piles, mid, h)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        return ans;
    }

    public boolean canEatInTime(int[] piles, int k, int h) {
    long hours = 0;

    for (int i = 0; i < piles.length; i++) {
        hours += piles[i] / k;

        if (piles[i] % k != 0) {
            hours++;
        }
    }

    return hours <= h;
    }
}