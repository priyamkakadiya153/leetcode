import java.util.*;

public class Solution {

    // Function to check if a number is prime
    private boolean isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }

    // Main function to check if any element has a prime frequency
    public boolean checkPrimeFrequency(int[] nums) {
        Map<Integer, Integer> freqMap = new HashMap<>();
        
        // Count frequency of each element
        for (int num : nums) {
            freqMap.put(num, freqMap.getOrDefault(num, 0) + 1);
        }

        // Check if any frequency is prime
        for (int count : freqMap.values()) {
            if (isPrime(count)) {
                return true;
            }
        }
        return false;
    }
}
