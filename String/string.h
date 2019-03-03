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
            if (!s.length())
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


    class AcMachine {
        const static int MAXS = 500; // MAX number of states in the matching machine
        const static int MAXC = 26;  // MAX number of characters in input alphabet
    public:
        AcMachine() {
        };

        void SearchWords(std::string text) {
            BuildTree();
            int currentState = 0;
            for (int i = 0; i < text.size(); ++i) {
                currentState = FindNextState(currentState, text[i]);
                if (!out[currentState])
                    continue;

                // Match found, print all matching words of arr[]
                for (int j = 0; j < stringlist.size(); ++j) {
                    if (out[currentState] & (1 << j)) {
                        std::cout << "Word \"" << stringlist[j] << "\" from " << i - stringlist[j].size() + 1 << " to "
                                  << i << std::endl;
                    }
                }
            }
        }

        void Insert(const std::string &s) {
            stringlist.push_back(s);
        }

        void test() {
            Insert("sunxiaochuan");
            Insert("nm$l");
            Insert("renren");

            std::string text = "sunxiaochuannmslnmlrenrendoushisunxiaochuan";

            SearchWords(text);
        }


    private:

        int BuildTree() {
            // Init arrays.
            memset(out, 0, sizeof(out));
            memset(g, -1, sizeof(g));

            int states = -1;
            // Cinstruct values for goto function
            for (int i = 0; i < stringlist.size(); ++i) {
                const std::string &word = stringlist[i];
                int currentState = 0;
                for (auto ch : word) {
                    ch -= 'a';

                    if (g[currentState][static_cast<int>(ch)] == -1)
                        g[currentState][static_cast<int>(ch)] = states++;
                    currentState = g[currentState][static_cast<int>(ch)];
                }

                // Add current word in output function
                out[currentState] |= (1 << i);
            }

            // For all characters which don't have an edge from root(or state 0) in Trie, add an edge to state 0 itself
            for (int ch = 0; ch < MAXC; ++ch) {
                if (g[0][ch] == -1)
                    g[0][ch] = 0;
            }

            // Initialize values in fail function
            memset(f, -1, sizeof(f));

            // Using BFS
            std::queue<int> q;
            for (int ch = 0; ch < MAXC; ++ch) {
                if (g[0][ch] != 0) {
                    f[g[0][ch]] = 0;
                    q.push(g[0][ch]);
                }
            }

            // For the removed state, find failure function for all those characters for which got ot function is not defined
            while (!q.empty()) {
                int state = q.front();
                q.pop();
                for (int ch = 0; ch <= MAXC; ++ch) {
                    if (g[state][ch] != -1) {
                        // Find failure state of removed state.
                        int failure = f[state];

                        while (g[failure][ch] == -1)
                            failure = f[failure];
                        failure = g[failure][ch];
                        f[g[state][ch]] = failure;
                        // Merge output values
                        out[g[state][ch]] |= out[failure];
                        // Insert the next level node (of Trie) in Queue
                        q.push(g[state][ch]);
                    }
                }
            }
            return states;
        }

        int FindNextState(int currentState, char nextInput) {
            int answer = currentState;
            int ch = nextInput - 'a';

            // IF goto is not defined, use failure function
            while (g[answer][ch] == -1)
                answer = f[answer];

            return g[answer][ch];
        }

        int f[MAXS]; // Failure function
        int g[MAXS][MAXC]; // GOTO function
        int out[MAXS];

        std::vector<std::string> stringlist;

    };

    class AcMachion2 {
        struct TreeNode {
            int fail = 0;
            int vis[26] = {0};
            int end = 0;
        };
        using Node = TreeNode;
        using Node_array = TreeNode *;
    public:
        AcMachion2() {

        }

        void Build(const std::string s) {
            int now = 0; // Current pointer
            for (auto i : s) {
                while (now >= TrieTree.size()) {
                    TrieTree.emplace_back(Node());
                }
                if (TrieTree[now].vis[i - 'a'] == 0)
                    TrieTree[now].vis[i - 'a'] = ++cnt;
                now = TrieTree[now].vis[i - 'a'];
            }
            TrieTree[now].end += 1;
        }

        int ACSearching(std::string s) {
            TrieTree[0].fail = 0;
            GetFail();
            int now = 0, ans = 0;
            for (auto i : s) {
                now = TrieTree[now].vis[i - 'a'];
                for (int t = now; t && TrieTree[t].end != -1; t = TrieTree[t].fail)//循环求解
                {
                    ans += TrieTree[t].end;
                    TrieTree[t].end = -1;
                }
            }
            return ans;
        }

        void test() {
            Build("sunxiaochuan");
            Build("nm$l");
            Build("renren");

            std::string text = "sunxiaochuannmslnmlrenrendoushisunxiaochuan";

            std::cout << ACSearching(text) << std::endl;
        }

    private:

        void GetFail() {
            std::queue<int> Q;
            for (int i = 0; i < 26; ++i) {
                if (TrieTree[0].vis[i] != 0) {
                    TrieTree[TrieTree[0].vis[i]].fail = 0;
                    Q.push(TrieTree[0].vis[i]);
                }
            }

            while (!Q.empty()) {
                int u = Q.front();
                Q.pop();
                for (int i = 0; i < 26; ++i) {
                    if (TrieTree[u].vis[i] != 0) {
                        TrieTree[TrieTree[u].vis[i]].fail = TrieTree[TrieTree[u].fail].vis[i];
                        Q.push(TrieTree[u].vis[i]);
                    } else  // IF not existed
                        TrieTree[u].vis[i] = TrieTree[TrieTree[u].fail].vis[i];
                }
            }
        }


        int cnt = 0;

        std::vector<TreeNode> TrieTree;
    };

}

#endif //ACM_TEMPLATE_STRING_H
