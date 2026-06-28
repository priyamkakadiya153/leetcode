int search(int A[], int n, int target)

{
    int low = 0;
    int high = n - 1;

    while (low <= high) 
    {
        int mid = (low + high) / 2;

        if (A[mid] == target) 
        {
            return mid;
        }

        if (A[mid] > target) 
        {
            high = mid - 1;
        }

        if (A[mid] < target) 
        {
            low = mid + 1;
        }
    }
    return -1;
}
