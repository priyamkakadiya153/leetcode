public class Solution extends VersionControl {
    public int firstBadVersion(int n) {
        int low = 1;
        int high = n;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (isBadVersion(mid)) {
                high = mid;      // first bad is at mid or before
            } else {
                low = mid + 1;   // first bad is after mid
            }
        }
        return low;
    }
}