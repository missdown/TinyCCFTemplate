//
// Created by miss on 3/6/19.
//

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string.h>
#include<algorithm>
#include<vector>

using namespace std;

const int N = 1005;
int n, m, flag, top, sum, du[N], ans[5005], map[N][N];

void dfs(int x) {
    ans[++top] = x;
    for (int i = 1; i <= n; i++) {
        if (map[x][i] >= 1) {
            map[x][i]--;
            map[i][x]--;
            dfs(i);
            break;
        }
    }
}

void fleury(int x) {
    top = 1;
    ans[top] = x;
    while (top > 0) {
        int k = 0;
        for (int i = 1; i <= n; i++)//判断是否可扩展
        {
            if (map[ans[top]][i] >= 1)//若存在一条从ans[top]出发的边  那么就是可扩展
            {
                k = 1;
                break;
            }
        }
        if (k == 0)//该点x没有其他的边可以先走了（即不可扩展）， 那么就输出它
        {
            printf("%d ", ans[top]);
            top--;
        } else if (k == 1)//如可扩展， 则dfs可扩展的哪条路线
        {
            top--;//这需要注意
            dfs(ans[top + 1]);
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(du, 0, sizeof(du));
        memset(map, 0, sizeof(map));

        for (int i = 1; i <= m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            map[x][y]++; //记录边， 因为是无向图所以加两条边， 两个点之间可能有多条边
            map[y][x]++;
            du[x]++;
            du[y]++;
        }
        flag = 1; // flag标记开始点。 如果所有点度数全为偶数那就从1开始搜
        sum = 0;
        for (int i = 1; i <= n; i++) {
            if (du[i] % 2 == 1) {
                sum++;
                flag = i;// 若有奇数边， 从奇数边开始搜
            }
        }
        if (sum == 0 || sum == 2)
            fleury(flag);
    }
    return 0;
}


/*
 *
 * Method 2
 *
 */

#include<bits/stdc++.h>

using namespace std;
const int N = 1025;
multiset<int> to[N];
int len[N];
int road[N], k;

void dfs(int x) {
    for (auto a = to[x].begin(); a != to[x].end(); a = to[x].begin()) {//auto类型为C++11标准，可进行自动类型推断
        int u = *a;
        to[x].erase(a);
        to[u].erase(to[u].find(x));//删边
        dfs(u);//递归
    }
    road[k++] = x;//往答案队列里插入答案
}

int main() {
    int m, a, b;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        len[a]++, len[b]++;
        to[a].insert(b);
        to[b].insert(a);
    }
    int s = -1, e = -1;//起点与终点
    for (int i = 1; i <= 1024; i++)
        if (len[i] % 2 == 1) {
            if (s == -1)s = i;
            else if (e == -1)e = i;
            else exit(1);
        }//判断每个点的度数
    if (s == -1)s = 1;
    dfs(s);//开始递归
    for (k = k - 1; k >= 0; k--)
        printf("%d\n", road[k]);//倒序输出答案
    return 0;
}