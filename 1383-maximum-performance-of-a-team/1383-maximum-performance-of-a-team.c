#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MOD 1000000007LL

typedef struct {
    int s; // speed
    int e; // efficiency
} Eng;

static int cmp_desc_eff(const void *a, const void *b) {
    const Eng *x = (const Eng *)a, *y = (const Eng *)b;
    if (y->e != x->e) return (y->e - x->e);     // efficiency desc
    return (y->s - x->s);                        // optional: speed desc tie-break
}

/* --------- Min-heap for speeds --------- */
typedef struct {
    int *a;
    int size;
    int cap;
} MinHeap;

static void heap_swap(int *x, int *y) {
    int t = *x; *x = *y; *y = t;
}

static void heap_init(MinHeap *h, int cap) {
    h->a = (int *)malloc(sizeof(int) * (cap + 5));
    h->size = 0;
    h->cap = cap + 5;
}

static void heap_free(MinHeap *h) {
    free(h->a);
    h->a = NULL;
    h->size = h->cap = 0;
}

static void heap_up(MinHeap *h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->a[p] <= h->a[i]) break;
        heap_swap(&h->a[p], &h->a[i]);
        i = p;
    }
}

static void heap_down(MinHeap *h, int i) {
    while (1) {
        int l = 2*i + 1, r = 2*i + 2, m = i;
        if (l < h->size && h->a[l] < h->a[m]) m = l;
        if (r < h->size && h->a[r] < h->a[m]) m = r;
        if (m == i) break;
        heap_swap(&h->a[m], &h->a[i]);
        i = m;
    }
}

static void heap_push(MinHeap *h, int val) {
    if (h->size >= h->cap) { // grow if ever needed (rare)
        h->cap *= 2;
        h->a = (int *)realloc(h->a, sizeof(int) * h->cap);
    }
    h->a[h->size] = val;
    heap_up(h, h->size);
    h->size++;
}

static int heap_pop_min(MinHeap *h) {
    int ret = h->a[0];
    h->size--;
    if (h->size > 0) {
        h->a[0] = h->a[h->size];
        heap_down(h, 0);
    }
    return ret;
}

/* --------- Main function --------- */
int maxPerformance(int n, int* speed, int speedSize, int* efficiency, int efficiencySize, int k){
    (void)speedSize; (void)efficiencySize;

    Eng *arr = (Eng *)malloc(sizeof(Eng) * n);
    for (int i = 0; i < n; ++i) {
        arr[i].s = speed[i];
        arr[i].e = efficiency[i];
    }
    qsort(arr, n, sizeof(Eng), cmp_desc_eff);

    MinHeap heap;
    heap_init(&heap, k);
    long long sumSpeeds = 0;
    long long best = 0;

    for (int i = 0; i < n; ++i) {
        // add current speed
        heap_push(&heap, arr[i].s);
        sumSpeeds += arr[i].s;

        // keep only k speeds (remove smallest if overflow)
        if (heap.size > k) {
            int removed = heap_pop_min(&heap);
            sumSpeeds -= removed;
        }

        long long perf = sumSpeeds * (long long)arr[i].e;
        if (perf > best) best = perf;
    }

    heap_free(&heap);
    free(arr);

    return (int)(best % MOD);
}
