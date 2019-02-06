//
// Created by miss on 2/2/19.
//

#ifndef ACM_TEMPLATE_STRING_H
#define ACM_TEMPLATE_STRING_H

namespace String{
    const int maxn = 100;
    int next[maxn];
    int nextpro[maxn];
    void getNext(const char s[], int len) {
        int j = -1;
        next[0] = -1;
        for (int i = 1; i < len; ++i) {
            while(j!= -1 && s[i] != s[j + 1])
                j = next[j];
            if(s[i] == s[j + 1])
                j++;
            next[i] = j;
        }
    }

    void getNextPro(const char s[], int len){
        int j = -1;
        nextpro[0] = -1;
        for (int i = 1; i < len; ++i) {
            while(j!= -1 && s[i] != s[j + 1])
                j = nextpro[j];
            if(s[i] == s[j + 1])
                j++;

            if(j == -1 || s[i + 1] != s[j + 1])
                nextpro[i] = j;
            else
                nextpro[i] = nextpro[j];
        }

    }

    bool KMP(const char text[], const char pattern[]) {
        int n = strlen(text), m = strlen(pattern);
        getNext(pattern, m);
        int j = -1;
//        for (int i = 0; i < m; ++i) {
//            std::cout << next[i] << " ";
//        }
        std::cout << std::endl;
        for (int i = 0; i < n; ++i) {
            while(j != -1 && text[i] != pattern[j + 1])
                j = next[j];
            if(text[i] == pattern[j + 1])
                j++;
            if(j == m - 1)
                return true;
        }
        return false;
    }

    int KMPN(const char text[], const char pattern[]) {
        int n = strlen(text), m = strlen(pattern);
        getNextPro(pattern, m);
        int ans = 0, j = -1;
        for (int i = 0; i < n; ++i) {
            while(j != -1 && text[i] != pattern[j + 1])
                j = nextpro[j];
            if(text[i] == pattern[j + 1])
                j++;
            if(j == m - 1) {
                ans++;
                j = nextpro[j];
            }
        }
        return ans;
    }

}

#endif //ACM_TEMPLATE_STRING_H
