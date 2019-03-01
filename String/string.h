//
// Created by miss on 2/2/19.
//

#ifndef ACM_TEMPLATE_STRING_H
#define ACM_TEMPLATE_STRING_H

#include <list>
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

    // TridTree Method
    const int MAX_CHAR = 256;

    class SuffixTriedNode {
    public:
        SuffixTriedNode() {
            indexs = new std::list<int>;
            for (int i = 0; i < MAX_CHAR; ++i) {
                children[i] = nullptr;
            }
        }

        void insertSuffix(std::string suffix, int index) {
            indexs->push_back(index);
            if (suffix.length() > 0) {
                int cIndex = static_cast<int>(suffix.at(0));

                if (children[cIndex] == nullptr)
                    children[cIndex] = new SuffixTriedNode();

                children[cIndex]->insertSuffix(suffix.substr(1), index + 1);
            }
        }

        std::list<int> *search(std::string s) {
            if (s.length() == 0)
                return indexs;

            int cIndex = static_cast<int>(s.at(0));
            if (children[cIndex] != nullptr)
                return (children[cIndex])->search(s.substr(1));
            else return nullptr;
        }

    private:
        SuffixTriedNode *children[MAX_CHAR];
        std::list<int> *indexs;
    };

    class SuffixTrid {
    private:
        SuffixTriedNode root;
    public:
        SuffixTrid(std::string txt) {
            for (int i = 0; i < txt.length(); ++i) {
                root.insertSuffix(txt.substr(i), i);
            }
        }

        void search(std::string pat) {
            std::list<int> *result = root.search(pat);

            if (result == nullptr)
                std::cout << "Pattern not found" << std::endl;
            else {
                std::list<int>::iterator i;
                int patLen = pat.length();
                for (i = result->begin(); i != result->end(); ++i)
                    std::cout << "Pattern found at position " << *i - patLen << std::endl;
            }

        }
    };

}

#endif //ACM_TEMPLATE_STRING_H
