//
// Created by miss on 2/2/19.
//

#ifndef ACM_TEMPLATE_STRING_H
#define ACM_TEMPLATE_STRING_H

#include <list>
#include <queue>
#include <map>

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


    class WuManber {
        typedef unsigned short WORD;
        const int WORD_SIZE = 65536;
        const int M_VALUE = 5;
        const int B_VALUE = 2;

        typedef struct _NODE {
            _NODE *pNext;     //next node point
            const char *pPattern;  //pattern string
            WORD wPrefix;    //prefix value
        } NODE, *PNODE;

        unsigned char *g_ShiftTable = nullptr;
        PNODE *g_pNode = nullptr;

    public:
        WuManber() : k(0), m(0), m_bInitialized(false) {
            m_ShiftTable = nullptr;
            m_nBitsInShift = 5;
        }

        virtual ~WuManber() {
            if (m_ShiftTable) {
                delete[] m_ShiftTable;
                m_ShiftTable = nullptr;
            }
        }

        bool Initialize(const std::vector<const char *> &patterns,
                        bool bCaseSensitive = false, bool bIncludeSpecialCharacters = false,
                        bool bIncludeExtendedAscii = false) {
            // bIncludeExtendedAscii, bIncludeSpecialCharacters matched as whitespace when false

            k = patterns.size();
            m = 0; // start with 0 and grow from there
            for (unsigned int i = 0; i < k; ++i) {
                size_t lenPattern = strlen(patterns[i]);
                if (B > lenPattern) throw std::runtime_error("found pattern less than B in length");
                m = (0 == m) ? lenPattern : std::min(m, lenPattern);
            }

            m_nSizeOfAlphabet = 1; // at minimum we have a white space character
            for (unsigned short i = 0; i <= 255; ++i) {
                m_lu[i].letter = ' '; // table is defaulted to whitespace
                m_lu[i].offset = 0;  //
                if ((i >= 'a') && (i <= 'z')) {
                    m_lu[i].letter = (char) i; // no problems with lower case letters
                    m_lu[i].offset = m_nSizeOfAlphabet++;
                }
                if (bCaseSensitive) { // case of !bCaseSensitive fixed up later on
                    if ((i >= 'A') && (i <= 'Z')) {
                        m_lu[i].letter = (char) i; // map upper case to lower case
                        m_lu[i].offset = m_nSizeOfAlphabet++;
                    }
                }
                if ((i >= '0') && (i <= '9')) {
                    m_lu[i].letter = (char) i; // use digits
                    m_lu[i].offset = m_nSizeOfAlphabet++;
                }
            }
            if (!bCaseSensitive) {  // fix up upper case mappings ( uppercase comes before lower case in ascii table )
                for (unsigned short i = 'A'; i <= 'Z'; ++i) {
                    char letter = (char) (i - 'A' + 'a');  // map upper case to lower case
                    m_lu[i].letter = letter; // map upper case to lower case
                    m_lu[i].offset = m_lu[static_cast<int>(letter)].offset;
                    // no unique characters so don't increment size
                }
            }
            if (bIncludeSpecialCharacters) {
                for (char *c = rchSpecialCharacters; 0 != *c; ++c) {
                    m_lu[*c].letter = *c;
                    m_lu[*c].offset = m_nSizeOfAlphabet++;
                }
            }
            if (bIncludeExtendedAscii) {
                for (unsigned char *c = rchExtendedAscii; 0 != *c; ++c) {
                    m_lu[*c].letter = static_cast<char>( *c );
                    m_lu[*c].offset = m_nSizeOfAlphabet++;
                }
            }

            //m_nBitsInShift = (unsigned short) ceil( log( (double) m_nSizeOfAlphabet ) / log( (double) 2 ) );
            // can use fewer bits in shift to turn it into a hash

            m_nTableSize = (size_t) pow(pow(2., m_nBitsInShift), static_cast<int>(B));
            // 2 ** bits ** B, will be some unused space when not hashed
            if (m_ShiftTable == nullptr) {
                m_ShiftTable = new unsigned int[m_nTableSize];
                if (m_ShiftTable == nullptr) {
                    return false;
                }

            }


            for (size_t i = 0; i < m_nTableSize; ++i) {
                m_ShiftTable[i] = m - B + 1; // default to m-B+1 for shift
            }

            //m_vPatternMap = new vector<structPatternMap>[ m_nTableSize ];

            for (size_t j = 0; j < k; ++j) {  // loop through patterns
                for (size_t q = m; q >= B; --q) {
                    unsigned int hash;
                    hash = (m_lu[patterns[j][q - 2 - 1]].offset & 0xF); // bring in offsets of X in pattern j
                    hash <<= m_nBitsInShift;
                    hash += (m_lu[patterns[j][q - 1 - 1]].offset & 0xF);
                    hash <<= m_nBitsInShift;
                    hash += (m_lu[patterns[j][q - 1]].offset & 0xF);
                    size_t shiftlen = m - q;
                    m_ShiftTable[hash] = std::min(m_ShiftTable[hash], static_cast<unsigned int>(shiftlen));
                    if (0 == shiftlen) {
                        m_PatternMapElement.ix = j;
                        m_PatternMapElement.PrefixHash = m_lu[patterns[j][0]].offset;
                        m_PatternMapElement.PrefixHash <<= m_nBitsInShift;
                        m_PatternMapElement.PrefixHash += m_lu[patterns[j][1]].offset;
                        m_vPatternMap.insert(std::make_pair(hash, m_PatternMapElement));
                    }
                }
            }
            m_bInitialized = true;
            return true;
        };

        bool Search(size_t TextLength, const char *Text, const std::vector<const char *> &patterns) {
            if (m > TextLength) {
                return false;
            }

            size_t ix = m - 1; // start off by matching end of largest common pattern
            while (ix < TextLength) {
                unsigned int hash1;
                hash1 = (m_lu[Text[ix - 2]].offset & 0xF);
                hash1 <<= m_nBitsInShift;
                hash1 += (m_lu[Text[ix - 1]].offset & 0xF);
                hash1 <<= m_nBitsInShift;
                hash1 += (m_lu[Text[ix]].offset & 0xF);
                size_t shift = m_ShiftTable[hash1];
                if (shift > 0) {
                    ix += shift;
                } else {  // we have a potential match when shift is 0
                    unsigned int hash2;  // check for matching prefixes
                    hash2 = m_lu[Text[ix - m + 1]].offset;
                    hash2 <<= m_nBitsInShift;
                    hash2 += m_lu[Text[ix - m + 2]].offset;
                    /*vector<structPatternMap> &element = m_vPatternMap[ hash1 ];
                    vector<structPatternMap>::iterator iter = element.begin();*/
                    std::multimap<unsigned int, structPatternMap>::iterator iter = m_vPatternMap.lower_bound(hash1);
                    while (m_vPatternMap.upper_bound(hash1) != iter) {
                        if (hash2 == (*iter).second.PrefixHash) {
                            // since prefix matches, compare target substring with pattern
                            const char *ixTarget = Text + ix - m + 3; // we know first two characters already match
                            const char *ixPattern = patterns[(*iter).second.ix] + 2;  // ditto
                            while ((0 != *ixTarget) && (0 != *ixPattern)) { // match until we reach end of either string
                                if (m_lu[*ixTarget].letter ==
                                    m_lu[*ixPattern].letter) {  // match against chosen case sensitivity
                                    ++ixTarget;
                                    ++ixPattern;
                                } else {
                                    break;
                                }
                            }
                            if (0 == *ixPattern) {  // we found the end of the pattern, so match found
                                return true;
                            }
                        }
                        ++iter;
                    }
                    ++ix;
                }
            }
            return false;
        }

        //the length of each string in vector must longer then M_VALUE
        bool BuildShiftTable(std::vector<const char *> vecPattern) {
            bool bRet = false;
            //how long the shift table?  the range of hash value.
            //we use the two characters combine the hash value
            //so the range of hash value is 0 to 65535, need 64k size to store
            g_ShiftTable = new unsigned char[WORD_SIZE];
            if (nullptr == g_ShiftTable) {
                goto Exit0;
            }

            g_pNode = new PNODE[WORD_SIZE];
            if (nullptr == g_pNode) {
                goto Exit0;
            }

            for (int i = 0; i < WORD_SIZE; i++) {
                g_ShiftTable[i] = M_VALUE - 1;
            }
            memset(g_pNode, 0, WORD_SIZE * sizeof(g_pNode[0]));

            for (unsigned int i = 0; i < vecPattern.size(); i++) {
                for (int j = 0; j < M_VALUE - B_VALUE + 1; j++) {
                    WORD wdHash = *(WORD *) (&vecPattern[i][M_VALUE - 1 - j - 1]);
                    if (g_ShiftTable[wdHash] > j)
                        g_ShiftTable[wdHash] = j;
                    if (0 == j)// need save prefix hash value for each pattern, but maybe more than one
                    {
                        if (!InsertNode(wdHash, vecPattern[i], *(WORD *) (&vecPattern[i][0])))
                            goto Exit0;
                    }
                }
            }
            bRet = true;
            Exit0:
            if (!bRet) {
                Release();
            }
            return bRet;
        }

        bool InsertNode(WORD wdHash, const char *pPattern, WORD wPrefix) {
            PNODE pNode = new NODE;
            if (!pNode)
                return false;

            pNode->pPattern = pPattern;
            pNode->pNext = g_pNode[wdHash];
            pNode->wPrefix = wPrefix;
            g_pNode[wdHash] = pNode;

            return true;
        }

        void Release() {
            if (g_ShiftTable) {
                delete[] g_ShiftTable;
                g_ShiftTable = nullptr;
            }
            if (g_pNode) {
                for (int i = 0; i < WORD_SIZE; i++) {
                    while (g_pNode[i]) {
                        PNODE pNext = g_pNode[i]->pNext;
                        delete g_pNode[i];
                        g_pNode[i] = pNext;
                    }
                }
                delete[] g_pNode;
                g_pNode = nullptr;
            }
        }

        void WuManberSearch(const char *pDest) {
            int nLen = strlen(pDest);
            if (nLen < M_VALUE)
                return;

            int nBeginIdx = 0;
            while (nBeginIdx + (M_VALUE - 1) < nLen) {
                WORD wHash = *(WORD *) &pDest[nBeginIdx + (M_VALUE - 1) - 1];
                if (0 != g_ShiftTable[wHash]) {
                    nBeginIdx += g_ShiftTable[wHash];
                } else//hash value identical, maybe find a match
                {
                    PNODE pNode = g_pNode[wHash];
                    while (pNode) {
                        if (pNode->wPrefix == *(WORD *) &pDest[nBeginIdx]) {
                            int i = 0;
                            while (pNode->pPattern[i] && nBeginIdx + i < nLen &&
                                   pNode->pPattern[i] == pDest[nBeginIdx + i]) {
                                i++;
                            }
                            if (pNode->pPattern[i] == 0)//find a match
                            {
                                ReportMatch(nBeginIdx, pNode->pPattern);
                            }
                        }
                        pNode = pNode->pNext;
                    }
                    nBeginIdx++;
                }
            }
        }

        void ReportMatch(int nFindEnd, const char *pPattern) {
            printf("Find at %2d, %s\r\n", nFindEnd, pPattern);
        }

        void TestWuManber() {
            bool b;
            char text[] = "text is abcde 12345";
            std::vector<const char *> vecPattern;
            vecPattern.push_back("abcde");
            vecPattern.push_back("12345");
            vecPattern.push_back("ab345");
            vecPattern.push_back("12cde");
            WuManber wumanber;
            wumanber.Initialize(vecPattern, true);
            b = wumanber.Search(strlen(text), text, vecPattern);
            return;
        }

        void TestWuManber2() {
            char text[] = "text is abcdef 123456 abx456 12xdef 12cdef ab3456 ab3457";
            printf("%s\r\n", text);
            std::vector<const char *> vecPattern;
            vecPattern.push_back("abcdef");
            vecPattern.push_back("123456");
            vecPattern.push_back("ab3456");
            vecPattern.push_back("12cdef");
            BuildShiftTable(vecPattern);
            WuManberSearch(text);
            Release();
            return;
        }

    private:
        size_t k;  // number of patterns;
        size_t m;  // largest common pattern length
        static const size_t B = 3;  // Wu Manber paper suggests B is 2 or 3
        // small number of patterns, use B=2, use an exact table
        // for large number of patterns, use B=3 use compressed table (their code uses 400 as a cross over )
        // this class needs to be adjusted for B=2 (in the build shift table portion)
        static unsigned char rchExtendedAscii[];
        static char rchSpecialCharacters[];

        bool m_bInitialized;

        struct structAlphabet {
            char letter;  // letter for matching purposes
            unsigned char offset; // index of character in offsetted alphabet for shift and hash tables
        } m_lu[256]; // defines our alphabet for matching purposes, is LookUp table of letters for pattern/text matching
        unsigned char m_nSizeOfAlphabet;
        unsigned short m_nBitsInShift; // used for hashing blocks of B characters
        unsigned int m_nTableSize;  // size for SHIFT and HASH tables
        unsigned int *m_ShiftTable;  // SHIFT table
        struct structPatternMap { // one struct per pattern for this hash
            unsigned int PrefixHash;  // hash of first two characters of the pattern
            unsigned int ix;  // index into patterns for final comparison
        } m_PatternMapElement;  // termporary area for element storage
        //vector<structPatternMap> *m_vPatternMap;
        std::multimap<unsigned int, structPatternMap> m_vPatternMap;
        // this is a combination of HASH and PREFIX table
        // the paper suggests shifting hash right by n bits to hash into this table in order to reduce sparseness

    };

    char WuManber::rchSpecialCharacters[] = {0x21, 0x22, 0x23, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
                                             0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e,
                                             0x3f, 0x40, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x7b, 0x7c, 0x7d,
                                             0x7e, 0x00};

    unsigned char WuManber::rchExtendedAscii[] = {
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
            0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x99, 0x9a, 0x9c, 0x0d, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3,
            0xa4, 0xa5, 0x00};

}

#endif //ACM_TEMPLATE_STRING_H
