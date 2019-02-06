//
// Created by miss on 2/3/19.
//

// 矩形嵌套

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
LL mod=1e9+7;
const int N=1005;

int a[N],b[N],dp[N];
int n;
int G[N][N];
int solve(int a)
{
    int &ans=dp[a]; //记忆化关键
    if(ans)
        return ans;
    ans=1;
    for(int j=0; j<n; j++)
    {
        if(j!=a && G[a][j]==1)
        {
            ans=max(ans, solve(j)+1);
        }
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
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n;
        memset(G,0,sizeof(G));
        memset(dp,0,sizeof(dp));
        for(int i=0; i<n; i++)
        {
            cin>>a[i]>>b[i];
        }
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(j!=i && ( (a[j]<a[i] && b[j]<b[i]) || ( a[j]<b[i] && a[i]>b[j]) ) )//判断i是否可以套j
                {
                    G[i][j]=1;
                }
            }
        }
        int ans=0;
        for(int i=0; i<n; i++)
        {
            int temp=solve(i);
            ans=max(ans,temp);
        }
        cout<<ans<<endl;
    }
}