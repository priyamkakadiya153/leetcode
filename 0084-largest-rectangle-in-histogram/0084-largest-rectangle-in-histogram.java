class Solution {
    public int largestRectangleArea(int[] heights) {

        int n = heights.length;

        int[] left = new int[n];
        int[] right = new int[n];

        Stack<Integer> st = new Stack<>();

        // Next Smaller to Left
        for (int i = 0; i < n; i++) {

            while (!st.isEmpty() && heights[st.peek()] >= heights[i]) {
                st.pop();
            }

            if (st.isEmpty()) {
                left[i] = -1;
            } else {
                left[i] = st.peek();
            }

            st.push(i);
        }

        st.clear();

        // Next Smaller to Right
        for (int i = n - 1; i >= 0; i--) {

            while (!st.isEmpty() && heights[st.peek()] >= heights[i]) {
                st.pop();
            }

            if (st.isEmpty()) {
                right[i] = n;
            } else {
                right[i] = st.peek();
            }

            st.push(i);
        }

        int maxArea = 0;

        for (int i = 0; i < n; i++) {

            int width = right[i] - left[i] - 1;
            int area = heights[i] * width;

            maxArea = Math.max(maxArea, area);
        }
        return maxArea;
    }
}