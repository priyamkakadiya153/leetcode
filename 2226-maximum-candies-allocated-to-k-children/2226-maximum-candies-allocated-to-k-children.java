class Solution {
    public int maximumCandies(int[] candies, long k) {

        int l = 1;
        int r = 0;

        for (int candy : candies) {
            r = Math.max(r, candy);
        }

        int ans = 0;

        while (l <= r) {
            int mid = l + (r - l) / 2;

            if (canAllocate(candies, k, mid)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return ans;
    }

    private boolean canAllocate(int[] candies, long k, int mid) {

        long children = 0;

        for (int candy : candies) {
            children += candy / mid;
        }

        return children >= k;
    }
}