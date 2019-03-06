//
// Created by miss on 3/6/19.
//
//欧拉回路是指不重复的走过所有路径的回路，而哈密尔顿环是指不重复地走过所有的点，并且最后还能回到起点的回路。使用简单的深度优先搜索，就能求出一张图中所有的哈密尔顿环


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <vector>

using namespace std;


int start, length, x, n;
bool visited[101], v1[101];
int ans[101], num[101];
int g[101][101];

void print() {
    int i;
    for (i = 1; i <= length - 1; i++)cout << ans[i] << ' ';
    cout << ans[length] << endl;
}

void dfs(int last, int i)  //图用数组模拟邻接表存储，访问点i，last表示上次访问的点
{
    visited[i] = 1;       //标记为已经访问过
    v1[i] = 1;              //标记为已在一张图中出现过
    ans[length++] = i;      //记录下答案
    for (int j = 1; j <= num[i]; j++) {
        if (g[i][j] == x && g[i][j] != last) {   //回到起点构成哈密顿环
            ans[++length] = g[i][j];
            print(); //这里说明找到了一个环，则输出ans数组
            length--;
            break;
        }
        if (!visited[g[i][j]])
            dfs(i, g[i][j]); //遍历与i相关联的所有未访问的点。
    }
    length--;
    visited[i] = 0;//回溯的过程，注意v1不能回溯
}

int main() {
    memset(visited, 0, sizeof(visited));
    memset(v1, 0, sizeof(v1));
    cin >> n;
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        g[x][++num[x]] = y;
        g[y][++num[y]] = x;

    }

    for (x = 1; x <= n; x++) //每一个点都作为起点来尝试访问，因为不是从任何一点开始都能找过整个图
    {
        if (!v1[x])  //如果点x不在之前曾经被访问过的图里
        {
            length = 0;   //定义一个ans数组存答案，length记答案的长度
            dfs(0, x);
        }
    }
    return 0;