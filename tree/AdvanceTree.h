//
// Created by miss on 2/2/19.
//

#ifndef ACM_TEMPLATE_ADVANCETREE_H
#define ACM_TEMPLATE_ADVANCETREE_H

#include <queue>

namespace ADTree{

#define LSB(i) ((i)&(-i))

    // Binary Indexed Tree
    template <typename T>
    class BIT{
    public:
        BIT(unsigned long num) {
            Tree.resize(num+1);
        }

        int Sum(int i) const {
            int sum = 0;
            i++;
            while(i > 0)
                sum += Tree[i], i -= LSB(i);
            return sum;
        }

        void Build(std::vector<T>& A){
            for (int i = 0; i < A.size(); ++i) {
                update(i, A[i]);
            }
        }

        void update(int i, int k) {
            i++;
            while (i <= Tree.size())
                Tree[i] += k, i += LSB(i);
        }

    private:
        std::vector<T> Tree;
    };


/*
 * 连续区间修改或者单节点更新的动态查询问题
 */
    template <typename T>
    class SegmentTree {
    public:

        SegmentTree(unsigned long maxn):__maxn(maxn){
            Tree.resize(maxn << 2);
            Add.resize(maxn << 2);
        }

        void Build(std::vector<T> &A){
            __Build(A, 1, static_cast<int>(__maxn), 1);
        }

        void Update(int L, int C) {
            __Update(L, C, 1, static_cast<int>(__maxn), 1);
        }

        void Update(int L, int R, int C){
            __Update(L, R, C, 1, static_cast<int>(__maxn), 1);
        }
        /*
         * Get the Sum Value
         */

        T Query(int L, int R) {
            return __Query(L, R, 1, static_cast<int>(__maxn), 1);
        }

        T QueryMin(int L, int R, std::vector<T>& A){
            return __QueryMin(L, R, 1, static_cast<int>(__maxn), 1, A);
        }

    private:

        T __QueryMin(int L, int R, int l, int r, int rt, std::vector<T>& A){

            if (L > r || R < l)
                return -1;

            if(L <= l && r <= R)
                return Tree[rt];
            int p1, p2;
            int m = (l + r) >> 1;
            p1 = __QueryMin(L, R, l, m, rt << 1, A);
            p2 = __QueryMin(L, R, m + 1, r, rt << 1|1, A);
            //return the position where the overall
            //minimum is
            if (p1 == -1)
                return p2;
            if (p2 == -1)
                return p1;
            if (A[p1] <= A[p2])
                return p1;
            return p2;

        }

        T __Query(int L, int R, int l, int r, int rt){
            if(L <= l && r <= R) {
                return Tree[rt];
            }
            int m = (l + r) >> 1;
            __PushDown(rt, m-l+1, r - m);
            int ans = 0;
            if(L <= m) ans += __Query(L, R, l, m, rt<<1);
            if(m < R) ans += __Query(L, R, m+1, r, rt << 1|1);
            return ans;
        }

        void __Update(int L, int C, int l, int r, int rt){
            if(l == r) {
                Tree[rt] += C;
                return ;
            }
            int m = (l + r) >> 1;
//            __PushDown(rt, m-l+1, r - m);
            if(L <= m) __Update(L, C, l, m,rt << 1);
            else __Update(L, C, m+1, r, rt << 1|1);
            __PushUp(rt);
        }

        void __Update(int L, int R, int C, int l, int r, int rt){
            if(L <= l && r <= R) {
                Tree[rt] += C*(r - l + 1);
                Add[rt] += C;
                return ;
            }
            int m = (l + r) >> 1;
            __PushDown(rt, m-l+1, r - m);
            if(L <= m) __Update(L, R, C, l, m,rt << 1);
            if(R > m) __Update(L, R, C, m+1, r, rt << 1|1);
            __PushUp(rt);
        }

        void __Build(std::vector<T> &A, int l, int r, int rt) {
            Add[rt] = 0;
            if(l == r) {  // Getting the end of the tree
                Tree[rt] = A[l];
                return;
            }
            int m = (l + r) >> 1;
            __Build(A, l, m, rt << 1);
            __Build(A, m + 1, r, rt << 1|1);
            __PushUp(rt);
        }

        void __PushUp(int rt) {
            Tree[rt] = Tree[rt<<1] + Tree[rt<<1|1];
        }

        void __PushDown(int rt, int ln, int rn) {
            if(Add[rt]) {
                Add[rt << 1] += Add[rt];
                Add[rt << 1|1] + Add[rt];
                Tree[rt << 1] += Add[rt] * ln;
                Tree[rt << 1|1] += Add[rt] * rn;
                Add[rt] = 0;
            }
        }

        const unsigned long __maxn;
        std::vector<T> Tree;
        std::vector<T> Add;
    };

    template <typename T>
    class SegmentTree2{
    public:
        SegmentTree2(unsigned long maxn):__maxn(maxn){
            Tree.resize(maxn << 2);
            Add.resize(maxn << 2);
        }

        void Build(std::vector<T> &A){
            N = 1;while(N < A.size() + 2) N <<= 1;
            for (int i = 0; i < A.size(); ++i)
                Tree[N+i] = A[i];
            for (int i = N - 1; i > 0 ; --i) {
                Tree[i] = Tree[i << 1] + Tree[i << 1|1];
                Add[i] = 0;
            }
        }
        // Point Version
        void Update(int L, int C){
            for (int i = N + L; i ; i >>= 1) {
                Tree[i] += C;
            }
        }
        // Point Ver.
        T Query(int L, int R) {
            int ans = 0;
            for (int i = N + L - 1, t = N + R + 1; i^t^1;i>>=1,t>>=1){
                if(~i&1) ans += Tree[i^1];
                if(t&1) ans += Tree[t^1];
            }
            return ans;
        }

        // Interval Version.
        void Update(int L, int R, int C) {
            int s,t,Ln=0,Rn=0,x=1;
            //Ln:  s一路走来已经包含了几个数
            //Rn:  t一路走来已经包含了几个数
            //x:   本层每个节点包含几个数
            for(s=N+L-1,t=N+R+1;s^t^1;s>>=1,t>>=1,x<<=1){
                //更新Sum
                Tree[s] += C* Ln;
                Tree[t] += C * Rn;
                //处理Add
                if(~s&1) Add[s^1]+=C, Tree[s^1] += C * x,Ln += x;
                if( t&1) Add[t^1]+=C, Tree[t^1] += C * x,Rn += x;
            }
            //更新上层Sum
            for(;s;s>>=1,t>>=1){
                Tree[s] += C * Ln;
                Tree[t] += C * Rn;
            }
        }

        // Interval Ver.
        T IQuery(int L, int R){
            int s, t, Ln = 0, Rn = 0, x = 1, ans = 0;
            for(s = N + L - 1,t = N + R + 1; s ^ t ^ 1; s>>=1, t>>=1, x<<=1){
                if(Add[s]) ans+=Add[s]*Ln;
                if(Add[t]) ans+=Add[t]*Rn;
                //常规求和
                if(~s&1) ans+=Tree[s^1],Ln+=x;
                if( t&1) ans+=Tree[t^1],Rn+=x;

            }

            for(;s;s>>=1,t>>=1){
                ans+=Add[s]*Ln;
                ans+=Add[t]*Rn;
            }
            return ans;

        }
    private:
        std::vector<T> Tree;
        std::vector<T> Add;
        int N;
        const unsigned long __maxn;
    };



    template <typename T>
    class RBTree{

        enum Color {
            RED, BLACK
        };

        class RBNode {
        public:
            T data;
            Color color;
            RBNode *left, *right, *parent;

            explicit RBNode(T data) : data(data) {
                left = right = parent = nullptr;
                color = RED;
            }

            RBNode *uncle() {
                if (parent == nullptr || parent->parent == nullptr)
                    return nullptr;

                if (parent->isOnLeft())
                    return parent->parent->right;
                else
                    return parent->parent->left;
            }

            bool isOnLeft() {
                return this == parent->left;
            }

            RBNode *sibling() {
                if (parent == nullptr)
                    return nullptr;
                if (isOnLeft())
                    return parent->right;
                else
                    return parent->left;
            }

            void moveDown(RBNode *nParent) {
                if (parent != nullptr) {
                    if (isOnLeft()) {
                        parent->left = nParent;
                    } else {
                        parent->right = nParent;
                    }
                }
                nParent->parent = parent;
                parent = nParent;
            }

            bool hasRedChild() {
                return (left != nullptr and left->color == RED) or (right != nullptr and right->color == RED);
            }
        };

        using Node_array = RBNode *;
    public:
        RBTree() {
            mroot = nullptr;
        }

        Node_array getRoot() { return mroot; }

        Node_array search(T n) {
            Node_array temp = mroot;
            while (temp != nullptr) {
                if (n < temp->data) {
                    if (temp->left == nullptr)
                        break;
                    else
                        temp = temp->left;
                } else if (n == temp->data) {
                    break;
                } else {
                    if (temp->right == nullptr)
                        break;
                    else
                        temp = temp->right;
                }
            }
            return temp;
        }

        void insert(T n) {
            Node_array newNode = new RBNode(n);
            if (mroot == nullptr) {
                newNode->color = BLACK;
                mroot = newNode;
            } else {
                Node_array temp = search(n);
                if (temp->data == n) {
                    return;
                }
                newNode->parent = temp;
                if (n < temp->data)
                    temp->left = newNode;
                else
                    temp->right = newNode;
                fixRedRed(newNode);
            }
        }

        void deleteByVal(T n) {
            if (mroot == nullptr)
                return;
            Node_array v = search(n), u;
            if (v->data != n) {
                return;
            }
            deleteNode(v);
        }

        void InOrder() {
            std::cout << "Inorder: " << std::endl;
            if (mroot == nullptr)
                std::cout << "Tree is empty" << std::endl;
            else
                inOrder(mroot);
            std::cout << std::endl;
        }

        void LevelOrder() {
            std::cout << "Level order: " << std::endl;
            if (mroot == nullptr)
                std::cout << "Tree is empty" << std::endl;
            else
                levelOrder(mroot);
            std::cout << std::endl;
        }

    private:
        Node_array mroot;

        void leftRotate(Node_array x) {
            Node_array nParent = x->right;
            if (x == mroot)
                mroot = nParent;
            x->moveDown(nParent);
            x->right = nParent->left;
            if (nParent->left != nullptr)
                nParent->left->parent = x;
            nParent->left = x;
        }

        void rightRotate(Node_array x) {
            Node_array nParent = x->left;

            if (x == mroot)
                mroot = nParent;
            x->moveDown(nParent);

            x->left = nParent->right;

            if (nParent->right != nullptr)
                nParent->right->parent = x;

            nParent->right = x;
        }

        void swapColors(Node_array x1, Node_array x2) {
            Color temp = x1->color;
            x1->color = x2->color;
            x2->color = temp;
        }

        void swapValues(Node_array x1, Node_array x2) {
            T data = x1->data;
            x1->data = x2->data;
            x2->data = data;
        }

        void fixRedRed(Node_array x) {
            if (x == mroot) {
                x->color = BLACK;
                return;
            }

            Node_array parent = x->parent, grandparent = parent->parent, uncle = x->uncle();

            if (parent->color != BLACK) {
                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    fixRedRed(grandparent);
                } else {
                    if (parent->isOnLeft()) {
                        if (x->isOnLeft()) {
                            swapColors(parent, grandparent);
                        } else {
                            leftRotate(parent);
                            swapColors(x, grandparent);
                        }
                        rightRotate(grandparent);
                    } else {
                        if (x->isOnLeft()) {
                            rightRotate(parent);
                            swapColors(x, grandparent);
                        } else {
                            swapColors(parent, grandparent);
                        }
                        leftRotate(grandparent);
                    }
                }
            }
        }

        Node_array successor(Node_array x) {
            Node_array temp = x;
            while (temp->left != nullptr)
                temp = temp->left;
            return temp;
        }

        Node_array BSTreplace(Node_array x) {
            if (x->left != nullptr && x->right != nullptr)
                return successor(x->right);
            if (x->left == nullptr && x->right == nullptr)
                return nullptr;
            if (x->left != nullptr)
                return x->left;
            else
                return x->right;
        }

        void deleteNode(Node_array v) {
            Node_array u = BSTreplace(v);
            bool uvBlack = ((u == nullptr || u->color == BLACK) && (v->color == BLACK));
            Node_array parent = v->parent;

            if (u == nullptr) {
                if (v == mroot) {
                    mroot = nullptr;
                } else {
                    if (uvBlack) {
                        fixDoubleBlack(v);
                    } else {
                        if (v->sibling() != nullptr)
                            v->sibling()->color = RED;
                    }

                    // delete v from the tree
                    if (v->isOnLeft()) {
                        parent->left = nullptr;
                    } else {
                        parent->right = nullptr;
                    }
                }
                delete v;
                return;
            }

            if (v->left == nullptr || v->right == nullptr) {
                if (v == mroot) {
                    v->data = u->data;
                    v->left = v->right = nullptr;
                    delete u;
                } else {
                    if (v->isOnLeft()) {
                        parent->left = u;
                    } else {
                        parent->right = u;
                    }
                    delete v;
                    u->parent = parent;
                    if (uvBlack) {
                        fixDoubleBlack(u);
                    } else {
                        u->color = BLACK;
                    }
                }
                return;
            }
            swapValues(u, v);
            deleteNode(u);
        }

        void fixDoubleBlack(Node_array x) {
            if (x == mroot)
                return;

            Node_array sibling = x->sibling(), parent = x->parent;
            if (sibling == nullptr) {
                fixDoubleBlack(parent);
            } else {
                if (sibling->color == RED) {
                    parent->color = RED;
                    sibling->color = BLACK;
                    if (sibling->isOnLeft()) {
                        rightRotate(parent);
                    } else {
                        leftRotate(parent);
                    }
                    fixDoubleBlack(x);
                } else {
                    if (sibling->hasRedChild()) {
                        if (sibling->left != nullptr and sibling->left->color == RED) {
                            if (sibling->isOnLeft()) {
                                // left left
                                sibling->left->color = sibling->color;
                                sibling->color = parent->color;
                                rightRotate(parent);
                            } else {
                                // right left
                                sibling->left->color = parent->color;
                                rightRotate(sibling);
                                leftRotate(parent);
                            }
                        } else {
                            if (sibling->isOnLeft()) {
                                // left right
                                sibling->right->color = parent->color;
                                leftRotate(sibling);
                                rightRotate(parent);
                            } else {
                                // right right
                                sibling->right->color = sibling->color;
                                sibling->color = parent->color;
                                leftRotate(parent);
                            }
                        }
                        parent->color = BLACK;
                    } else {
                        sibling->color = RED;
                        if (parent->color == BLACK)
                            fixDoubleBlack(parent);
                        else
                            parent->color = BLACK;
                    }
                }
            }
        }

        void levelOrder(Node_array x) {
            if (x == nullptr)
                return;
            std::queue<Node_array> q;
            Node_array curr;

            q.push(x);

            while (!q.empty()) {
                curr = q.front();
                q.pop();
                std::cout << curr->data << " ";
                if (curr->left != nullptr)
                    q.push(curr->left);
                if (curr->right != nullptr)
                    q.push(curr->right);
            }
        }

        void inOrder(Node_array x) {
            if (x == nullptr)
                return;
            inOrder(x->left);
            std::cout << x->data << " ";
            inOrder(x->right);
        }

    };

    template<typename T>
    class BTree {
        class BTreeNode {
        public:
            int *keys;

        private:
        };

    public:
    private:
    };

}

#endif //ACM_TEMPLATE_ADVANCETREE_H
