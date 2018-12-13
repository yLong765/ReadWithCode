#include <iostream>

using namespace std;

class PoolAllocator
{
  public:
    typedef uintptr_t U32_pointer;
    typedef uintptr_t U32;

    PoolAllocator(U32 pool_count, U32 block_size)
    {
        this->pool_count = pool_count;
        this->block_size = block_size + 4; // 预留指针空间
        U32 poolSize_bytes = this->pool_count * this->block_size;
        begin_marker = (U32_pointer)malloc(poolSize_bytes);
        next_marker = begin_marker + this->block_size;
        alloc_marker = (pool_pointer)begin_marker;
    }
    ~PoolAllocator()
    {
        free((void *)begin_marker);
    }

    void *allocBlock()
    {
        this->alloc_block_count++;
        if (this->alloc_block_count > this->pool_count)
        {
            return NULL;
        }

        if (free_marker != NULL)
        {
            pool_pointer result = free_marker;
            free_marker = free_marker->next;
            return (void *)((U32_pointer)result + 4);
        }
        else
        {
            U32_pointer newBlock = (U32_pointer)alloc_marker + block_size;
            ((pool_pointer)newBlock)->next = alloc_marker;
            alloc_marker = (pool_pointer)newBlock;
            return (void *)((U32_pointer)newBlock + 4);
        }
    }

    void freeBlock(void *p)
    {
        if (p != NULL)
        {
            this->alloc_block_count--;
            ((pool_pointer)((U32_pointer)p - 4))->next = free_marker;
            free_marker = ((pool_pointer)((U32_pointer)p - 4));
        }
    }

  private:
    struct pool
    {
        pool *next;
    };

    typedef pool *pool_pointer;

    pool_pointer alloc_marker = 0;
    pool_pointer free_marker = 0;
    U32_pointer begin_marker = 0;
    U32_pointer next_marker = 0;
    U32 block_size;
    U32 pool_count;
    U32 alloc_block_count = 0;
};

int main()
{
    PoolAllocator pa = PoolAllocator(4, 4);
    void *p1 = pa.allocBlock();
    cout << "p1: " << p1 << endl;   // p1: 0x751774
    void *p2 = pa.allocBlock();
    cout << "p2: " << p2 << endl;   // p2: 0x75177c
    void *p3 = pa.allocBlock();
    cout << "p3: " << p3 << endl;   // p3: 0x751784
    pa.freeBlock(p1);
    void *p4 = pa.allocBlock();
    cout << "p4: " << p4 << endl;   // p4: 0x751774
    void *p5 = pa.allocBlock();
    cout << "p5: " << p5 << endl;   // p5: 0x75178c
    pa.freeBlock(p5);
    pa.freeBlock(p3);
    void *p6 = pa.allocBlock();
    cout << "p6: " << p6 << endl;   // p6: 0x751784
    void *p7 = pa.allocBlock();
    cout << "p7: " << p7 << endl;   // p7: 0x75178c

    return 0;
}