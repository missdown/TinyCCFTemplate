//
// Created by miss on 2/2/19.
//

#ifndef ACM_TEMPLATE_DP_H
#define ACM_TEMPLATE_DP_H

#include <iostream>
#include <algorithm>
#include <cstring>

namespace DP {

    const int maxn = 100;

    int Factorial(int n) {
        int dp[1000];
        std::fill(dp, dp + 1000, -1);
        if (n == 0 || n == 1) return 1;
        if (dp[n] != -1) return dp[n];
        else {
            dp[n] = Factrial(n - 1) + Factrial(n - 2);
            return dp[n];
        }
    }

    int NumberTower() {
        int f[maxn][maxn], dp[maxn][maxn];
        int n = 5;
        f[1][1] = 5;f[2][1] = 8;f[2][2] = 3;f[3][1] = 12;f[3][2] = 7;
        f[3][3] = 16;f[4][1] = 4;f[4][2] = 10;f[4][3] = 11;f[4][4] = 6;
        f[5][1] = 9;f[5][2] = 5;f[5][3] = 3;f[5][4] = 9;f[5][5] = 4;

        for (int i = 1; i <= n ; ++i) {
            dp[n][i] = f[n][i];                // Boundary
        }

        for (int i = n - 1; i >= 1; --i) {
            for (int j = 1; j <= i ; ++j) {
                dp[i][j] = std::max(dp[i + 1][j], dp[i + 1][j + 1]) + f[i][j];
            }
        }
        return dp[1][1];
    }


    const int maxn2 = 10010;

    int LongestSequenze() {
        int A[maxn2] = {-2, 11, -4, 13, -5, -2}, dp2[maxn2];
        int n = 6;

        dp2[0] = A[0];   // Boundary
        for (int i = 0; i < n; ++i) {
            dp2[i] = std::max(A[i], dp2[i - 1] + A[i]);
        }
        int k = 0;
        for (int j = 1; j < n; ++j) {
            if(dp2[j] > dp2[k])
                k = j;
        }
        return dp2[k];
    }

    int LIS() {
        int A[maxn2] = {0, 1, 2, 3, -9, 3, 9, 0, 11}, dp2[maxn2];
        int n = 8;
        int ans = -1;
        for (int i = 1; i <= n; ++i) {
            dp2[1] = 1;
            for (int j = 1; j < i; ++j) {
                if(A[i] >= A[j] && (dp2[j] + 1 > dp2[i]))
                    dp2[i] = dp2[j] + 1;
            }
            ans = std::max(ans, dp2[i]);
        }
        return ans;
    }

    const int N = 100;


    int LCS() {
        char string1[N]=" sadstory";
        char string2[N]=" adminsorry";
        int LCSdp[N][N];
        int lenA = strlen(string1+1);
        int lenB = strlen(string2 + 1);
        for (int i = 0; i < lenA; ++i) {
            LCSdp[i][0] = 0;
        }
        for (int j = 0; j < lenB; ++j) {
            LCSdp[0][j] = 0;
        }
        for (int i = 1; i <= lenA; ++i) {
            for (int j = 1; j <= lenB ; ++j) {
                if(string1[i] == string2[j]) {
                    LCSdp[i][j] = LCSdp[i - 1][j - 1] + 1;
                }else {
                    LCSdp[i][j] = std::max(LCSdp[i - 1][j], LCSdp[i][j - 1]);
                }
            }
        }
//        for (int i = 1; i <= lenA; ++i) {
//            for (int j = 1; j <= lenB ; ++j) {
//                std::cout << LCSdp[i][j] << " ";
//            }
//            std::cout << std::endl;
//        }
        std::string ss = "";
        int i = lenA - 1;
        int j = lenB - 1;
        while (i != -1 && j != -1){
                if(string1[i+1] == string2[j+1]) {
                    ss += string1[i + 1];
                    --i;
                    --j;
                }else{
                    if(LCSdp[i + 1][j + 1] == LCSdp[i][j]) {
                        --i;
                        --j;
                    }else {
                        if(LCSdp[i][j + 1] >= LCSdp[i + 1][j])
                            i--;
                        else
                            j--;
                    }
                }
            }
        for (unsigned long k = ss.size(); k > 0; --k) {
            std::cout << ss[k - 1] << "";
        }
        std::cout << std::endl;
        return LCSdp[lenA][lenB];
    }

    const int maxn3 = 1010;
    int Backword() {
        char S[maxn3] = "PATZJUJZTACCBCC";
        int dp[maxn3][maxn3];
        int len = strlen(S), ans = 1;
        memset(dp, 0, sizeof(dp));

        // Boundary
        for (int i = 0; i < len; ++i) {
            dp[i][i] = 1;
            if(i < len - 1) {
                if(S[i] == S[i + 1]) {
                    dp[i][i + 1] = 1;
                    ans = 2;
                }
            }
        }
        // Function
        for (int L = 3; L <= len ; ++L) {
            for (int i = 0; i + L - 1 < len; ++i) {
                int j = i + L - 1;
                if(S[i] == S[j] && dp[i + 1][j - 1] == 1) {
                    dp[i][j] = 1;
                    ans = L;
                }
            }
        }
        return ans;
    }

    int ManacherInit(char * s_new, char* st) {
        int len = strlen(st);
        s_new[0] = '$';  //防止越界
        s_new[1] = '#';
        int j = 2;
        for (int i = 0; i < len; i++)
        {
            s_new[j++] = st[i];
            s_new[j++] = '#';
        }
        s_new[j] = '\0';  //防止越界
        return j;  // 返回 s_new 的长度
    }

    // O(n)
    int MANACHER() {
        char st[maxn3] = "PATZJUJZTACCBCC";
        char s_new[2 * maxn3];
        int p[2 * maxn3];
        int len = ManacherInit(s_new, st);  // 取得新字符串长度并完成向 s_new 的转换
        int max_len = -1;  // 最长回文长度
        int id = 0;
        int mx = 0;
        for (int i = 1; i < len; i++){
            if (i < mx)
                p[i] = std::min(p[2 * id - i], mx - i);  // 需搞清楚上面那张图含义, mx 和 2*id-i 的含义
            else
                p[i] = 1;
            while (s_new[i - p[i]] == s_new[i + p[i]])  // 不需边界判断，因为左有'$',右有'\0'
                p[i]++;
            // 我们每走一步 i，都要和 mx 比较，我们希望 mx 尽可能的远，这样才能更有机会执行 if (i < mx)这句代码，从而提高效率
            if (mx < i + p[i]){
                id = i;
                mx = i + p[i];
            }
            max_len = std::max(max_len, p[i] - 1);
        }
        return max_len;
    }

    const int maxnthing = 100;
    const int maxnvalue = 1000;

    int ZeroOneBagpack() {
        int n = 5, V = 8;
        int w[maxnthing] = {3, 5, 1, 2, 2};
        int c[maxnthing] = {4, 5, 2, 1, 3};
        int dp[maxnthing];

        // Boundary
        for (int v = 0; v <= V; ++v) {
            dp[v] = 0;
        }
        for (int i = 0; i <= n; ++i) {
            for (int v = V; v >= w[i] ; --v) {
                dp[v] = std::max(dp[v], dp[v - w[i]] + c[i]);
            }
        }
        int max = 0;
        for (int v = 0; v <= V; ++v) {
            if(dp[v] > max)
                max = dp[v];
        }
        return max;
    }

    int FullBagpack() {
        int n = 5, V = 8;
        int w[maxnthing] = {3, 5, 1, 2, 2};
        int c[maxnthing] = {4, 5, 2, 1, 3};
        int dp[maxnthing];

        // Boundary
        for (int v = 0; v <= V; ++v) {
            dp[v] = 0;
        }
        for (int i = 0; i <= n; ++i) {
            for (int v = w[i]; v <= V ; ++v) {
                dp[v] = std::max(dp[v], dp[v - w[i]] + c[i]);
            }
        }
        int max = 0;
        for (int v = 0; v <= V; ++v) {
            if(dp[v] > max)
                max = dp[v];
        }
        return max;
    }


}

#endif //ACM_TEMPLATE_DP_H
