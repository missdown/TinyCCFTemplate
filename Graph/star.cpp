#include<iostream>
#include<cstring>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<queue>
using namespace std;
const int MAX_V = 200010;
const int MAX_E = 2000010;
const int INF = 0x3f3f3f3f;
int V,E,cnt;
int heap[MAX_V],dis[MAX_V];

struct Edge{
    int to,next,cost;
}rng[MAX_E];
void add(int u,int v,int cost){
    rng[cnt].to = v;
    rng[cnt].next = heap[u];
    rng[cnt].cost = cost;
    heap[u] = cnt++;
}
struct Rule{
    bool operator()(int &a,int &b)const{
        return dis[a] > dis[b];
    }
};
inline int read()
{
    int X=0,w=1; char ch=0;
    while(ch<'0' || ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}
void Dijkstra(int a_){
    memset(dis,INF,sizeof(dis));
    priority_queue<int,vector<int>,Rule > q;
    dis[a_] = 0;q.push(a_);

    while(!q.empty()){
        int u = q.top();q.pop();
        for(int k=heap[u];k != -1;k = rng[k].next){
            int &v = rng[k].to;
            if(dis[v] > dis[u] + rng[k].cost){
                dis[v] = dis[u] + rng[k].cost;
                q.push(v);
            }
        }
    }
}
int main(void){
    cnt = 0;
    memset(heap,-1,sizeof(heap));
    V = read(),E = read();
    int x,y,z;
    for(int i=1;i<=E;i++){
        x = read(),y = read(),z = read();
        add(x,y,z);
    }
    Dijkstra(1);
    if(dis[V] == INF){
        printf("-1\n");
    }
    else
        printf("%d\n",dis[V]);
    return 0;
}