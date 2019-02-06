//
// Created by miss on 1/31/19.
//

#ifndef ACM_TEMPLATE_QUEUE_H
#define ACM_TEMPLATE_QUEUE_H
/************************************************************************/
/* 队列的实现，可以通过表直接实现，这里采用数组实现
/************************************************************************/

#include <assert.h>

namespace queue
{
    template <typename Object>
    class Queue
    {
        Queue(int QueueSize)
                :Front(0)
                ,Rear(1)
                ,Size(0)
                ,Capacity(QueueSize)
        {
            Array = new Object[QueueSize];
        }

        ~Queue()
        {
            assert(Array);
            delete[] Array;
        }

        //入队函数
        void EnQueue(Object x)
        {
            if (IsFull())
            {
                throw();
            }
            Array[Rear++] = x;
            Rear = (++Rear) % Capacity;
            ++Size;
        }

        //出队函数
        void DeQueue()
        {
            if (IsEmpty())
            {
                throw();
            }
            ++Front;
            --Size;
        }

        bool IsFull()
        {
            return Size == Capacity;
        }

        bool IsEmpty()
        {
            return Size == 0;
        }

    private:
        Object* Array;
        int Capacity;    //队列最大容量
        int Front;         //队列头位置
        int Rear;          //队列尾的位置
        int Size;           //队列中对象的数量
    };
}
#endif //ACM_TEMPLATE_QUEUE_H
