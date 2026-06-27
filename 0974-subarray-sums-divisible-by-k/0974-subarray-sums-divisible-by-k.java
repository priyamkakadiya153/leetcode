class Solution {
    public int subarraysDivByK(int[] nums, int k) {
        int sum = 0, count = 0;

        int[] freq = new int[k];
        freq[0] = 1;

        for (int i = 0; i < nums.length; i++) {
            sum += nums[i];
            int r = ((sum % k) + k) % k; // Handle negative sums
            count += freq[r]; // Add previous occurrences of this remainder
            freq[r]++; // Increment frequency of this remainder
        }
        return count;
    }
}