//
// Created by miss on 1/31/19.
//

#ifndef ACM_TEMPLATE_HEAP_H
#define ACM_TEMPLATE_HEAP_H
/************************************************************************/
/* 堆的实现                                                                     */
/************************************************************************/
#include<vector>
namespace heap
{
    template<typename T>
    class Heap
    {
    public:
        /************************************************************************/
        /*构造函数*/
        Heap(int capacity = 100)
                :size(0)   //堆中包含数据个数
        {
            H.resize(capacity);
        }

        ~Heap()
        {
        }

        bool isEmpty()
        {
            return size == 0;
        }

        void makeEmpty()
        {
            size = 0;
            for (auto it = H.begin(); it != H.end(); it++)
            {
                H.erase(it);
            }
        }
        /************************************************************************/
        /*插入函数 */
        void insert(const T & x)
        {
            //如果vector中已经存满了，重新分为大小，数组首地址不存数据
            if (size == H.size() -1)
            {
                H.resize(2*size);
            }
            int current;
            //size大小加一
            for (current = ++size; current > 1 && H[current/2] > x; current /= 2)
            {
                H[current] = H[current/2];
            }
            //找到空位将x插入
            H[current] = x;
        }

        /*删除函数*/
        T deleteMin()
        {
            if (isEmpty())
            {
                throw();
            }
            int current, child;
            T returnVal = H[1];
            T lastElement = H[size--];   //将最后一个值保存下来，删除一个元素所以自减运算
            for (current = 1; 2 * current > size; current = child)
            {
                child = 2 * current;
                //防止访问越界
                if (child != size && H[2 * current] > H[2 * current + 1])
                {
                    ++child;
                }
                //比较子较小的儿子与最后一个值的大小，如果儿子较小用儿子上滤，否则跳出循环
                if (H[child] < H[current])
                {
                    H[current] = H[child];
                }
                else
                {
                    break;
                }
            }
            H[current] = lastElement;
            return returnVal;
        }

    private:
        std::vector<T> H;
        int size;
    };
}
#endif //ACM_TEMPLATE_HEAP_H
