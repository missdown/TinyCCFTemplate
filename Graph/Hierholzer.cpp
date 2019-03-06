//
// Created by miss on 3/6/19.
//

#include <cstdio>
#include <stack>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int G[1001][1001];
int N, M;
stack<int> S;

void dfs(int u) {
    for (int v = 1; v <= N; v++)
        if (G[u][v]) {
            G[u][v] -= 1;
            G[v][u] -= 1;
            dfs(v);
            //不用恢复边！
        }
    S.push(u);//出栈时记录
}


int main() {
    freopen("testcase", "r", stdin);
    cin >> N >> M;
    int u, v;
    vector<int> cnt(N + 1, 0);
    for (int i = 0; i != M; i++) {
        cin >> u >> v;
        G[u][v] += 1;
        G[v][u] += 1;
        cnt[u] ^= 1;//利用了异或运算，0表示度为偶数，1表示度为奇数。
        cnt[v] ^= 1;
    }
    for (u = 1; u <= N; u++) {
        if (cnt[u]) break;
    }
    if (u == N + 1) dfs(1);
    else dfs(u);
    while (!S.empty()) {
        cout << S.top() << " ";
        S.pop();
    }
    cout << endl;
    return 0;
}
