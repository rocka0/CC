#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://github.com/rocka0/CC

    Usage:  topologicalSort(vector<vector<int>> adj) returns vector<int> ans

    Note:   ans.size() < n in case of cycle
*/

vector<int> topologicalSort(const vector<vector<int>>& graph)
{
    int n = int(graph.size());
    vector<int> indegree(n);

    for (int i = 0; i < n; ++i) {
        for (auto& vertex : graph[i]) {
            ++indegree[vertex];
        }
    }

    /*
        NOTE: Use:
        1. priority_queue<int>: Lexicographically Maximal Answer
        2. priority_queue<int, vector<int>, greater<int>>: Lexicographically Minimal Answer
    */
    queue<int> Q;

    vector<int> ans;
    ans.reserve(n);

    for (int i = 0; i < n; ++i) {
        if (!indegree[i]) {
            Q.push(i);
        }
    }

    while (!Q.empty()) {
        int vertex = Q.front();

        // NOTE: Q.top() for Priority Queue
        Q.pop();

        ans.push_back(vertex);

        for (auto& child : graph[vertex]) {
            if (--indegree[child] == 0) {
                Q.push(child);
            }
        }
    }

    return ans;
}