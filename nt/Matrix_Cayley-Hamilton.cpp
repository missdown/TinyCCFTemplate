//
// Created by miss on 3/8/19.
//

/*
 * 给定数列 {hn}前k项，其后每一项满足
    hn = a1*h(n-1) + a2*h(n-2) + … + ak*h(n-k)
    其中 a1,a2…ak 为给定数列。请计算 h(n)，并将结果对 1000000007 取模输出。
    对于 100% 数据，满足 n <= 10^9;k <= 2000; abs(hi)<=10^9; abs(ai)<=10^9
 *
 *大概就是先把状态转移矩阵A画出来，不难发现A的特征多项式就是xk−∑i=1kai∗xk−ixk−∑i=1kai∗xk−i。
设f(x)=xk−∑i=1kai∗xk−if(x)=xk−∑i=1kai∗xk−i，根据Cayley-Hamilton定理可以得到f(A)=0f(A)=0。
那么An=Anmodf(A)An=Anmodf(A)。
于是我们可以先快速幂求出xnmodf(x)xnmodf(x)的值，设为∑i=0k−1ci∗xi∑i=0k−1ci∗xi然后把AA带到xx里面，我们要求的是AnH=∑i=0k−1ci∗Ai∗HAnH=∑i=0k−1ci∗Ai∗H的最后一个元素。
就等于∑i=0k−1ci∗hi+k∑i=0k−1ci∗hi+k。
那么我们可以先O(k2)O(k2)把hk...2khk...2k求出来然后直接算即可。
 */

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

typedef long long LL;

const int N = 4005;
const int MOD = 1000000007;

int n, k, a[N], c[N], mo[N], tmp[N], ans[N], b[N];

int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

void mul(int *a, int *b, int *c) {
    for (int i = 0; i <= k * 2 - 2; i++) tmp[i] = 0;
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            tmp[i + j] += (LL) a[i] * b[j] % MOD, tmp[i + j] -= tmp[i + j] >= MOD ? MOD : 0;
    for (int i = k * 2 - 2; i >= k; i--)
        for (int j = k - 1; j >= 0; j--)
            tmp[i - k + j] += MOD - (LL) tmp[i] * mo[j] % MOD, tmp[i - k + j] -= tmp[i - k + j] >= MOD ? MOD : 0;
    for (int i = 0; i < k; i++) c[i] = tmp[i];
}

int main() {
    n = read();
    k = read();
    for (int i = 1; i <= k; i++) c[i] = read(), c[i] += c[i] < 0 ? MOD : 0;
    for (int i = 1; i <= k; i++) a[i] = read(), a[i] += a[i] < 0 ? MOD : 0;
    for (int i = 1; i <= k; i++) mo[k - i] = MOD - c[i];
    mo[k] = 1;
    b[1] = 1;
    ans[0] = 1;
    for (n -= k - 1; n; n >>= 1) {
        if (n & 1) mul(ans, b, ans);
        mul(b, b, b);
    }
    for (int i = k + 1; i <= k * 2 - 1; i++)
        for (int j = 1; j <= k; j++)
            a[i] += (LL) a[i - j] * c[j] % MOD, a[i] -= a[i] >= MOD ? MOD : 0;
    int tot = 0;
    for (int i = 0; i <= k - 1; i++) tot += (LL) ans[i] * a[k + i] % MOD, tot -= tot >= MOD ? MOD : 0;
    printf("%d", tot);
    return 0;
}
