/************************************************************************/
/* 堆排序法
/* 时间复杂度：O(NlogN)
/************************************************************************/

#include <stdio.h>

#define LeftChild(i) ((2 * (i)) + 1)

void HeapAdjust(int * array, int i, int N)
{
    int child;
    int temp;
    int index;
    //从该节点开始往下遍历，进行父节点与子节点的排序
    for(index = i; LeftChild(index) < N; index = child)
    {
        //得到根节点的左儿子
        child = LeftChild(index);

        /*比较左儿子和右儿子的大小，选出较大的那个*/
        //如果左儿子小于右儿子
        if(child < N - 1 && array[child] < array[child + 1])
        {
            child += 1;
        }

        //比较父节点与子节点，如果父节点小于子节点则交换
        if(array[index] < array[child])
        {
            //交换父节点与子节点
            array[index] = array[index] ^ array[child];
            array[child] = /*array[child] ^*/ array[index] ^ array[child];
            array[index] = array[index] ^ array[child];
            //temp = array[index];
            //array[index] = array[child];
            //array[child] = temp;
        }
    }
}

void HeapSort(int * array, int N)
{
    /* 建立堆 */
    int index;
    //从原有堆中第一个非页节点开始调整
    for(index = N / 2; index >= 0; --index)
    {
        HeapAdjust(array, index, N);
    }

    int MaxElement;

    for(index = N - 1; index > 0; --index)
    {
        /*交换第一个和最后一个元素，保证最后一个元素是当前堆最大的元素
        **交换后堆的实际大小减一*/
        MaxElement = array[0];
        array[0] = array[index];
        array[index] = MaxElement;

        //交换后原来堆的堆序性发生变化，但是只有堆顶的堆序发生变换，因此只需要调整堆顶的堆序
        HeapAdjust(array, 0, index);
    }
}

int main()
{
    int array[10] = {10, 45, 78, 32, 89, 18, 105, 953, 243, 19};
    HeapSort(array, 10);
    int i = 0;
    int j = sizeof(array) / sizeof(int);
    while (i < j)
    {
        printf("%d     ", array[i++]);
    }
    return 0;
}