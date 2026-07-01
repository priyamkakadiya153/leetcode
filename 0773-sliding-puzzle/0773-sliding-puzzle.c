int slidingPuzzle(int** board, int boardSize, int* boardColSize) {
    typedef struct { char s[7]; int step; } Node;

    char start[7], goal[] = "123450";
    int idx = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            start[idx++] = board[i][j] + '0';
    start[6] = '\0';

    // adjacency list for 0’s possible moves
    int adj[6][4] = {
        {1, 3, -1, -1}, {0, 2, 4, -1}, {1, 5, -1, -1},
        {0, 4, -1, -1}, {1, 3, 5, -1}, {2, 4, -1, -1}
    };

    Node q[720];              // BFS queue (6! = 720 states max)
    char vis[720][7];         // visited states
    int front = 0, rear = 0, visCount = 0;

    strcpy(q[rear].s, start);
    q[rear++].step = 0;
    strcpy(vis[visCount++], start);

    while (front < rear) {
        Node cur = q[front++];
        if (strcmp(cur.s, goal) == 0)
            return cur.step;

        int z = strchr(cur.s, '0') - cur.s;
        for (int k = 0; k < 4 && adj[z][k] != -1; k++) {
            int n = adj[z][k];
            char next[7];
            strcpy(next, cur.s);
            next[z] = next[n];
            next[n] = '0';

            int seen = 0;
            for (int i = 0; i < visCount; i++)
                if (strcmp(vis[i], next) == 0) { seen = 1; break; }
            if (seen) continue;

            strcpy(vis[visCount++], next);
            strcpy(q[rear].s, next);
            q[rear++].step = cur.step + 1;
        }
    }
    return -1;
}