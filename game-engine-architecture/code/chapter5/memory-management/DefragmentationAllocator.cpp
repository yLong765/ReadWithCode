/// Description: 不同大小池分配器 + 句柄内存碎片整理
/// Anthor: Yinl
/// Reference: Game Engine Architecture

#include <iostream>

using namespace std;

class Allocator
{
  public:
    typedef uintptr_t U32_pointer;
    typedef uintptr_t U32;

    // 初始化池大小
    Allocator(U32 poolSize_bytes)
    {
        begin_marker = (U32_pointer)malloc(poolSize_bytes);
        end_marker = begin_marker + poolSize_bytes;
        alloc_marker = (handle_pointer)operator new(4);
    }
    // 回收资源
    ~Allocator()
    {
        free((void *)begin_marker);
    }
    // 分配池
    void *allocBlock(U32 block_size)
    {
        U32_pointer newBlock = curr_marker + block_size;
        if (newBlock <= end_marker)
        {
            ((pool_pointer)newBlock)->next = alloc_marker;
            alloc_marker = (pool_pointer)newBlock; 
            return (void *)((U32_pointer)newBlock + 4);
        }

        return NULL;
    }
    // 回收池
    void freeBlock(void *p)
    {
        if (p != NULL)
        {

        }
    }

  private:
    struct handle
    {
        handle *next;
        U32_pointer data;
    };

    typedef handle *handle_pointer;

    handle_pointer alloc_marker = 0; // 分配新池指针
    U32_pointer begin_marker = 0;
    U32_pointer curr_marker = 0;
    U32_pointer end_marker = 0;
};

int main()
{
    PoolAllocator pa = PoolAllocator(4, 4);
    void *p1 = pa.allocBlock();
    cout << "p1: " << p1 << endl; // p1: 0x751774
    void *p2 = pa.allocBlock();
    cout << "p2: " << p2 << endl; // p2: 0x75177c
    void *p3 = pa.allocBlock();
    cout << "p3: " << p3 << endl; // p3: 0x751784
    pa.freeBlock(p1);
    void *p4 = pa.allocBlock();
    cout << "p4: " << p4 << endl; // p4: 0x751774
    void *p5 = pa.allocBlock();
    cout << "p5: " << p5 << endl; // p5: 0x75178c
    pa.freeBlock(p5);
    pa.freeBlock(p3);
    void *p6 = pa.allocBlock();
    cout << "p6: " << p6 << endl; // p6: 0x751784
    void *p7 = pa.allocBlock();
    cout << "p7: " << p7 << endl; // p7: 0x75178c
    void *p8 = pa.allocBlock();
    cout << "p8: " << p8 << endl; // p8: 0x0(NULL)

    return 0;
}