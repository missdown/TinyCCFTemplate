//
// Created by miss on 2/2/19.
//

#ifndef ACM_TEMPLATE_ADVANCETREE_H
#define ACM_TEMPLATE_ADVANCETREE_H

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
    struct RBNode {
        T data;
        bool color;
        RBNode* left, *right, *parent;

        RBNode(T data):data(data) {left = right = parent = nullptr}
    };

    template <typename T>
    class RBTree{
    public:


    private:
        enum Color{RED, BLACK};


    };
}

#endif //ACM_TEMPLATE_ADVANCETREE_H
