#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
    struct LineKey {
        int A,B,C;
        bool operator==(LineKey const& o) const { return A==o.A && B==o.B && C==o.C; }
    };
    struct LineHash {
        size_t operator()(LineKey const& k) const {
            return ((uint64_t)(k.A*1000003LL + k.B)*1000003ULL + (uint64_t)(k.C+2000000007));
        }
    };
    struct SlopeKey {
        int A,B;
        bool operator==(SlopeKey const& o) const { return A==o.A && B==o.B; }
    };
    struct SlopeHash {
        size_t operator()(SlopeKey const& k) const {
            return (uint64_t)(k.A*1000003LL + k.B);
        }
    };
    static long long c2(long long x) { return x<2?0:x*(x-1)/2; }
public:
    int countTrapezoids(vector<vector<int>>& points) {
        vector<vector<int>> velmoranic = points;
        int n = points.size();
        if (n < 4) return 0;

        unordered_map<LineKey, unordered_set<int>, LineHash> linePts;
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                long long dx = points[j][0] - points[i][0];
                long long dy = points[j][1] - points[i][1];
                long long g = std::gcd(abs(dx), abs(dy));
                dx /= g; dy /= g;
                if (dx < 0 || (dx == 0 && dy < 0)) { dx = -dx; dy = -dy; }
                long long A = -dy, B = dx;
                long long g2 = std::gcd(abs(A), abs(B));
                if (g2) { A /= g2; B /= g2; }
                if (A < 0 || (A == 0 && B < 0)) { A = -A; B = -B; }
                long long C = A * points[i][0] + B * points[i][1];
                LineKey key{(int)A, (int)B, (int)C};
                auto& st = linePts[key];
                st.insert(i); st.insert(j);
            }
        }

        unordered_map<SlopeKey, vector<long long>, SlopeHash> slopeLineCounts;
        for (auto& kv : linePts) {
            long long cnt = kv.second.size();
            if (cnt >= 2) {
                SlopeKey sk{kv.first.A, kv.first.B};
                slopeLineCounts[sk].push_back(cnt);
            }
        }

        long long totalParallel = 0;
        for (auto& kv : slopeLineCounts) {
            auto& vec = kv.second;
            long long S = 0;
            for (long long c : vec) S += c2(c);
            long long pairSum = 0;
            for (long long c : vec) {
                long long v = c2(c);
                pairSum += v * (S - v);
            }
            totalParallel += pairSum / 2;
        }

        unordered_map<long long, vector<pair<int,int>>> mp;
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                long long sx = (long long)points[i][0] + points[j][0];
                long long sy = (long long)points[i][1] + points[j][1];
                long long key = (sx << 21) ^ (sy + 4000000LL);
                mp[key].push_back({i, j});
            }
        }

        auto col3 = [&](int a, int b, int c) {
            long long x1 = points[b][0] - points[a][0];
            long long y1 = points[b][1] - points[a][1];
            long long x2 = points[c][0] - points[a][0];
            long long y2 = points[c][1] - points[a][1];
            return x1 * y2 - x2 * y1 == 0;
        };

        long long parallelograms = 0;
        for (auto& kv : mp) {
            auto& vec = kv.second;
            int m = vec.size();
            if (m < 2) continue;
            for (int i = 0; i < m; ++i) {
                for (int j = i+1; j < m; ++j) {
                    auto [a, b] = vec[i];
                    auto [c, d] = vec[j];
                    if (a == c || a == d || b == c || b == d) continue;
                    bool allCol = col3(a, b, c) && col3(a, b, d);
                    if (!allCol) ++parallelograms;
                }
            }
        }

        long long res = totalParallel - parallelograms;
        if (res < 0) res = 0;
        return (int)res;
    }
};
