int searchInsert(int* nums, int numsSize, int target) {
    int lo = 0, hi = numsSize - 1;
    int ans = numsSize;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] >= target) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    return ans;
}