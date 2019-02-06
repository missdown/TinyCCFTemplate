//
// Created by miss on 2/2/19.
//

#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iomanip>
#include<queue>
#include<stack>
#include<vector>
#include<set>
#include<map>
using namespace std;
int a[1005];
int B[2005];
int n,m,Index,val,offset,lowext;
int Winner(int x,int y)
{
    if(a[x]>a[y])return y;
    else return x;
}
int Loser(int x,int y)
{
    if(a[x]>a[y])return x;
    else return y;
}
void Play(int father,int l,int r)
{
    int tmp1=0,tmp2=0;
    B[father]=Loser(l,r);
    tmp1=Winner(l,r);
    while(father>1&&father%2==1)
    {
        tmp2=Winner(tmp1,B[father/2]);
        B[father/2]=Loser(tmp1,B[father/2]);
        tmp1=tmp2;
        father/=2;
    }
    B[father/2]=tmp1;
}
void replay(int i)
{
    int father;
    if(i<=lowext)
        father=(i+offset)/2;
    else
        father=(i-lowext+n-1)/2;
    B[0]=Winner(i,B[father]);
    B[father]=Loser(i,B[father]);
    while(father/2>=1)
    {
        int tmp=Winner(B[father/2],B[0]);
        B[father/2]=Loser(B[father/2],B[0]);
        B[0]=tmp;
        father/=2;
    }
}
void Build()
{
    int s,i;
    for(s=1;s*2<=n-1;s<<=1);
    lowext=2*(n-s);
    offset=2*s-1;
    for(i=2;i<=lowext;i+=2)
    {
        Play((offset+i)/2,i-1,i);
    }
    if(n%2==1)
    {
        Play(n/2,B[(n-1)/2],lowext+1);
        i=lowext+3;
    }
    else
    {
        i=lowext+2;
    }
    for(;i<=n;i+=2)
    {
        Play((i-lowext+n-1)/2,i-1,i);
    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    Build();
    for(int i=0;i<n;++i)
    {
        cout<<a[B[i]]<<" ";
    }
    cout<<endl;
    while(m--)
    {
        cin>>Index>>val;
        a[Index+1]=val;
        replay(Index+1);
        for(int i=0;i<n;++i)
        {
            cout<<a[B[i]]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
