//
// Created by miss on 19-1-22.
//

#ifndef ACM_TEMPLATE_GRAPH_H
#define ACM_TEMPLATE_GRAPH_H

#include <vector>

namespace Graph {

    struct Node {
        int v;    //  POINT2
        int w;    //  BIAS
        Node(int _v, int _w) : v(_v), w(_w) {}
    };

    /*
     * Adjacency Matrix
     */
    class Graph {

    private:

    public:

        std::vector<int> Adj[100];    // Method one
        int G[100][100];              // Method two

        int n = 10;    // The num of Node
        bool vis[100] = {false};

        void BFS(int u){
            std::queue<int> q;
            q.push(u);
            vis[u] = true;
            while(!q.empty()){
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; ++v) {
                    if(!vis[v] && G[u][v] != INFINITY){
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }

        void BFSTrave(int q) {
            for (int i = 0; i < n; ++i) {
                if(!vis[i])
                    BFS(q);
            }
        }

        void DFS(int u){
            vis[u] = true;
            for (int i = 0; i < Adj[u].size(); ++i) {
                int v = Adj[u][i];
                if(vis[v] == false){
                    DFS(v);
                }
            }
        }

        void DFSTrave() {
            for (int i = 0; i < n; ++i) {
                if(vis[i] == false)
                    DFS(i);
            }
        }

        void Insert(int x, int v, int w) {
//            Adj2[x].emplace_back(Node(v, w));
        }


        void DFS2(int u) {
            vis[u] = true;
            for (int i = 0; i < n; ++i) {
                if(!vis[i] && G[u][i] != INFINITY){
                    DFS2(i);
                }
            }
        }

        void DFSTrave2() {
            for (int i = 0; i < n; ++i) {
                if(!vis[i])
                    DFS(i);
            }
        }


        struct Node2 {
            int v;
            int layer;
            Node2(int _v, int _layer):v(_v), layer(_layer) {};
        };

        std::vector<Node2> Adj2[100];
        void BFS2(int s) {   // s is the start element's number
            std::queue<Node2> q;
            q.push(Node2(s, 0));
            vis[s] = true;
            while(!q.empty()) {
                Node2 topNode = q.front();
                q.pop();
                int u = topNode.v;
                for (int i = 0; i < Adj2[u].size(); ++i) {
                    Node2 next = Adj2[u][i];
                    next.layer = topNode.layer + 1;
                    if(!vis[next.v]) {
                        q.push(next);
                        vis[next.v] = true;
                    }
                }
            }
        }

    };

}

#endif //ACM_TEMPLATE_GRAPH_H
