//
// Created by miss on 2/5/19.
//


// Usage: GPU Sort
#include <iostream>
#define ASCENDING true
using namespace std;


/*
 *1、双调序列
 *  (1)先单调递增后单调递减（或者先单调递减后单调递增）的序列。（比如1 2 3 6 5 4）
 *  (2)或者循环移位之后能满足(1)的序列。（比如4 5 6 2 1 2）
 *2、Batcher定理
    将任意一个长为2n的双调序列A分为等长的两半X和Y，将X中的元素与Y中的元素一一按原序比较，
    即a[i]与a[i+n] (i < n)比较，将较大者放入MAX序列，较小者放入MIN序列。
    则得到的MAX和MIN序列仍然是双调序列，并且MAX序列中的任意一个元素不小于MIN序列中的任意一个元素[2]。
  3、双调排序
    假设我们有一个双调序列，则我们根据Batcher定理，将该序列划分成2个双调序列，
    然后继续对每个双调序列递归划分，得到更短的双调序列，直到得到的子序列长度为1为止。这时的输出序列按单调递增顺序排列。
  4、任意序列生成双调序列
    前面讲了一个双调序列如何排序，那么任意序列如何变成一个双调序列呢？
    这个过程叫Bitonic merge, 实际上也是divide and conquer的思路。 和前面sort的思路正相反，
    是一个bottom up的过程——将两个相邻的，单调性相反的单调序列看作一个双调序列， 每次将这两个相邻的，
    单调性相反的单调序列merge生成一个新的双调序列， 然后排序（同3、双调排序）。 这样只要每次两个相邻长度为n的序列的单调性相反，
    就可以通过连接得到一个长度为2n的双调序列，然后对这个2n的序列进行一次双调排序变成有序，然后在把两个相邻的2n序列合并（在排序的时候第一个升序，
    第二个降序）。 n开始为1， 每次翻倍，直到等于数组长度， 最后就只需要再一遍单方向（单调性）排序了。
 */


void compare(int *arr, int a, int b, bool dir) {
    if (dir == (arr[a] > arr[b])) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }
}

void halfCleaner(int *arr, int group ,int length, bool dir, int flip) {
    for(int a = 0; a< group ; a++) {
        int begin = a * length;
        int delta;
        if (flip==1) delta = length - 1;
        else         delta = length/2;

        for(int i = 0;i<length/2;i++) {
            compare(arr, begin + i , begin + delta - flip * i, dir);
        }
    }
}

void bitonicSort(int *arr, int length, bool dir) {

    for(int i = 2; i <= length ; i <<= 1) {
        for(int j = i ; j > 1; j>>= 1) {
            halfCleaner(arr, length/j, j, dir,(j==i?1:-1));
        }
    }
}

int main(int argc, const char * argv[]) {

    int num = 32;
    int input[num];

    cout<<"input: ";
    srand((unsigned)time(NULL));
    for(int i = 0;i<num;i++) {
        input[i] = rand() % 100 +1;
        cout<<input[i]<<' ';
    }
    cout<<endl;

    bitonicSort(input, num, 1);

    cout<<"output: ";
    for(int i = 0;i<num;i++) {
        cout<<input[i]<<' ';
    }
    cout<<endl;

    return 0;
}
