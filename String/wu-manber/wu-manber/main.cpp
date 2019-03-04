#include "WuManber.h"
#include <stdio.h>
#include <cstring>
#include <memory>
typedef unsigned short      WORD;

#define WORD_SIZE 65536
#define M_VALUE 5
#define B_VALUE 2
 
typedef struct _NODE
{
    _NODE       *pNext;     //next node point
    const char  *pPattern;  //pattern string
    WORD        wPrefix;    //prefix value
}NODE, *PNODE;

unsigned char   *g_ShiftTable   = NULL;
PNODE           *g_pNode        = NULL;

void TestWuManber();
void TestWuManber2();
bool BuildShiftTable(vector<const char *> vecPattern);
bool InsertNode(WORD wdHash, const char *pPattern, WORD wPrefix);
void Release();
void WuManberSearch(const char *pDest);
void ReportMatch(int nFindEnd, const char *pPattern);

int main()
{
    TestWuManber();
    TestWuManber2();

    return 0;
}

void TestWuManber()
{
    printf("0         1         2         3         4\r\n");
    printf("01234567890123456789012345678901234567890\r\n");
    bool b;
    char text[] = "text is abcde 12345";
    vector<const char *> vecPattern;
    vecPattern.push_back("abcde");
    vecPattern.push_back("12345");
    vecPattern.push_back("ab345");
    vecPattern.push_back("12cde");
    WuManber wumanber;
    wumanber.Initialize(vecPattern, true);
    b = wumanber.Search(strlen(text), text, vecPattern);
    return;
}

void TestWuManber2()
{
    printf("0         1         2         3         4         5         6\r\n");
    printf("0123456789012345678901234567890123456789012345678901234567890\r\n");
    char text[] = "text is abcdef 123456 abx456 12xdef 12cdef ab3456 ab3457";
    printf("%s\r\n", text);
    vector<const char *> vecPattern;
    vecPattern.push_back("abcdef");
    vecPattern.push_back("123456");
    vecPattern.push_back("ab3456");
    vecPattern.push_back("12cdef");
    BuildShiftTable(vecPattern);
    WuManberSearch(text);
    Release();
    return;
}

//the length of each string in vector must longer then M_VALUE
bool BuildShiftTable(vector<const char *> vecPattern)
{
    bool bRet = false;
    //how long the shift table?  the range of hash value.
    //we use the two characters combine the hash value
    //so the range of hash value is 0 to 65535, need 64k size to store
    g_ShiftTable = new unsigned char[WORD_SIZE];
    if (NULL == g_ShiftTable)
    {
        goto Exit0;
    }

    g_pNode = new PNODE[WORD_SIZE];
    if (NULL == g_pNode)
    {
        goto Exit0;
    }

    for (int i = 0; i < WORD_SIZE; i++)
    {
        g_ShiftTable[i] = M_VALUE - 1;
    }
    memset(g_pNode, 0, WORD_SIZE * sizeof(g_pNode[0]));

    for (unsigned int i = 0; i < vecPattern.size(); i++)
    {
        for (int j = 0; j < M_VALUE - B_VALUE + 1; j++)
        {
            WORD wdHash = *(WORD *)(&vecPattern[i][M_VALUE-1 - j - 1]);
            if (g_ShiftTable[wdHash] > j)
                g_ShiftTable[wdHash] = j;
            if (0 == j)// need save prefix hash value for each pattern, but maybe more than one
            {
                if (!InsertNode(wdHash, vecPattern[i], *(WORD *)(&vecPattern[i][0])))
                    goto Exit0;
            }
        }
    }
    bRet = true;
Exit0:
    if (!bRet)
    {
        Release();
    }
    return bRet;
}
    
bool InsertNode(WORD wdHash, const char *pPattern, WORD wPrefix)
{
    PNODE pNode         = new NODE;
    if (!pNode)
        return false;

    pNode->pPattern     = pPattern;
    pNode->pNext        = g_pNode[wdHash];
    pNode->wPrefix      = wPrefix;
    g_pNode[wdHash]     = pNode;

    return true;
}

void Release()
{
    if (g_ShiftTable)
    {
        delete [] g_ShiftTable;
        g_ShiftTable = NULL;
    }
    if (g_pNode)
    {
        for (int i = 0; i < WORD_SIZE; i++)
        {
            while (g_pNode[i])
            {
                PNODE pNext = g_pNode[i]->pNext;
                delete g_pNode[i];
                g_pNode[i] = pNext;
            }
        }
        delete [] g_pNode;
        g_pNode = NULL;
    }
}

void WuManberSearch(const char *pDest)
{
    int nLen = strlen(pDest);
    if (nLen < M_VALUE)
        return;

    int nBeginIdx = 0;
    while (nBeginIdx + (M_VALUE-1) < nLen)
    {
        WORD wHash = *(WORD*)&pDest[nBeginIdx + (M_VALUE-1) - 1];
        if (0 != g_ShiftTable[wHash])
        {
            nBeginIdx += g_ShiftTable[wHash];
        }
        else//hash value identical, maybe find a match
        {
            PNODE pNode = g_pNode[wHash];
            while (pNode)
            {
                if (pNode->wPrefix == *(WORD*)&pDest[nBeginIdx])
                {
                    int i = 0;
                    while (pNode->pPattern[i] && nBeginIdx+i < nLen && 
                           pNode->pPattern[i] == pDest[nBeginIdx+i])
                    {
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

void ReportMatch(int nFindEnd, const char *pPattern)
{
    printf("Find at %2d, %s\r\n", nFindEnd, pPattern);
}
