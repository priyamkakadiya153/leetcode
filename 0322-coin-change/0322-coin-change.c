#include <stdlib.h>

int coinChange(int* coins, int coinsSize, int amount) {
    if (amount == 0) return 0;  // No coins needed for amount 0
    if (coinsSize == 0) return -1; // No coins available

    // Allocate DP array
    int *dp = (int*) malloc((amount + 1) * sizeof(int));
    if (!dp) return -1;  // Memory allocation failure

    // Initialize dp array with a sentinel value (amount+1, which is impossible)
    for (int i = 0; i <= amount; i++) {
        dp[i] = amount + 1;
    }
    dp[0] = 0; // base case

    // Build up the dp table
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < coinsSize; j++) {
            if (coins[j] <= i) {
                int candidate = dp[i - coins[j]] + 1;
                if (candidate < dp[i]) {
                    dp[i] = candidate;
                }
            }
        }
    }

    int result = (dp[amount] > amount) ? -1 : dp[amount];
    free(dp);
    return result;
}