class Solution(object):
    def splitArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)

        # Sieve of Eratosthenes to mark prime indices
        is_prime = [False, False] + [True] * (n - 2)
        p = 2
        while p * p < n:
            if is_prime[p]:
                for multiple in range(p * p, n, p):
                    is_prime[multiple] = False
            p += 1

        sum_A = 0
        sum_B = 0

        for i in range(n):
            if is_prime[i]:
                sum_A += nums[i]
            else:
                sum_B += nums[i]
        return abs(sum_A - sum_B)
