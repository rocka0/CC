// https://github.com/rocka0/CC

vi topologicalSort(const vector<vi>& graph)
{
    int n = sz(graph);
    vi indegree(n);
    for (int i = 0; i < n; ++i) {
        for (auto& vertex : graph[i]) {
            ++indegree[vertex];
        }
    }
    // TODO: Use priority_queue for:
    // 1. priority_queue<int>: Lexicographically Maximal Answer
    // 2. priority_queue<int, vi, greater<int>>: Lexicographically Minimal Answer
    queue<int> Q;
    vi ans;
    ans.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (!indegree[i]) {
            Q.push(i);
        }
    }
    while (!Q.empty()) {
        int vertex = Q.front();
        // TODO: Q.top() for Priority Queue
        Q.pop();
        ans.pb(vertex);
        for (auto& child : graph[vertex]) {
            if (--indegree[child] == 0) {
                Q.push(child);
            }
        }
    }
    // TODO: sz(ans) != n in case of cycle
    return ans;
}