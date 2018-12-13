#include <iostream>
#include <assert.h>

using namespace std;

class StackAllocator
{
  public:
    typedef uintptr_t U32;
    typedef uintptr_t U32_pointer;
    typedef uint8_t U8;

    // 给定总大小，构建一个堆栈分配器
    explicit StackAllocator(U32 stackSize_bytes)
    {
        begin_marker = (U32_pointer)malloc(stackSize_bytes);
        curr_marker = begin_marker;
    }
    ~StackAllocator()
    {
        free((void *)begin_marker);
    }

    // 给定内存快大小，从堆栈顶端分配一个新的内存块
    void *alloc(U32 size_bytes)
    {
        U32_pointer temp = curr_marker;
        curr_marker += size_bytes;
        return (void *)temp;
    }

    // 对齐分配内存块,注：“alignment”必须为2的幂（一般为4或16）
    void *allocateAligned(U32 size_bytes, U32 alignment)
    {
        // 计算总共要分配的内存量
        U32 expandedSize_bytes = size_bytes + alignment;

        // 分配未对齐的内存块
        U32_pointer rawAddress = (U32_pointer)alloc(expandedSize_bytes);

        // 利用掩码去除地址低位部分，计算“错位”量，从而计算调整量
        U32_pointer mask = alignment - 1;
        U32_pointer misalignment = rawAddress & mask;
        U32_pointer adjustment = alignment - misalignment;

        // 计算调整后的地址，并把它以指针类型返回
        U32_pointer alignedAddress = rawAddress + adjustment;
        
        // 把alignment存储在调整后地址的前1字节
        U32_pointer *pAdjustment = (U32_pointer *)(alignedAddress - 1);
        *pAdjustment = adjustment;

        return (void *)alignedAddress;
    }

    // 取得指向当前堆栈顶端的标记
    U32_pointer getMarker()
    {
        return curr_marker;
    }

    // 把堆栈回滚至之前的标记
    void freeToMarker(U32_pointer marker)
    {
        curr_marker = marker;
    }

    // 回滚对齐分配的内存块
    void freeAligned(void *p)
    {
        U32_pointer alignedAddress = (U32_pointer)p;
        U8 *pAdjustment = (U8 *)(alignedAddress - 1);
        U32_pointer adjustment = (U32_pointer)*pAdjustment;
        U32_pointer rawAddress = alignedAddress - adjustment;
        freeToMarker(rawAddress);
    }

    // 清空整个堆栈
    void Clear()
    {
        curr_marker = begin_marker;
    }

  private:
    U32_pointer begin_marker;
    U32_pointer curr_marker;
};

int main()
{
    StackAllocator sa = StackAllocator(4);
    void *p1 = sa.alloc(1);
    cout << "p1: " << p1 << endl; // p1: 0xfc1770
    void *p2 = sa.alloc(1);
    cout << "p2: " << p2 << endl;    // p2: 0xfc1771
    unsigned int p = sa.getMarker(); // 获取标记
    cout << "p: " << p << endl;      // p: 0xfc1772
    void *p3 = sa.alloc(1);
    cout << "p3: " << p3 << endl; // p3: 0xfc1772
    void *p4 = sa.alloc(1);
    cout << "p4: " << p4 << endl; // p4: 0xfc1773
    sa.freeToMarker(p);           // 释放空间到标记
    void *p5 = sa.alloc(1);
    cout << "p5: " << p5 << endl; // p5: 0xfc1772
    void *p6 = sa.alloc(1);
    cout << "p6: " << p6 << endl; // p6: 0xfc1773

    StackAllocator saa = StackAllocator(16);
    int *pp1 = (int *)saa.allocateAligned(3, 4);
    cout << "pp1: " << pp1 << endl; // pp1: 0xfc1794
    void *pp2 = saa.allocateAligned(4, 4);
    cout << "pp2: " << pp2 << endl; // pp2: 0xfc1798
    saa.freeAligned(pp1);
    saa.freeAligned(pp2);

    return 0;
}