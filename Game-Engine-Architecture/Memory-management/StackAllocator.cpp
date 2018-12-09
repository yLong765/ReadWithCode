#include <iostream>
#include <stdlib.h>

#define U32 unsigned int
#define size sizeof(U32 *)

using namespace std;

class StackAllocator
{
  public:
    typedef U32 Marker;
    // 给定总大小，构建一个堆栈分配器
    explicit StackAllocator(U32 stackSize_bytes)
    {
        stackSize = stackSize_bytes;
        top = malloc(size * stackSize);
        front = top;
    }
    // 给定内存快大小，从堆栈顶端分配一个新的内存块
    void *alloc(U32 size_bytes)
    {
        allocSize += size_bytes;
        if (allocSize > stackSize)
        {
            EnsureCapacity(allocSize);
        }
        void *preTop = top;
        top = (U32 *)top + size_bytes;
        return preTop;
    }
    // 取得指向当前堆栈顶端的标记
    Marker getMarker()
    {
        return allocSize;
    }
    // 把堆栈回滚至之前的标记
    void freeToMarker(Marker marker)
    {
        top = (U32 *)front + marker;
        allocSize = marker;
    }
    // 清空整个堆栈
    void Clear()
    {
        top = front;
    }

  private:
    void *front;
    void *top;
    void *maxTop;
    U32 stackSize;
    U32 allocSize = 0;

    // 超出申请的内存大小，则重新申请
    void EnsureCapacity(U32 newSize)
    {
        int oldSize = stackSize;
        stackSize *= 2;
        if (stackSize < newSize)
        {
            stackSize = newSize;
        }
        Copy(malloc(size * stackSize), oldSize);
    }
    // 拷贝数据
    void Copy(void *newStack, int oldSize)
    {
        void *newFront = newStack;
        top = newFront;
        int p = -1;
        while (++p < oldSize)
        {
            *((U32 *)top + p) = *((U32 *)front + p);
            top = (U32 *)top + p;
            cout << top << " " << (U32 *)front + p << endl;
        }
        front = newFront;
    }
};

int main()
{
    StackAllocator sa = StackAllocator(4);
    U32 *p1 = (U32 *)sa.alloc(1);
    cout << "p1: " << p1 << endl; // p1: 0x1080df8
    U32 *p2 = (U32 *)sa.alloc(1);
    cout << "p2: " << p2 << endl; // p2: 0x1080dfc
    U32 p = sa.getMarker();       // 获取标记
    cout << "p: " << p << endl;   // p: 2
    U32 *p3 = (U32 *)sa.alloc(1);
    cout << "p3: " << p3 << endl; // p3: 0x1080e00
    U32 *p4 = (U32 *)sa.alloc(1);
    cout << "p4: " << p4 << endl; // p4: 0x1080e04
    sa.freeToMarker(p);           // 释放空间到标记
    U32 *p5 = (U32 *)sa.alloc(1);
    cout << "p5: " << p5 << endl; // p5: 0x1080e00
    U32 *p6 = (U32 *)sa.alloc(1);
    cout << "p6: " << p6 << endl; // p6: 0x1080e04
    U32 *p7 = (U32 *)sa.alloc(1); // 经过扩容
    cout << "p7: " << p7 << endl; // p7: 0x1080e28
    return 0;
}