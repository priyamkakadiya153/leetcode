import java.util.*;

class Solution {
    public int[][] divideArray(int[] nums, int k) {
        Arrays.sort(nums);
        int n = nums.length;
        List<int[]> result = new ArrayList<>();

        for (int i = 0; i < n; i += 3) {
            // Ensure group of 3 exists
            if (i + 2 >= n) return new int[0][];
            
            int a = nums[i], b = nums[i + 1], c = nums[i + 2];
            if (c - a <= k) {
                result.add(new int[]{a, b, c});
            } else {
                return new int[0][];
            }
        }
        return result.toArray(new int[result.size()][]);
    }
}
