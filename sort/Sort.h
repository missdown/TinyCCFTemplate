//
// Created by miss on 19-1-12.
//

#ifndef ACM_TEMPLATE_SORT_H
#define ACM_TEMPLATE_SORT_H
#include <iostream>
#include <time.h>
#include <cstdlib>


/*
 * 排序的稳定性和复杂度
 * 不稳定：
      选择排序（selection sort）— O(n2)
      快速排序（quicksort）— O(nlogn) 平均时间, O(n2) 最坏情况; 对于大的、乱序串列一般认为是最快的已知排序
      堆排序 （heapsort）— O(nlogn)
      希尔排序 （shell sort）— O(nlogn)
      基数排序（radix sort）— O(n·k); 需要 O(n) 额外存储空间 （K为特征个数）
 * 稳定：
      插入排序（insertion sort）— O(n2)
      冒泡排序（bubble sort） — O(n2)
      归并排序 （merge sort）— O(n log n); 需要 O(n) 额外存储空间
      二叉树排序（Binary tree sort） — O(nlogn); 需要 O(n) 额外存储空间
      计数排序  (counting sort) — O(n+k); 需要 O(n+k) 额外存储空间，k为序列中Max-Min+1
      桶排序 （bucket sort）— O(n); 需要 O(k) 额外存储空间
 */


/*
 * 遍历数组，遍历到i时，a0,a1...ai-1是已经排好序的，取出ai，从ai-1开始向前和每个比较大小，如果小于，
 * 则将此位置元素向后移动，继续先前比较，如果不小于，则放到正在比较的元素之后。可见相等元素比较是，
 * 原来靠后的还是拍在后边，所以插入排序是稳定的。当待排序的数据基本有序时，插入排序的效率比较高，只需要进行很少的数据移动。
 */
void insertion_sort (int a[], int n) {
    int i,j,v;
    for (i=1; i<n; i++) {
        //如果第i个元素小于第j个，则第j个向后移动
        for (v=a[i], j=i-1; j>=0&&v<a[j]; j--)
            a[j+1]=a[j];
        a[j+1]=v;
    }
}

/*
 * 遍历数组，遍历到i时，a0,a1...ai-1是已经排好序的，然后从i到n选择出最小的，记录下位置，如果不是第i个，
 * 则和第i个元素交换。此时第i个元素可能会排到相等元素之后，造成排序的不稳定。
 */
void selection_sort (int a[], int n) {
    int i,j,pos,tmp;
    for (i=0; i<n-1; i++) {
        //寻找最小值的下标
        for (pos=i, j=i+1; j<n; j++)
            if (a[pos]>a[j])
                pos=j;
        if (pos != i) {
            tmp=a[i];
            a[i]=a[pos];
            a[pos]=tmp;
        }
    }
}



void bubble_sort (int a[], int n) {
    int i, j, lastSwap, tmp;
    for (j=n-1; j>0; j=lastSwap) {
        lastSwap=0;     //每一轮要初始化为0，防止某一轮未发生交换，lastSwap保留上一轮的值进入死循环
        for (i=0; i<j; i++) {
            if (a[i] > a[i+1]) {
                tmp=a[i];
                a[i]=a[i+1];
                a[i+1]=tmp;
                //最后一次交换位置的坐标
                lastSwap = i;
            }
        }
    }
}

/*
 * 堆排序是把数组看作堆，第i个结点的孩子结点为第2*i+1和2*i+2个结点（不超出数组长度前提下），堆排序的第一步是建堆，
 * 然后是取堆顶元素然后调整堆。建堆的过程是自底向上不断调整达成的，这样当调整某个结点时，其左节点和右结点已经是满足条件的，
 * 此时如果两个子结点不需要动，则整个子树不需要动，如果调整，则父结点交换到子结点位置，再以此结点继续调整。下述代码使用的大顶堆，
 * 建立好堆后堆顶元素为最大值，此时取堆顶元素即使堆顶元素和最后一个元素交换，最大的元素处于数组最后，此时调整小了一个长度的堆，
 * 然后再取堆顶和倒数第二个元素交换，依次类推，完成数据的非递减排序。堆排序的主要时间花在初始建堆期间，建好堆后，
 * 堆这种数据结构以及它奇妙的特征，使得找到数列中最大的数字这样的操作只需要O(1)的时间复杂度，维护需要logn的时间复杂度。
 * 堆排序不适宜于记录数较少的文件
 */


void heapAdjust(int a[], int i, int nLength)
{
    int nChild;
    int nTemp;
    for (nTemp = a[i]; 2 * i + 1 < nLength; i = nChild)
    {
        // 子结点的位置=2*（父结点位置）+ 1
        nChild = 2 * i + 1;
        // 得到子结点中较大的结点
        if ( nChild < nLength-1 && a[nChild + 1] > a[nChild])
            ++nChild;
        // 如果较大的子结点大于父结点那么把较大的子结点往上移动，替换它的父结点
        if (nTemp < a[nChild])
        {
            a[i] = a[nChild];
            a[nChild]= nTemp;
        }
        else
            // 否则退出循环
            break;
    }
}

// 堆排序算法
void heap_sort(int a[],int length)
{
    int tmp;
    // 调整序列的前半部分元素，调整完之后第一个元素是序列的最大的元素
    //length/2-1是第一个非叶节点，此处"/"为整除
    for (int i = length / 2 - 1; i >= 0; --i)
        heapAdjust(a, i, length);
    // 从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
    for (int i = length - 1; i > 0; --i)
    {
        // 把第一个元素和当前的最后一个元素交换，
        // 保证当前的最后一个位置的元素都是在现在的这个序列之中最大的
        ///  Swap(&a[0], &a[i]);
        tmp = a[i];
        a[i] = a[0];
        a[0] = tmp;
        // 不断缩小调整heap的范围，每一次调整完毕保证第一个元素是当前序列的最大值
        heapAdjust(a, 0, i);
    }
}


/*
 * Shell Sort
 */
void ShellSort(int * array, int size)
{
    int Gap, i, j;
    int tmp;
    for(Gap = size / 2; Gap > 0; Gap /= 2)
    {
        for(i = Gap; i < size; i += Gap)
        {
            tmp = array[i];
            for(j = i; array[j - Gap] > tmp && j > 0; j -= Gap)
            {
                array[j] = array[j - Gap];
            }
            array[j] = tmp;
        }
    }
}
// Usage: int Array[10] = {5, 45, 36, 48, 20, 17, 84, 201, 92, 54};
// ShellSort(Array, 10);

/*
 * 基数排序也可以看作一种桶排序，不断的使用不同的标准对数据划分到桶中，最终实现有序。
 * 基数排序的思想是对数据选择多种基数，对每一种基数依次使用桶排序。
 * 基数排序的步骤：以整数为例，将整数按十进制位划分，从低位到高位执行以下过程。
 * 1. 从个位开始，根据0~9的值将数据分到10个桶桶，例如12会划分到2号桶中。
 * 2. 将0~9的10个桶中的数据顺序放回到数组中。
 * 重复上述过程，一直到最高位。
 * 上述方法称为LSD（Least significant digital），还可以从高位到低位，称为MSD。
 */

int getNumInPos(int num,int pos) //获得某个数字的第pos位的值
{
    int temp = 1;
    for (int i = 0; i < pos - 1; i++)
        temp *= 10;

    return (num / temp) % 10;
}

#define RADIX_10 10    //十个桶，表示每一位的十个数字
#define KEYNUM 5     //整数位数
void radix_sort(int* pDataArray, int iDataNum)
{
    int *radixArrays[RADIX_10];    //分别为0~9的序列空间
    for (int i = 0; i < RADIX_10; i++)
    {
        radixArrays[i] = new int[iDataNum];
        radixArrays[i][0] = 0;    //index为0处记录这组数据的个数
    }

    for (int pos = 1; pos <= KEYNUM; pos++)    //从个位开始到31位
    {
        for (int i = 0; i < iDataNum; i++)    //分配过程
        {
            int num = getNumInPos(pDataArray[i], pos);
            int index = ++radixArrays[num][0];
            radixArrays[num][index] = pDataArray[i];
        }

        for (int i = 0, j =0; i < RADIX_10; i++) //写回到原数组中，复位radixArrays
        {
            for (int k = 1; k <= radixArrays[i][0]; k++)
                pDataArray[j++] = radixArrays[i][k];
            radixArrays[i][0] = 0;
        }
    }
}


namespace HEAP {
    const int maxn = 100;
    // n = num of the elements
    int heap[maxn], n = 10;

    /*
     * O(logn)
     */
    void downAdjust(int low, int high) {
        int i = low, j = i * 2;  // i  = root ; j = root.lchild;
        while(j <= high) {  // lchild is existed
            if(j + 1 <= high && heap[j + 1] > heap[j]) {  // if root has rchild and rchild > lchild
                j = j + 1;  // j save the root's rchild position
            }

            if(heap[j] > heap[i]) { // child > root
                std::swap(heap[j], heap[i]);
                i = j;  // update root and lchild
                j = i * 2;
            }else break;
        }
    }

    // O(n)
    void createHeap() {
        for (int i = n / 2; i >= 1; --i) {  // backword to make sure root is the gigantic number from the tuple
            downAdjust(i, n);
        }
    }

    // O(logn)
    void deleteTop() {
        heap[1] = heap[n--];
        downAdjust(1, n);
    }

    // O(logn)
    void upAdjust(int low, int high) {
        int i = high, j = i / 2;   // i need to be adjust ,j is i's father
        while(j >= low) {
            if(heap[j] < heap[i]) {
                std::swap(heap[j], heap[i]);
                i = j;
                j = i / 2;
            } else break;
        }
    }

    void insert(int x) {
        heap[++n] = x;
        upAdjust(1, n);
    }

    void heapSort() {
        createHeap();

        for (int i = n; i > 1; --i) {
            std::swap(heap[i], heap[1]);
            downAdjust(1, i - 1);
        }
    }



    /// Another one

    //给定父节点的索引，得到左子节点的索引
    #define LeftChild(i) (2*(i)+1)
    //元素下沉方法
    void PercDown(int A[], int i, int N)
    {
        //子节点的索引号
        int child;
        //存储当前父节点元素的临时变量
        //(注：每一个节点都可以看作是其子树的根节点)
        int tmp;

        for (tmp = A[i]; LeftChild(i)<N; i = child)
        {
            child = LeftChild(i);
            //挑选出左、右子节点中较大者
            if (child != N-1 && A[child+1]>A[child])
            {
                child++;
            }
            //比较当前父节点与较大子节点
            if (A[i]<A[child])
            {
                //交换当前父节点处的元素值与较大子节点的元素值
                tmp= A[i];
                A[i] = A[child];
                A[child] = tmp;
            }
            else
            {
                break;
            }

        }
    }

    void Swap(int *num1, int * num2)
    {
        int tmp = *num1;
        *num1 = *num2;
        *num2 = tmp;
    }

    void HeapSort(int A[], int N)
    {
        int i;
        //步骤一：创建大根堆
        for (i  = N/2;  i>=0; i--)
        {
            PercDown(A, i, N);

        }
        //步骤二：调整大根堆
        for ( i = N-1; i > 0; i--)
        {
            //首尾交换
            Swap(&A[0], &A[i]);
            //元素下沉
            PercDown(A, 0, i);
        }
    }

    void Test()
    {
        int A[6] = {4,5,3,2,6,1};
        HeapSort(A, 6);
        for(int i = 0; i <= 5; ++i) {
            std::cout << A[i] << " ";
        }
        std::cout << std::endl;
    }


}


template <typename T>
class Sort
{
public:
    const int maxn = 100;


    void mergeSort(T A[], int left, int right)
    {
        if(left < right) {
            int mid = (left + right) / 2;

            mergeSort(A, left, mid);
            mergeSort(A, mid + 1, right);
            merge(A, left, mid, mid + 1, right);
        }
    }

    void print(T A[], int start, int end)
    {
        for (int i = start; i < end; i++) {
            std::cout << A[i] << " ";
        }
        std::cout << std::endl;
    }

    void mergeSort2(T A[], int left, int right)
    {
        for (int step = 2; step / 2 <= (right - left) ; step *= 2) {
            for (int i = 0; i < (right - left); i += step) {
                int mid = i + step / 2 -1;
                if(mid + 1 <= (right- left))
                    merge(A, i, mid, mid+1, i + step - 1 < right -left ? i + step - 1 : right -left);
            }
        }
    }

    // O(nlog(n)) Bad O(n^2)
    /*
     * 快速排序首先找到一个基准，下面程序以第一个元素作为基准（pivot），然后先从右向左搜索，如果发现比pivot小，
     * 则和pivot交换，然后从左向右搜索，如果发现比pivot大，则和pivot交换，一直到左边大于右边，此时pivot左边的都比它小，
     * 而右边的都比它大，此时pivot的位置就是排好序后应该在的位置，此时pivot将数组划分为左右两部分，可以递归采用该方法进行。
     * 快排的交换使排序成为不稳定的。
     */
    void quickSort(T A[], int left, int right)
    {
        if(left < right)
        {
            int pos = randPartiton(A, left, right);
            quickSort(A, left, pos - 1);
            quickSort(A, pos + 1, right);
        }
    }

private:

    void merge(T A[], int L1, int R1, int L2, int R2)
    {
        int i = L1, j = L2;
        T temp[maxn];
        int index = 0;
        while(i <= R1 && j <= R2)
        {
            if(A[i] <= A[j])
            {
                temp[index++] = A[i++];
            }
            else
            {
                temp[index++] = A[j++];
            }
        }
        while(i <= R1) temp[index++] = A[i++];
        while(j <= R2) temp[index++] = A[j++];
        for (int i = 0; i < index; ++i) {
            A[L1 + i] = temp[i];
        }
    }

    int randPartiton(T A[], int left, int right)
    {
        int p = round(1.0*rand()/RAND_MAX*(right- left)+left);
        std::swap(A[p], A[left]);
        T temp = A[left];
        while(left < right)
        {
            while(left < right && A[right] > temp) right--;
            A[left] = A[right];
            while (left < right && A[left] <= temp) left++;
            A[right] = A[left];
        }
        A[left] = temp;
        return left;
    }


};


#endif //ACM_TEMPLATE_SORT_H
