//
// Created by miss on 19-1-22.
//

#ifndef ACM_TEMPLATE_SP_H
#define ACM_TEMPLATE_SP_H

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <limits>
#include <set>
#include <deque>
#include <stack>

namespace ShortestPath {


    template<typename T>
    class GraphMatrix {
    public:
        T **Graph;

        GraphMatrix(int vertexNum, int edgeNum, T initv) : __vertexNum(vertexNum), __edgeNum(edgeNum) {
            Graph = new T *[__vertexNum];
            for (int i = 0; i < __vertexNum; ++i) {
                Graph[i] = new T[vertexNum];
                std::fill(Graph[i], Graph[i] + __vertexNum, initv);
            }
        }

        void SetValue(int w, int h, T bias) {
            Graph[w][h] = bias;
//            Graph[__w - w][__h - h] = bias;    // Doult Method
        }

        T GetValue(int w, int h) const {
            return Graph[w][h];
        }

        ~GraphMatrix() {
            for (int i = 0; i < __vertexNum; ++i) {
                delete[] Graph[i];
            }
            delete[] Graph;
        }

        void print() {
            for (int i = 0; i < __vertexNum; ++i) {
                for (int j = 0; j < __vertexNum; ++j) {
                    std::cout << Graph[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

    private:
        int __vertexNum, __edgeNum;
    };


    template<typename T>
    class MatrixGraph {

    public:

        MatrixGraph(int v, int e, bool method = true, bool direction = false) :
                __method(method), vertexNum(v), edgeNum(e), direction(direction) {
            if (method)
                graph = new GraphMatrix<T>(v, e, INF);     // Using Array
            else {
                vgraph.resize(static_cast<unsigned long>(v));
                for (int i = 0; i < v; ++i) {
                    vgraph[i].resize(v);
                    std::fill(vgraph[i].begin(), vgraph[i].end(), INF);
                }
            }
        }

        ~MatrixGraph(){
            if(__method)
                delete graph;
        }

        void Set(int from, int to, T bias) {
            if (__method)
                graph->SetValue(from, to, bias);
            else
                vgraph[from][to] = bias;
            if (!direction) {
                if (__method)
                    graph->SetValue(to, from, bias);
                else
                    vgraph[to][from] = bias;
            }
        }

        friend std::ostream &operator<<(std::ostream &out, MatrixGraph &mg) {
            if (mg.__method)
                mg.graph->print();
            else
                for (int i = 0; i < mg.vgraph.size(); ++i) {
                    for (int j = 0; j < mg.vgraph[i].size(); ++j) {
                        out << mg.vgraph[i][j] << " ";
                    }
                    out << std::endl;
                }
        }

        // Using in Dense Graph
        int Prim(int entrance = 0) const {   // inlet
            T *d = new T[vertexNum];
            std::fill(d, d + vertexNum, INF);
            d[entrance] = static_cast<T>(0);     // Self distance is zero.
            bool *vis = new bool[vertexNum];
            memset(vis, 0, sizeof(bool) * (vertexNum));
            int ans = 0;
            for (int i = 0; i < vertexNum; ++i) {
                int u = -1, MIN = INF;
                for (int j = 0; j < vertexNum; ++j) {
                    if (!vis[j] && d[j] < MIN) {    // u let the d[u] tiny, MIN save the smallest d[u]
                        u = j;
                        MIN = d[j];
                    }
                }
                if (u == -1) return -1;  // EXIT Condition: Can't find any d[u] < INF;
                ans += d[u];
                vis[u] = true;        // Stamp the u has already came.
                for (int v = 0; v < vertexNum; ++v) {
                    if (!vis[v] && vgraph[u][v] != INF &&
                        vgraph[u][v] < d[v]) // if v has never been visited && u can attach v && u and uv can be better
                        d[v] = vgraph[u][v];   // optimize d[v]
                }
            }
            delete[] vis;
            delete[] d;
            return ans;
        }

        // O(n^2)
        void Dijkstra(int entrance) const {   // inlet
            T *d = new T[vertexNum];
            std::fill(d, d + vertexNum, INF);
            d[entrance] = static_cast<T>(0);     // Self distance is zero.
            bool *vis = new bool[vertexNum];
            memset(vis, 0, sizeof(bool) * (vertexNum));


            for (int i = 0; i < vertexNum; ++i) {
                int u = -1, MIN = INF;
                for (int j = 0; j < vertexNum; ++j) {
                    if (!vis[j] && d[j] < MIN) {    // u let the d[u] tiny, MIN save the smallest d[u]
                        u = j;
                        MIN = d[j];
                    }
                }

                if (u == -1) break;  // EXIT Condition: Can't find any d[u] < INF;
                vis[u] = true;        // Stamp the u has already came.
                for (int v = 0; v < vertexNum; ++v) {
                    if (!vis[v] && vgraph[u][v] != INF && d[u] + vgraph[u][v] <
                                                          d[v]) // if v has never been visited && u can attach v && u and uv can be better
                        d[v] = d[u] + vgraph[u][v];   // optimize d[v]
                }

            }
            for (int i = 0; i < vertexNum; ++i) {
                std::cout << d[i] << " ";
            }
            std::cout << std::endl;
            delete[] vis;
            delete[] d;
        }

        void Dijkstra(int entrance, int end) const {   // inlet
            T *d = new T[vertexNum];
            std::fill(d, d + vertexNum, INF);
            d[entrance] = static_cast<T>(0);     // Self distance is zero.
            bool *vis = new bool[vertexNum];
            memset(vis, 0, sizeof(bool) * (vertexNum));
            int *pre = new int[vertexNum];
            for (int i = 0; i < vertexNum; ++i) pre[i] = i;

            for (int i = 0; i < vertexNum; ++i) {
                int u = -1, MIN = INF;
                for (int j = 0; j < vertexNum; ++j) {
                    if (!vis[j] && d[j] < MIN) {    // u let the d[u] tiny, MIN save the smallest d[u]
                        u = j;
                        MIN = d[j];
                    }
                }

                if (u == -1) break;  // EXIT Condition: Can't find any d[u] < INF;
                vis[u] = true;        // Stamp the u has already came.
                for (int v = 0; v < vertexNum; ++v) {
                    if (!vis[v] && vgraph[u][v] != INF && d[u] + vgraph[u][v] <
                                                          d[v]) {// if v has never been visited && u can attach v && u and uv can be better
                        d[v] = d[u] + vgraph[u][v];   // optimize d[v]
                        pre[v] = u;
                    }
                }

            }
            __DFSPATH(entrance, end, pre);
            std::cout << std::endl;
            delete[] vis;
            delete[] d;
            delete[] pre;
        }

        /// ADVANCED
        void DijkstraDFS(int s, int end) {
            T *d = new T[vertexNum];
            std::fill(d, d + vertexNum, INF);
            d[s] = static_cast<T>(0);
            bool *vis = new bool[vertexNum];
            memset(vis, 0, sizeof(bool) * (vertexNum));
            /// Attention
            std::vector<int> pre[vertexNum];


            for (int i = 0; i < vertexNum; ++i) {
                int u = -1, MIN = INF;
                for (int j = 0; j < vertexNum; ++j) {
                    if (!vis[j] && d[j] < MIN) {
                        u = j;
                        MIN = d[j];
                    }
                }

                if (u == -1) break;
                vis[u] = true;
                for (int v = 0; v < vertexNum; ++v) {
                    if (!vis[v] && vgraph[u][v] != INF) {
                        if (d[u] + vgraph[u][v] < d[v]) {
                            d[v] = d[u] + vgraph[u][v];
                            /// Attention
                            pre[v].clear();
                            pre[v].push_back(u);
                        } else if (d[u] + vgraph[u][v] == d[v])
                            pre[v].push_back(u);
                    }
                }

            }

            __DFSPATHADVANCED(s, end, pre);
            delete[] vis;
            delete[] d;
        }

        void SetOptValue(int nval) {
            optvalue = nval;
        }

        void Floyd() {
            for (int i = 0; i < vertexNum; ++i) {
                vgraph[i][i] = 0;
            }

            if (__method) {
                for (int k = 0; k < vertexNum; ++k) {
                    for (int i = 0; i < vertexNum; ++i) {
                        for (int j = 0; j < vertexNum; ++j) {
                            if (graph->Graph[i][k] != INF && graph->Graph[k][j] != INF &&
                                (graph->Graph[i][k] + graph->Graph[k][j]) < graph->Graph[i][j])
                                graph->Graph[i][j] = graph->Graph[i][k] + graph->Graph[k][j];
                        }
                    }
                }
                graph->print();
            } else {
                for (int k = 0; k < vertexNum; ++k) {
                    for (int i = 0; i < vertexNum; ++i) {
                        for (int j = 0; j < vertexNum; ++j) {
                            if (vgraph[i][k] != INF && vgraph[k][j] != INF &&
                                (vgraph[i][k] + vgraph[k][j]) < vgraph[i][j])
                                vgraph[i][j] = vgraph[i][k] + vgraph[k][j];
                        }
                    }
                }
//                for (int i = 0; i < vertexNum; ++i) {
//                    for (int j = 0; j < vertexNum; ++j) {
//                        std::cout << vgraph[i][j] << " ";
//                    }
//                    std::cout << std::endl;
//                }
            }
        }

        int LongestPathDP(int s = 0){
            T * dp = new T[vertexNum];
            int * choice = new int[vertexNum];
            std::fill(choice, choice+ vertexNum, -1);
            memset(dp, 0, sizeof(T)*vertexNum);
            int tmp = __DP(s, dp, choice);
            std::cout << s ;
            while(choice[s] != -1) {
                s = choice[s];
                std::cout << "->" << s ;
            }
            std::cout << std::endl;
            delete[] dp;
            delete[] choice;
            return tmp;
        }

        int LongestPathDPEndComfirm(int s = 0) {
            T * dp = new T[vertexNum];
            bool * vis = new bool[vertexNum];
            memset(vis, false, sizeof(bool) * vertexNum);
            std::fill(dp, dp + vertexNum, -INF);
            dp[s] = 0;
            int tmp = __DPEndConfirm(s, dp, vis);
            delete[] vis;
            delete[] dp;
            return tmp;
        }

        // Add new Edge Cost;May have multiply access;
        /*
         * T** cost; int c[];
         *
         * for (int v = 0; v < vertexNum; ++v) {
                    if(!vis[v] && vgraph[u][v] != INF) {
                         if(d[u] + vgraph[u][v] < d[v]) {
                             d[v] = d[u] + vgraph[u][v];
                             c[v] = c[u] + cost[u][v];
                         }else if(d[u] + vgraph[u][v] == d[v] && c[u] + cost[u][v] < c[v])
                             c[v] = c[u] + cost[u][v];

                    }
                }
         */
        // Add new Point
        /*
         * T* weight; int w[];
         *
         * for (int v = 0; v < vertexNum; ++v) {
                    if(!vis[v] && vgraph[u][v] != INF) {
                         if(d[u] + vgraph[u][v] < d[v]) {
                             d[v] = d[u] + vgraph[u][v];
                             w[v] = w[u] + weight[u][v];
                         }else if(d[u] + vgraph[u][v] == d[v] && w[u] + weight[v] < w[v])
                             w[v] = w[u] + weight[v];

                    }
                }
         */
        // How Many Shortest Path
        /*
         * int num[];
         *
         * for (int v = 0; v < vertexNum; ++v) {
                    if(!vis[v] && vgraph[u][v] != INF) {
                         if(d[u] + vgraph[u][v] < d[v]) {
                             d[v] = d[u] + vgraph[u][v];
                             num[v] = num[u];
                         }else if(d[u] + vgraph[u][v] == d[v])
                             w[v] = w[u] + weight[v];
                             num[v] += num[u];

                    }
                }
         */

        void EulerPath() {

        }

    private:

        const T INF = std::numeric_limits<T>::max() / 2;

        bool direction = false;

        int __DP(int i, T* dp, int * choice) {
            if(dp[i] > 0) return dp[i];  // Already Calculated.
            for (int j = 0; j < vertexNum; ++j) {
                if(vgraph[i][j] != INF) {
                    int temp = __DP(j, dp, choice) + vgraph[i][j];
                    if(dp[i] < temp){
                        dp[i] = temp;
                        choice[i] = j;
                    }
                }
            }
            return dp[i];
        }

        int __DPEndConfirm(int i, T * dp, bool * vis) {
            if(vis[i]) return dp[i];
            vis[i] = true;
            for (int j = 0; j < vertexNum; ++j) {
                if(vgraph[i][j] != INF) {
                    dp[i] = std::max(dp[i], __DPEndConfirm(j, dp, vis) + vgraph[i][j]);
                }
            }
            return dp[i];
        }

        void __DFSPATH(int s, int v, int *pre) const {
            if (v == s) {
                std::cout << v << " ";
                return;
            }
            __DFSPATH(s, pre[v], pre);
            std::cout << v << " ";
        }

        /// ADVANCED
        int optvalue = 10; // the best value of Secondary optimize standard
        std::vector<int> path, tempPath;   // Saving Best Paths

        void __DFSPATHADVANCED(int start, int cur, std::vector<int> *pre) {

            if (cur == start) {
                tempPath.push_back(cur);
                int value;
                /// Calculate value by require.

                /* User Coding Here */

                /// Here is a Sample Below:

                //* Sum of the edge's weight *//
                value = 0;
                for (unsigned long i = tempPath.size() - 1; i > 0; --i) {  // From Back to Front
                    int id = tempPath[i], idNext = tempPath[i - 1];
                    // value += V[id][idNext];  //  Edge's Second Evalution Value;
                }
                //* Sum of the vertex'w weight  *//
                value = 0;
                for (unsigned long i = tempPath.size(); i > 0; --i) {  // From Back to Front
                    int id = tempPath[i - 1];
                    // value += W[id];  //  Vertex's Second Evalution Value;
                }
                //* if value better than optvalue *//
                if (value < optvalue) {

                    /// Calculate end
                    optvalue = value;
                    path = tempPath;
                }
                tempPath.pop_back();


                for (unsigned long j = path.size(); j > 0; --j) {
                    std::cout << path[j - 1] << " ";
                }
                std::cout << std::endl;

                return;
            }

            tempPath.push_back(cur);
            for (int j = 0; j < pre[cur].size(); ++j) {
                __DFSPATHADVANCED(start, pre[cur][j], pre);
            }
            tempPath.pop_back();
        }

        /// ADVANCED END

        GraphMatrix<T> *graph;
        bool __method = true;
        std::vector<std::vector<T>> vgraph;
        int vertexNum;
        int edgeNum;
    };


    template<typename T>
    struct Node {
        int v;   // Attribute Node
        T dis;   // Edge bias;
        Node() = default;

        Node(int v, T dis) : v(v), dis(dis) {};

        friend bool operator>(const Node &first, const Node &second) { return first.dis > second.dis; }

        friend bool operator<(const Node &first, const Node &second) { return first.dis < second.dis; }
    };

    template<typename T>
    class LinkedlistGraph {
        using node = Node<T>;
        using size_t = unsigned long;

    public:

        LinkedlistGraph() = delete;

        LinkedlistGraph(int v, int e, bool direction) : vertexNum(v), edgeNum(e), __direction(direction) {
            Adj = new std::vector<node>[v];
        }

        ~LinkedlistGraph() {
            delete[] Adj;
        }

        void Set(int from, int to, T bias) {
            Adj[from].push_back(node(to, bias));
            if (!__direction)
                Adj[to].push_back(node(from, bias));
        }

        friend std::ostream &operator<<(std::ostream &out, LinkedlistGraph &llg) {
            for (int i = 0; i < llg.vertexNum; ++i) {
                for (int j = 0; j < llg.Adj[i].size(); ++j) {
                    out << i << " " << llg.Adj[i][j].v << " " << llg.Adj[i][j].dis << std::endl;
                }
            }
            return out;
        }


        int Prim(int s = 0) const {
            T *d = new T[vertexNum];
//            if(std::is_same<int, T>::value)
//                memset(d, 0x3f3f3f, sizeof(T) * vertexNum);
//            else
            std::fill(d, d + vertexNum, INF);
            bool *vis = new bool[vertexNum];
            std::fill(vis, vis + vertexNum, false);
            d[s] = 0;
            int ans = 0;
            for (int i = 0; i < vertexNum; ++i) {
                int u = -1;
                T MIN = INF;
                for (int j = 0; j < vertexNum; ++j) {
                    if (!vis[j] && d[j] < MIN) {
                        u = j;
                        MIN = d[j];
                    }
                }
                if (u == -1) return -1;
                vis[u] = true;
                ans += d[u];
                for (int j = 0; j < Adj[u].size(); ++j) {
                    if (!vis[Adj[u][j].v] && Adj[u][j].dis < d[Adj[u][j].v])
                        d[Adj[u][j].v] = Adj[u][j].dis;
                }
            }
            delete[] vis;
            delete[] d;
            return ans;
        }

        int PrimHeap(int s = 0) const {
            bool *vis = new bool[vertexNum];
            std::fill(vis, vis + vertexNum, false);
            std::priority_queue<node, std::vector<node>, std::greater<node>> Q;  // Small Cap Heap.
            for (int j = 0; j < Adj[s].size(); ++j) {
                Q.push(node(Adj[s][j].v, Adj[s][j].dis));
            }
            int ans = 0;
            vis[s] = true;
            node tmp;
            for (int i = 0; i < vertexNum - 1; ++i) {
                do {
                    tmp = Q.top();
                    Q.pop();
                } while (vis[tmp.v]);
                if (Q.empty()) break;
                vis[tmp.v] = true;
                ans += tmp.dis;
                for (int j = 0; j < Adj[tmp.v].size(); ++j) {
                    if (!vis[Adj[tmp.v][j].v])
                        Q.push(node(Adj[tmp.v][j].v, Adj[tmp.v][j].dis));
                }
            }
            delete[] vis;
            return ans;
        }


        int Kruskal() {
            int *father = new int[vertexNum];
            int ans = 0, Num_Edge = 0;
//            KruskalEdge * test = new KruskalEdge[edgeNum];
            std::priority_queue<KruskalEdge, std::vector<KruskalEdge>, std::greater<KruskalEdge>> E;
            for (int i = 0, counter = 0; i < vertexNum; ++i) {
                for (int j = 0; j < Adj[i].size(); ++j, ++counter) {
                    E.push(KruskalEdge(i, Adj[i][j].v, Adj[i][j].dis));
//                    test[counter].from = i;
//                    test[counter].to = Adj[i][j].v;
//                    test[counter].cost = Adj[i][j].dis;
                }
            }
//            std::sort(test, test+edgeNum);
            for (int i = 0; i < vertexNum; ++i) {
                father[i] = i;
            }

//            for (int i = 0; i < edgeNum; i++) {
//                int fafrom = __FindFather(test[i].from, father);
//                int fato = __FindFather(test[i].to, father);
//                if (fafrom != fato) {
//                    father[fafrom] = fato;
//                    ans += test[i].cost;
//                    Num_Edge++;
//                    if (Num_Edge == vertexNum - 1) break;
//                }
//            }
            while (!E.empty()) {
                KruskalEdge tmp = E.top();
                E.pop();
                int fafrom = __FindFather(tmp.from, father);
                int fato = __FindFather(tmp.to, father);
                if (fafrom != fato) {
                    father[fafrom] = fato;
                    ans += tmp.cost;
                    Num_Edge++;
                    if (Num_Edge == vertexNum - 1) break;
                }
            }
            delete[] father;
            if (Num_Edge != vertexNum - 1) return -1;
            else return ans;
        }


        void Dijkstra(int s = 0) const {
            T *d = new T[vertexNum];
            std::fill(d, d + vertexNum, INF);
            bool *vis = new bool[vertexNum];
            std::fill(vis, vis + vertexNum, false);
            d[s] = 0;
            for (int i = 0; i < vertexNum; ++i) {
                int u = -1;
                T MIN = INF;
                for (int j = 0; j < vertexNum; ++j) {
                    if (!vis[j] && d[j] < MIN) {
                        u = j;
                        MIN = d[j];
                    }
                }
                if (u == -1) break;
                vis[u] = true;
                for (int j = 0; j < Adj[u].size(); ++j) {
                    if (!vis[Adj[u][j].v] && d[u] + Adj[u][j].dis < d[Adj[u][j].v])
                        d[Adj[u][j].v] = d[u] + Adj[u][j].dis;
                }
            }
            for (int z = 0; z < vertexNum; ++z) {
                std::cout << d[z] << " ";
            }
            std::cout << std::endl;
            delete[] vis;
            delete[] d;
        }


        void DijkstraHeap(int s = 0) const {
            T d[vertexNum];
            std::fill(d, d + vertexNum, INF);
            bool vis[vertexNum];
            std::fill(vis, vis + vertexNum, false);
            d[s] = 0;
            std::priority_queue<node, std::vector<node>, std::greater<node>> Q;  // Small Cap Heap.
            Q.push(node(s, d[s]));
            while (!Q.empty()) {
                node tmp = Q.top();
                Q.pop();
                if (vis[tmp.v]) continue;
                vis[tmp.v] = true;
                for (int i = 0; i < Adj[tmp.v].size(); ++i) {
                    if (!vis[Adj[tmp.v][i].v] && d[tmp.v] + Adj[tmp.v][i].dis < d[Adj[tmp.v][i].v]) {
                        d[Adj[tmp.v][i].v] = d[tmp.v] + Adj[tmp.v][i].dis;
                        Q.push(node(Adj[tmp.v][i].v, d[Adj[tmp.v][i].v]));
                    }
                }
            }
            for (int z = 0; z < vertexNum; ++z) {
                std::cout << d[z] << " ";
            }
            std::cout << std::endl;
        }

        void DijkstraHeap (int s, int end) const {
            T d[vertexNum];
            std::fill(d, d + vertexNum, INF);
            bool vis[vertexNum];
            int pre[vertexNum];
            for (int i = 0; i < vertexNum; ++i) {
                vis[i] = false;
                pre[i] = i;
            }
            d[s] = 0;
            std::priority_queue<node, std::vector<node>, std::greater<node>> Q;  // Small Cap Heap.
            Q.push(node(s, d[s]));
            while (!Q.empty()) {
                node tmp = Q.top();
                Q.pop();
                if (vis[tmp.v]) continue;
//                if (tmp.v == end) break;
                vis[tmp.v] = true;
                for (int i = 0; i < Adj[tmp.v].size(); ++i) {
                    if (!vis[Adj[tmp.v][i].v] && d[tmp.v] + Adj[tmp.v][i].dis < d[Adj[tmp.v][i].v]) {
                        d[Adj[tmp.v][i].v] = d[tmp.v] + Adj[tmp.v][i].dis;
                        pre[Adj[tmp.v][i].v] = tmp.v;
                        Q.push(node(Adj[tmp.v][i].v, d[Adj[tmp.v][i].v]));
                    }
                }
            }
            __DFSPATH(s, end, pre);
            std::cout << std::endl;
        }

        void Astar(int s, int end) const {
            T d[vertexNum];
            std::fill(d, d + vertexNum, INF);
            bool vis[vertexNum];
            int pre[vertexNum];
            for (int i = 0; i < vertexNum; ++i) {
                vis[i] = false;
                pre[i] = i;
            }
            d[s] = 0;
            std::priority_queue<node, std::vector<node>, std::greater<node>> Q;  // Small Cap Heap.
            Q.push(node(s, d[s]));
            while (!Q.empty()) {
                node tmp = Q.top();
                Q.pop();
                if (vis[tmp.v]) continue;
                if (tmp.v == end) break;
                vis[tmp.v] = true;
                for (int i = 0; i < Adj[tmp.v].size(); ++i) {
                    for (int j = 0; j < 9; ++j) {
                        int u = tmp.v + Dir[j].x;
                        int v = i + Dir[j].y;
                        if(u<0 || u >= vertexNum || v < 0 || v>= Adj[u].size()) continue;
                        if (!vis[Adj[u][v].v] && d[u] + Adj[u][v].dis + sqrt((u-end)*(u-end) + (v-end)*(v-end)) < d[Adj[u][v].v]) {
                            d[Adj[u][v].v] = d[u] + Adj[u][v].dis + sqrt((u-end)*(u-end) + (v-end)*(v-end));
                            pre[Adj[u][v].v] = u;
                            Q.push(node(Adj[u][v].v, d[Adj[u][v].v]));
                        }
                    }
                }
            }
            __DFSPATH(s, end, pre);
            std::cout << std::endl;
        }

        void Dijkstra(int s, int end) const {
            T d[vertexNum];
            std::fill(d, d + vertexNum, INF);
            bool vis[vertexNum];
            int pre[vertexNum];
//            std::fill(vis, vis + vertexNum, false);
            for (int i = 0; i < vertexNum; ++i) {
                vis[i] = false;
                pre[i] = i;
            }
            d[s] = 0;
            for (int i = 0; i < vertexNum; ++i) {
                int u = -1;
                T MIN = INF;
                for (int j = 0; j < vertexNum; ++j) {
                    if (!vis[j] && d[j] < MIN) {
                        u = j;
                        MIN = d[j];
                    }
                }
                if (u == -1) break;
                vis[u] = true;
                for (int j = 0; j < Adj[u].size(); ++j) {
                    if (!vis[Adj[u][j].v] && d[u] + Adj[u][j].dis < d[Adj[u][j].v]) {
                        d[Adj[u][j].v] = d[u] + Adj[u][j].dis;
                        pre[Adj[u][j].v] = u;
                    }
                }
            }
            __DFSPATH(s, end, pre);
            std::cout << std::endl;
        }

        bool Bellman(int s) const {
            T d[vertexNum];
            std::fill(d, d + vertexNum, INF);  // Fucking a Dog !!!! If Using The Max Value may have wrong answer;

            d[s] = 0;
            for (int i = 0; i < vertexNum - 1; ++i) {
                for (int u = 0; u < vertexNum; ++u) {
                    for (int j = 0; j < Adj[u].size(); ++j) {
                        if (d[u] + Adj[u][j].dis < d[Adj[u][j].v]) {
                            d[Adj[u][j].v] = d[u] + Adj[u][j].dis;
                        }
                    }
                }
            }

            for (int u = 0; u < vertexNum; ++u) {
                for (int j = 0; j < Adj[u].size(); ++j) {
                    int v = Adj[u][j].v;
                    int dis = Adj[u][j].dis;
                    if (d[u] + dis < d[v]) {
                        return false;
                    }
                }
            }

            for (int i = 0; i < vertexNum; ++i) {
                std::cout << d[i] << " ";
            }
            std::cout << std::endl;
            return true;
        }

        void Bellman(int s, int end) {
            T d[vertexNum];
            std::fill(d, d + vertexNum, INF);
            std::set<int> pre[vertexNum];
            /// ADVANCED
            // int *num = new int(vertexNum);   // Save the num of shortest paths
            // int *w = new int[vertexNum];     // Save the maxvalue of the sum of vertex bias
            // std::memset(num, 0, sizeof(int) * vertexNum);
            // std::memset(w, 0, sizeof(int) * vertexNum);
            // w[s] = weight[s]; // weight[]:bias of vertex
            // num[s] = 1;
            d[s] = 0;
            for (int i = 0; i < vertexNum - 1; ++i) {
                for (int u = 0; u < vertexNum; ++u) {
                    for (int j = 0; j < Adj[u].size(); ++j) {
                        if (d[u] + Adj[u][j].dis < d[Adj[u][j].v]) {
                            d[Adj[u][j].v] = d[u] + Adj[u][j].dis;        // UPDATING
                            // w[v] = w[u] + weight[v];
                            // num[v] = num[u];
                            pre[Adj[u][j].v].clear();
                            pre[Adj[u][j].v].insert(u);
                        } else if (d[u] + Adj[u][j].dis == d[Adj[u][j].v]) {
//                            if(w[u] + weight[v] > w[v])
//                                w[v] = w[u] + weight[v];
                            pre[Adj[u][j].v].insert(u);
//                            num[v] = 0;
//                            for (std::set<int>::iterator it = pre[v].begin; it != pre[v].end; it++) {
//                                num[v] += num[*it];
                        }
                    }

                }
            }

            __DFSPATHADVANCED(s, end, pre);
        }


        bool SPFA(int s) {
            T d[vertexNum];
            bool inq[vertexNum];
            int num[vertexNum];
            memset(inq, false, sizeof(inq));
            memset(num, 0, sizeof(num));
            std::fill(d, d + vertexNum, INF);

            std::queue<int> Q;
            Q.push(s);
            inq[s] = true;
            num[s]++;
            d[s] = 0;
            while (!Q.empty()) {
                int u = Q.front();
                Q.pop();
                inq[u] = false;
                for (int i = 0; i < Adj[u].size(); ++i) {
                    int v = Adj[u][i].v;
                    int dis = Adj[u][i].dis;
                    if (d[u] + dis < d[v]) {
                        d[v] = d[u] + dis;
                        if (!inq[v]) {
                            Q.push(v);
                            inq[v] = true;
                            num[v]++;
                            if (num[v] >= vertexNum) return false;    // Negative Loop
                        }
                    }
                }
            }

            for (int i = 0; i < vertexNum; ++i) {
                std::cout << d[i] << " ";
            }
            std::cout << std::endl;
            return true;
        }


        bool SPFASLF(int s) {  // Small Label First
            T *d = new T[vertexNum];
            // memset(dis, 0x3f, sizeof(dis));  // Type Int
            bool *inq = new bool[vertexNum];
            int *num = new int[vertexNum];
            memset(inq, false, sizeof(bool) * vertexNum);
            memset(num, 0, sizeof(int) * vertexNum);
            std::fill(d, d + vertexNum, INF);

            std::deque<int> Q;
            Q.push_back(s);
            inq[s] = true;
            num[s]++;
            d[s] = 0;
            while (!Q.empty()) {
                int u = Q.front();
                Q.pop_front();
                inq[u] = false;
                for (int i = 0; i < Adj[u].size(); ++i) {
                    int v = Adj[u][i].v;
                    int dis = Adj[u][i].dis;
                    if (d[u] + dis < d[v]) {
                        d[v] = d[u] + dis;
                        if (!inq[v]) {

                            if (d[v] <= d[Q.front()]) Q.push_front(v);
                            else Q.push_back(v);
                            inq[v] = true;
                            num[v]++;
                            if (num[v] >= vertexNum) return false;    // Negative Loop
                        }
                    }
                }
            }

            for (int i = 0; i < vertexNum; ++i) {
                std::cout << d[i] << " ";
            }
            std::cout << std::endl;
            delete[] d;
            delete[] inq;
            delete[] num;
            return true;
        }

        bool SPFALLL(int s) {       // Large Label Last
            T *d = new T[vertexNum];
            bool *inq = new bool[vertexNum];
            int *num = new int[vertexNum];
            memset(inq, false, sizeof(bool) * vertexNum);
            memset(num, 0, sizeof(int) * vertexNum);
            std::fill(d, d + vertexNum, INF);

            std::queue<int> Q;
            Q.push(s);
            inq[s] = true;
            num[s]++;
            d[s] = 0;
            int cnt = 1, sum = 0;    // Compared with the mean value
            while (!Q.empty()) {
                int u = Q.front();
                while (d[u] * cnt > sum) {
                    Q.pop();
                    Q.push(u);
                    u = Q.front();
                }
                Q.pop();
                cnt--;
                sum -= d[u];
                inq[u] = false;
                for (int i = 0; i < Adj[u].size(); ++i) {
                    int v = Adj[u][i].v;
                    int dis = Adj[u][i].dis;
                    if (d[u] + dis < d[v]) {
                        d[v] = d[u] + dis;
                        if (!inq[v]) {
                            Q.push(v);
                            sum += d[v];
                            cnt++;
                            inq[v] = true;
                            num[v]++;
                            if (num[v] >= vertexNum) return false;    // Negative Loop
                        }
                    }
                }
            }

            for (int i = 0; i < vertexNum; ++i) {
                std::cout << d[i] << " ";
            }
            std::cout << std::endl;
            delete[] d;
            delete[] inq;
            delete[] num;
            return true;
        }

        bool SPFASLFLLL(int s) {
            T *d = new T[vertexNum];
            // memset(dis, 0x3f, sizeof(dis));  // Type Int
            bool *inq = new bool[vertexNum];
            int *num = new int[vertexNum];
            memset(inq, false, sizeof(bool) * vertexNum);
            memset(num, 0, sizeof(int) * vertexNum);
            std::fill(d, d + vertexNum, INF);

            std::deque<int> Q;
            Q.push_back(s);
            inq[s] = true;
            num[s]++;
            d[s] = 0;
            int cnt = 1, sum = 0;    // Compared with the mean value
            while (!Q.empty()) {
                int u = Q.front();
                while (d[u] * cnt > sum) {
                    Q.pop_front();
                    Q.push_back(u);
                    u = Q.front();
                }
                Q.pop_front();
                inq[u] = false;
                cnt--;
                sum -= d[u];
                for (int i = 0; i < Adj[u].size(); ++i) {
                    int v = Adj[u][i].v;
                    int dis = Adj[u][i].dis;
                    if (d[u] + dis < d[v]) {
                        d[v] = d[u] + dis;
                        if (!inq[v]) {
                            if (d[v] <= d[Q.front()]) Q.push_front(v);
                            else Q.push_back(v);
                            inq[v] = true;
                            num[v]++;
                            sum += d[v];
                            cnt++;
                            if (num[v] >= vertexNum) return false;    // Negative Loop
                        }
                    }
                }
            }

            for (int i = 0; i < vertexNum; ++i) {
                std::cout << d[i] << " ";
            }
            std::cout << std::endl;
            delete[] d;
            delete[] inq;
            delete[] num;
            return true;
        }


        bool SPFADFS(int s) {   // True : Has Negative Loop  False: Optimisitic
            T *d = new T[vertexNum];
            bool *vis = new bool[vertexNum];
            memset(vis, false, sizeof(bool) * vertexNum);
            for (int i = 0; i < vertexNum; ++i) {
                __SPFADFS(i, vis, d);
                if (flag) {
                    delete[] vis;
                    delete[] d;
                    return true;
                }
            }
            delete[] vis;
            delete[] d;
            return false;
        }

        bool TopologicalSort() {
            int* inDegree = new int[vertexNum];
            memset(inDegree, 0, sizeof(int) * vertexNum);
            for (int i = 0; i < vertexNum; ++i) {
                for (int j = 0; j < Adj[i].size(); ++j) {
                    inDegree[Adj[i][j].v]++;
                }
            }
            int num = 0;
            std::queue<int> q;
            for (int i = 0; i < vertexNum; ++i) {
                if(inDegree[i] == 0)
                    q.push(i);
            }

            while(!q.empty()) {
                int u = q.front();
                q.pop();
                for (int i = 0; i < Adj[u].size(); ++i) {
                    int v = Adj[u][i].v;
                    inDegree[v]--;
                    if(!inDegree[v])
                        q.push(v);
                }
                num++;
            }
            delete[] inDegree;
            return num == vertexNum;
        }

        // Find the longest path to other points based on the vertices passed in;
        void LongestPath(int s = 0){
            T d[vertexNum] = {0};
            bool vis[vertexNum] = {false};
            std::stack<int> Stack;
            for (int i = 0; i < vertexNum; i++)
                if (!vis[i])
                    __ToplogicalSortUtil(i, vis, Stack);
            std::fill(d, d+vertexNum, -INF);
            d[s] = 0;
            while(!Stack.empty())
            {
                int u = Stack.top();
                Stack.pop();
                // Updating Bias.
                if (d[u] != -INF)
                {
                    for(auto &i:Adj[u])
                        if (d[i.v] < d[u] + i.dis)
                            d[i.v] = d[u] + i.dis;
                }
            }

            for (int i = 0; i < vertexNum; i++)
                (d[i] == -INF)? std::cout << "INF ": std::cout << d[i] << " ";
            std::cout << std::endl;
        }




    private:

        bool __direction = false;

        struct KruskalEdge {
            int from, to;
            T cost;

            KruskalEdge() = delete;

            KruskalEdge(int u, int v, T bias) : from(u), to(v), cost(bias) {};

            friend bool operator<(const KruskalEdge &first, const KruskalEdge &second) {
                return first.cost < second.cost;
            }

            friend bool operator>(const KruskalEdge &first, const KruskalEdge &second) {
                return first.cost > second.cost;
            }

        };

        typedef struct
        {
            signed char x, y;
        } AstarPoint;

        const AstarPoint Dir[9] =
                {
                        {0, 0},
                        {0, 1},   // East
                        {1, 1},   // South_East
                        {1, 0},   // South
                        {1, -1},  // South_West
                        {0, -1},  // West
                        {-1, -1}, // North_West
                        {-1, 0},  // North
                        {-1, 1}   // North_East
                };

        void __ToplogicalSortUtil(int v, bool *visited, std::stack<int> &Stack)
        {
            visited[v] = true;
            for (auto &i: Adj[v])
            {
                if (!visited[i.v])
                    __ToplogicalSortUtil(i.v, visited, Stack);
            }
            Stack.push(v);
        }

        int __FindFather(int x, int *father) {
            int a = x;
            while (x != father[x])
                x = father[x];

            while (a != father[a]) {
                int z = a;
                a = father[a];
                father[z] = x;
            }
            return x;
        }

        void __DFSPATH(int s, int v, int *Path) const {
            if (v == s) {
                std::cout << v << " ";
                return;
            }
            __DFSPATH(s, Path[v], Path);
            std::cout << v << " ";
        }


        bool flag = false;

        void __SPFADFS(int u, bool *vis, T *d) {
            if (flag) return;
            vis[u] = true;
            for (int i = 0; i < Adj[u].size(); ++i) {
                if (d[u] + Adj[u][i].dis < d[Adj[u][i].v]) {
                    d[Adj[u][i].v] = d[u] + Adj[u][i].dis;
                    if (vis[Adj[u][i].v]) {
                        flag = true;
                        return;
                    } else __SPFADFS(Adj[u][i].v, vis, d);
                }
            }
            vis[u] = false;
        }


        /// ADVANCED
        int optvalue = 10; // the best value of Secondary optimize standard
        std::vector<int> path, tempPath;   // Saving Best Paths

        void __DFSPATHADVANCED(int start, int cur, std::set<int> *pre) {

            if (cur == start) {
                tempPath.push_back(cur);
                int value;
                /// Calculate value by require.

                /* User Coding Here */

                /// Here is a Sample Below:

                //* Sum of the edge's weight *//
                value = 0;
                for (unsigned long i = tempPath.size() - 1; i > 0; --i) {  // From Back to Front

                    int id = tempPath[i], idNext = tempPath[i - 1];
                    // value += V[id][idNext];  //  Edge's Second Evalution Value;
                }
                //* Sum of the vertex'w weight  *//
                value = 0;
                for (unsigned long i = tempPath.size(); i > 0; i--) {  // From Back to Front
                    int id = tempPath[i - 1];
                    // value += W[id];  //  Vertex's Second Evalution Value;
                }
                //* if value better than optvalue *//
                if (value < optvalue) {
                    /// Calculate end
                    optvalue = value;
                    path = tempPath;
                }
                tempPath.pop_back();
                for (unsigned long j = path.size(); j > 0; --j) {
                    std::cout << path[j - 1] << " ";
                }
                std::cout << std::endl;
                return;
            }
            tempPath.push_back(cur);
            for (auto it = pre[cur].begin(); it != pre[cur].end(); it++) {
                __DFSPATHADVANCED(start, *it, pre);
            }
            tempPath.pop_back();
        }

        /// ADVANCED END

        std::vector<node> *Adj;
        int vertexNum;
        int edgeNum;
        const T INF = std::numeric_limits<T>::max() / 2;
    };



    template<typename T>
    class StarHeap {
    public:
        StarHeap(int capacity = 50) : size(0)
        {
            H.resize(capacity);
        }

        ~StarHeap() = default;

        bool empty() {
            return size == 0;
        }

        void makeEmpty() {
            size = 0;
            for (auto it = H.begin(); it != H.end(); it++) {
                H.erase(it);
            }
        }

        void push(const T &x, const T* d) {
            int current;
            if (size == H.size() - 1) {
                H.resize(2 * size);
            }
            for (current = ++size; current > 1 && d[H[current / 2]] > d[x]; current /= 2) {
                H[current] = H[current / 2];
            }
            H[current] = x;
        }

        T pop(const T* d) {
            if (this -> empty()) {
                throw ("Heap is Empty already.");
            }
            T top = H[1];
            H[1] = H[size--];
            int i = 1, j = i * 2;
            while(j <= size) {
                if(j + 1 <= size && d[H[j + 1]] < d[H[j]])
                    ++j;
                if(d[H[j]] < d[H[i]]) {
                    std::swap(H[i], H[j]);
                    i = j;
                    j = i * 2;
                } else
                    break;
            }
            return top;
        }

        void print(){
            for(auto&i : H) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }

    private:
        std::vector<T> H;
        unsigned long size;
    };


    template<typename T>
    class LinkedListStar {

    public:
        LinkedListStar(int vertexNum, int edgeNum, bool direction) : vertexNum(vertexNum), edgeNum(edgeNum),
                                                                     __direction(direction) {
            head = new int[vertexNum];
//            memset(head, 0, sizeof(int)*vertexNum);
            std::fill(head, head + vertexNum, -1);
            edge = new Edge[edgeNum];

        }

        ~LinkedListStar() {
            delete[] head;
            delete[] edge;
        }

        void Set(int u, int v, T w) {
            edge[cnt].bias = w;
            edge[cnt].to = v;
            edge[cnt].next = head[u];
            head[u] = cnt++;
            if (!__direction) {
                edge[cnt].bias = w;
                edge[cnt].to = u;
                edge[cnt].next = head[v];
                head[v] = cnt++;
            }
        }

        void Dijkstra(int s = 0) {
            T *d = new T[vertexNum];
            std::fill(d, d + vertexNum, INF);
            d[s] = 0;
            heap.makeEmpty();
            heap.push(s, d);
            while (!heap.empty()) {
                int u = heap.pop(d);
                for (int k = head[u]; k != -1; k = edge[k].next) {
                    int v = edge[k].to;
                    if (d[v] > d[u] + edge[k].bias) {
                        d[v] = d[u] + edge[k].bias;
                        heap.push(v, d);
                    }
                }
            }
            for (int z = 0; z < vertexNum; ++z) {
                std::cout << d[z] << " ";
            }
            std::cout << std::endl;
            delete[] d;
        }

        bool SPFA(int s = 0) {
            T *d = new T[vertexNum];
            bool *inq = new bool[vertexNum];
            int *num = new int[vertexNum];
            memset(inq, false, sizeof(bool) * vertexNum);
            memset(num, 0, sizeof(int) * vertexNum);
            std::fill(d, d + vertexNum, INF);

            std::queue<int> Q;
            Q.push(s);
            inq[s] = true;
            num[s]++;
            d[s] = 0;
            while (!Q.empty()) {
                int u = Q.front();
                Q.pop();
                inq[u] = false;
                for (int i = head[u]; i != -1; i = edge[i].next) {
                    if (d[u] + edge[i].bias < d[edge[i].to]) {
                        d[edge[i].to] = d[u] + edge[i].bias;
                        if (!inq[edge[i].to]) {
                            Q.push(edge[i].to);
                            inq[edge[i].to] = true;
                            num[edge[i].to]++;
                            if (num[edge[i].to] >= vertexNum) return false;    // Negative Loop
                        }
                    }
                }
            }

            for (int i = 0; i < vertexNum; ++i) {
                std::cout << d[i] << " ";
            }
            std::cout << std::endl;
            delete[] d;
            delete[] inq;
            delete[] num;
            return true;
        }

        friend std::ostream &operator<<(std::ostream &out, LinkedListStar &LS) {
            for (int i = 0; i < LS.vertexNum; ++i) {
                for (int j = LS.head[i]; j != -1; j = LS.edge[j].next) {
                    out << i << " " << LS.edge[j].to << " " << LS.edge[i].bias << std::endl;
                }
            }
            return out;
        }

    private:
        struct Edge {
            int next;
            int to;
            T bias;
//            Edge() = delete;
//            Edge(int n, int t, T v):next(n), to(t), bias(v) {} ;
        };

        bool __direction = false;
        const T INF = std::numeric_limits<T>::max() / 2;
        int *head;
        Edge *edge;
        StarHeap<T> heap;
        int vertexNum;
        int edgeNum;
        int cnt = 0;
    };


}


#endif //ACM_TEMPLATE_SP_H
