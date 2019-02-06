//
// Created by miss on 2/3/19.
//

/*
 *  DAG图：在图论中，如果一个有向图无法从某个顶点出发经过若干条边回到该点，则这个图是一个有向无环图（DAG图）。

        题意
        有n种长宽高为x,y,z的砖头，每种都有无数个。

        砖头可以用不同姿势的方向来盖。

        砖头a以某种姿势可以盖在砖头b上，当且仅当a的底部的长宽都要比b的底部长宽要小。

        问最高可以建多高？

        思路

        对于一个x,y,z砖头，它可以有3中姿势放置。

         (前两个为地面，后一个为高)

        x, y, z

        x, z, y

        y, z, x

        把每种姿势都记录下来，变成了有3*n种固定姿势的砖头。

        然后建图，g[i][j] = true, 表示砖头i可以盖在砖头j上，反之亦然。

        然后就是求dag上的最长路了。

        注意每种砖头都可以取无线种
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
LL mod=1e9+7;
const int N=1005;

int n;
struct node
{
    int a,b,c;
}feng[33*3];
int G[33*3][33*3];// i可不可以放在j上
int dp[33*3];

int check(int i,int j)//判断 i可不可以放在j上
{
    if( (feng[i].a <feng[j].a && feng[i].b<feng[j].b) ||
        (feng[i].a < feng[j].b && feng[i].b<feng[j].a ) )
        return 1;
    else
        return 0;
}
int solve(int a)
{
    int &ans=dp[a];
    if(ans)
        return ans;
    ans=feng[a].c;
    for(int j=0; j<n; j++)
    {
        if( G[a][j]==1 )
            ans=max(ans, solve(j)+ feng[a].c);
    }
    return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
    //freopen("in.txt","r",stdin);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int kase=0;
    while(cin>>n,n)
    {
        int a,b,c;
        for(int i=0; i<n; i++) //一共有3*n种情况，每种可以取无限个
        {
            cin>>a>>b>>c;
            feng[i].a=a,feng[i].b=b,feng[i].c=c;
            feng[i+n].a=b,feng[i+n].b=c,feng[i+n].c=a;
            feng[i+2*n].a=c,feng[i+2*n].b=a,feng[i+2*n].c=b;
        }
        n*=3;
        memset(dp,0,sizeof(dp));
        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                G[i][j]= check(i,j);
                G[j][i]= check(j,i);
            }
        }
        int ans=0;
        for(int i=0; i<n; i++)
        {
            int temp=solve(i);
            ans=max(ans,temp);
        }
        cout<<"Case "<<++kase<<": maximum height = "<<ans<<endl;
    }
