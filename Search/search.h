//
// Created by miss on 19-1-15.
//

#ifndef ACM_TEMPLATE_SEARCH_H
#define ACM_TEMPLATE_SEARCH_H

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>


class Search {

public:
/*
 * Using recursive to solve the DFS problems
 */
    int n, k, x, maxSumSqu = -1, A[1000];
    std::vector<int> temp, ans;

    void DFS(int index, int nowK, int sum, int sumSqu) {
        if (nowK == k && sum == x) {
            if (sumSqu > maxSumSqu) {
                maxSumSqu = sumSqu;
                ans = temp;
            }
            return;
        }
        if (index == n || nowK > k || sum > x) return;
        temp.push_back(A[index]);
        DFS(index + 1, nowK + 1, sum + A[index], sumSqu + A[index] * A[index]);
        temp.pop_back();
        DFS(index + 1, nowK, sum, sumSqu);
    }

/*
 * Using Queue to solve the BFS problems
 */
    void BFS(int s) {
        std::queue<int> q;
/*
 * q.push(s);
 * while(!q.empty()){
 *  top = q.front();
 *  q.pop();
 *  q.push(top.next);
 *  }
 */

    }

private:
};

namespace Huffman {
    std::priority_queue<long long, std::vector<long long>> q;
    int test() {
        int n;
        long long temp, x, y, ans = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &temp);
            q.push(temp);
        }
        while(q.size() > 1) {
            x = q.top();
            q.pop();
            y = q.top();
            q.pop();
            q.push(x + y);
            ans += x + y;
        }
        printf("%lld\n", ans);
        return 0;
    }
}


namespace AVLTree {
    template<typename T>
    struct Node {
        T data;
        int height;
        Node *lchild, *rchild;
    };

    template<typename T>
    class AVLTree {
        using node = Node<T>;
        using node_array = node *;
    public:

        ~AVLTree(){
            __delete(mroot);
        }

        node_array newNode(T v) {
            node_array root = new node;
            root->data = v;
            root->height = 1;
            root->lchild = root->rchild = nullptr;
            return root;
        }

        T FindMax() const {
            return __findMax(mroot)->data;
        }

        T FindMin() const {
            return __findMin(mroot)->data;
        }

        int getHeight(node_array root) const {
            if (root == nullptr) return 0;
            return root->height;
        }

        node_array find(T x) const {
            return __find(mroot, x);
        }

        void insert(int v) {
            __insert(mroot, v);
        }

        void inOrder() const {
            __inOrder(mroot);
            std::cout << std::endl;
        }

        void erase(T v) {
            __deleteNode(mroot, v);
        }


    private:

        node_array mroot = nullptr;

        void __delete(node_array root) {
            if (root == nullptr)
                return ;
            __delete(root->lchild);
            __delete(root->rchild);
            delete root;
        }

        void __inOrder(node_array root) const {
            if (root == nullptr)
                return;
            __inOrder(root->lchild);
            std::cout << root->data << " ";
            __inOrder(root->rchild);
        }

        node_array __deleteNode(node_array root, T v) {
            // STEP 1: PERFORM STANDARD BST DELETE
            if (root == nullptr)
                return root;
            // If the key to be deleted is smaller than the
            // root's key, then it lies in left subtree
            if (v < root->data)
                root->lchild = __deleteNode(root->lchild, v);
                // If the key to be deleted is greater than the
                // root's key, then it lies in right subtree
            else if (v > root->data)
                root->rchild = __deleteNode(root->rchild, v);
                // if key is same as root's key, then This is
                // the node to be deleted
            else {
                // node with only one child or no child
                if ((root->lchild == NULL) || (root->rchild == NULL)) {
                    node_array temp = root->lchild ? root->lchild : root->rchild;
                    // No child case
                    if (temp == NULL) {
                        temp = root;
                        root = NULL;
                    } else // One child case
                        *root = *temp; // Copy the contents of
                    // the non-empty child
                    delete (temp);
                } else {
                    // node with two children: Get the inorder
                    // successor (smallest in the right subtree)
                    node_array temp = __findMin(root->rchild);
                    // Copy the inorder successor's data to this node
                    root->data = temp->data;
                    // Delete the inorder successor
                    root->rchild = __deleteNode(root->rchild, temp->data);
                }
            }
            // If the tree had only one node then return
            if (root == NULL)
                return root;
            // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
            __updateHeight(root);
            // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
            // check whether this node became unbalanced)
            int balance = __getBalanceFactor(root);
            // If this node becomes unbalanced, then there are 4 cases
            // Left Left Case
            if (balance > 1 && __getBalanceFactor(root->lchild) >= 0) {
                __R(root);
                return root;
            }
            // Left Right Case
            if (balance > 1 && __getBalanceFactor(root->lchild) < 0) {
                __L(root->lchild);
                __R(root);
                return root;
            }
            // Right Right Case
            if (balance < -1 && __getBalanceFactor(root->lchild) <= 0) {
                __L(root);
                return root;
            }

            // Right Left Case
            if (balance < -1 && __getBalanceFactor(root->rchild) > 0) {
                __R(root->rchild);
                __L(root);
                return root;
            }
            return root;
        }

        void __insert(node *&root, int v) {
            if (root == nullptr) {
                root = newNode(v);
                return;
            }

            if (v < root->data) {    ///  v < root->data
                __insert(root->lchild, v);
                __updateHeight(root);
                if (__getBalanceFactor(root) == 2) {
                    if (__getBalanceFactor(root->lchild) == 1) {   // Type LL
                        __R(root);
                    } else if (__getBalanceFactor(root->lchild) == -1) { // TYPE LR
                        __L(root->lchild);
                        __R(root);
                    }
                }
            } else {               /// v > root->data
                __insert(root->rchild, v);
                __updateHeight(root);
                if (__getBalanceFactor(root) == -2) {
                    if (__getBalanceFactor(root->rchild) == -1) {   // Type RR
                        __L(root);
                    } else if (__getBalanceFactor(root->rchild) == 1) { // TYPE RL
                        __R(root->rchild);
                        __L(root);
                    }
                }

            }
        }

        node_array __findMax(node_array root) const {
            while (root->rchild != nullptr)
                root = root->rchild;
            return root;
        }

        node_array __findMin(node_array root) const {
            while (root->lchild != nullptr)
                root = root->lchild;
            return root;
        }

        int __getBalanceFactor(node_array root) const {
            return getHeight(root->lchild) - getHeight(root->rchild);
        }


        node_array __find(node_array root, T x) const {
            if (root == nullptr) {
                return nullptr;
            }
            if (x == root->data) {
                return root;
            } else if (x < root->data)
                __find(root->lchild, x);
            else
                __find(root->rchild);
        }

        void __updateHeight(node_array root) {
            root->height = std::max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
        }

        /*
         *       A                       B
         *      / \                     / \
         *     C   B     ----->>       A   E
         *        / \                 / \
         *       D   E               C   D
         */
        void __L(node_array &root) {
            node_array temp = root->rchild;
            root->rchild = temp->lchild;
            temp->lchild = root;
            __updateHeight(root);
            __updateHeight(temp);
            root = temp;
        }

        /*
         *       A                       C
         *      / \                     / \
         *     C   B     ----->>       D   A
         *    / \                         / \
         *   D   E                       E   B
         */
        void __R(node_array &root) {
            node_array temp = root->lchild;
            root->lchild = temp->rchild;
            temp->rchild = root;
            __updateHeight(root);
            __updateHeight(temp);
            root = temp;
        }

    };


};

namespace BinaryTree {
    template<typename T>
    struct Node {
        T data;
        Node *lchild;
        Node *rchild;
//        friend bool operator < (Node &A, Node &B){
//            return A.data < B.data;
//        }
    };

    template<typename T>
    struct Node2 {
        T data;
        int lchild;
        int rchild;
    };

    template<typename T>
    class Tree_array {
        using node = Node2<T>;
        using node_array = node *;
    public:

        int newNode(T v) {
            nlist[index].data = v;
            nlist[index].lchild = nlist[index].rchild = -1;
            return index++;
        }

        void insert(T x) {
            if (index == 0) {
                index = newNode(x);
                return;
            } else
                __insert(nlist[0].lchild, x);
        }


    private:
        int index = 0;
        node nlist[1000];


        void __insert(int &root, T x) {
            if (nlist[root].data == -1) {
                newNode(x);
                return;
            }

            if (x < nlist[root].data)
                __insert(nlist[root].lchild, x);
            else if (x > nlist[root].data)
                __insert(nlist[root].rchild, x);
            else
                return;
        }

    };


    template<typename T>
    class Tree {
        using node = Node<T>;
        using node_array = node *;
    public:
        ~Tree(){
            __delete(mroot);
        }

        node_array NewNode(const T v) {
            auto Node = new node;
            Node->data = v;
            Node->lchild = Node->rchild = nullptr;
            return Node;
        }

        /*
         * Create binary tree from PreOrder array and inOrder array
         */
        node_array creatFromPI(int preL, int preR, int inL, int inR, const int pre[], const int in[]) {
            if (preL > preR)
                return nullptr;
            auto root = new node;
            root->data = pre[preL];
            int k;
            for (k = inL; k <= inR; ++k) {
                if (in[k] == pre[preL])
                    break;
            }
            int numLeft = k - inL;

            root->lchild = creatFromPI(preL + 1, preL + numLeft, inL, k - 1, pre, in);
            root->rchild = creatFromPI(pre + numLeft + 1, preR, k + 1, inR, pre, in);
            return root;
        }

        void erase(T x) {
            return __erase(mroot, x);
        }


        void preOrder() const {
            __preOrder(mroot);
            std::cout << std::endl;
        }

        void inOrder() const {
            __inOrder(mroot);
            std::cout << std::endl;
        }

        void postOrder() const {
            __postOrder(mroot);
            std::cout << std::endl;
        }

        void LayerOrder() const {
            __LayerOrder(mroot);
            std::cout << std::endl;
        }

        T FindMax() const {
            return __findMax(mroot)->data;
        }

        T FindMin() const {
            return __findMin(mroot)->data;
        }

        void insert(const T x) {
            if (mroot == nullptr) {
                mroot = NewNode(x);
                return;
            } else
                __insert(x, mroot);
        }

        node_array find(const T x) const {
            return __find(x, mroot);
        }

    private:

        node_array mroot = nullptr;

        void __delete(node_array root) {
            if (root == nullptr)
                return ;
            __delete(root->lchild);
            __delete(root->rchild);
            delete root;
        }

        void __erase(node_array &root, int x) {
            if (root == nullptr) return;
            if (root->data == x) {
                if (root->lchild == nullptr && root->rchild == nullptr){
                    delete root;
                    root = nullptr;
                }
                else if (root->lchild != nullptr) {
                    node_array pre = __findMax(root->lchild);
                    root->data = pre->data;
                    __erase(root->lchild, pre->data);
                } else {
                    node_array next = __findMin(root->rchild);
                    root->data = next->data;
                    __erase(root->rchild, next->data);
                }
            } else if (root->data > x) {
                __erase(root->lchild, x);
            } else {
                __erase(root->rchild, x);
            }
        }


        void __preOrder(node_array root) const {
            if (root == nullptr)
                return;
            std::cout << root->data << " ";
            __preOrder(root->lchild);
            __preOrder(root->rchild);

        }

        void __inOrder(node_array root) const {
            if (root == nullptr)
                return;
            __inOrder(root->lchild);
            std::cout << root->data << " ";
            __inOrder(root->rchild);
        }

        void __postOrder(node_array root) const {
            if (root == nullptr)
                return;
            __postOrder(root->lchild);
            __postOrder(root->rchild);
            std::cout << root->data << " ";
        }


        void __LayerOrder(node_array root) const {
            std::queue<node_array> q;
            q.push(root);

            while (!q.empty()) {
                node_array temp = q.front();
                q.pop();
                std::cout << temp->data << " ";
                if (temp->lchild != nullptr) q.push(temp->lchild);
                if (temp->rchild != nullptr) q.push(temp->rchild);
            }
        }


        node_array __find(const T x, node_array root) const {
            if (root == nullptr) {
                return nullptr;
            }
            if (root->data > x)
                __find(x, root->lchild);
            else if (root->data < x)
                __find(x, root->rchild);
            else if (root->data == x) {
                return root;
            }
        }

        void __insert(const T x, node_array &root) {
            if (root == nullptr) {
                root = NewNode(x);
                return;
            }
            if (x < root->data) {
                __insert(x, root->lchild);
            } else if (x > root->data) {
                __insert(x, root->rchild);
            } else return;
        }

        node_array __findMax(node_array root) const {
            while (root->rchild != nullptr)
                root = root->rchild;
            return root;
        }

        node_array __findMin(node_array root) const {
            while (root->lchild != nullptr)
                root = root->lchild;
            return root;
        }

    };
}


#endif //ACM_TEMPLATE_SEARCH_H
