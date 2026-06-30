#include <stdlib.h>
#include <string.h>

void solve(int r, int n, char** b, int* c, int* d1, int* d2, char**** s, int* rs, int* cap) {
    if (r == n) {
        // Fix: realloc with sizeof(char**)
        if (*rs >= *cap) *s = realloc(*s, (*cap *= 2) * sizeof(char**));
        
        char** board = malloc(n * sizeof(char*));
        for (int i = 0; i < n; i++) {
            board[i] = malloc(n + 1);
            memcpy(board[i], b[i], n + 1);  // faster than strcpy
        }
        (*s)[(*rs)++] = board;
        return;
    }
    for (int col = 0; col < n; col++) {
        int idx1 = r - col + n - 1, idx2 = r + col;
        if (!c[col] && !d1[idx1] && !d2[idx2]) {
            b[r][col] = 'Q';
            c[col] = d1[idx1] = d2[idx2] = 1;
            solve(r + 1, n, b, c, d1, d2, s, rs, cap);
            b[r][col] = '.';
            c[col] = d1[idx1] = d2[idx2] = 0;
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    int capacity = 8;
    char*** solutions = malloc(capacity * sizeof(char**));
    
    char** board = malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        board[i] = malloc(n + 1);
        memset(board[i], '.', n);
        board[i][n] = '\0';
    }
    
    int* cols = calloc(n, sizeof(int));
    int* diag1 = calloc(2 * n - 1, sizeof(int));
    int* diag2 = calloc(2 * n - 1, sizeof(int));
    
    solve(0, n, board, cols, diag1, diag2, &solutions, returnSize, &capacity);
    
    for (int i = 0; i < n; i++) free(board[i]);
    free(board);
    free(cols);
    free(diag1);
    free(diag2);
    
    *returnColumnSizes = malloc(*returnSize * sizeof(int));
    for (int i = 0; i < *returnSize; i++) (*returnColumnSizes)[i] = n;
    
    return solutions;
}
