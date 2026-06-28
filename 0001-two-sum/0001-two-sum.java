import java.util.HashMap;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        // Map to store number and its index
        HashMap<Integer, Integer> map = new HashMap<>();

        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            // If complement exists in map, return the pair of indices
            if (map.containsKey(complement)) {
                return new int[] { map.get(complement), i };
            }
            // Store current number with its index
            map.put(nums[i], i);
        }

        // As per problem, there is always exactly one solution
        return new int[0]; 
    }
}
