#include <iostream>
#include <stdlib.h>

using namespace std;

template <typename T, size_t BlockSize = 16>
class PoolAllocator
{
  public:
	typedef T *pointer;

	PoolAllocator()
	{
		currentBlock = NULL;
		currentSlot = NULL;
		lastSlot = NULL;
		freeSlot = NULL;
	}
	~PoolAllocator()
	{
		pool_pointer curr = currentBlock;
		while (curr != NULL)
		{
			pool_pointer prev = curr->next;
			operator delete((void *)curr); // 释放块内存
			curr = prev;
		}
	}
	// 申请块内存
	void allocatorBlock()
	{
		void *newBlock = operator new(BlockSize);
		((pool_pointer)newBlock)->next = currentBlock;
		currentBlock = (pool_pointer)newBlock;						 // 开始第一字节存储下一个块的地址
		currentSlot = (pool_pointer)newBlock + sizeof(pool_pointer); // 存储位置为第二字节
		lastSlot = (pool_pointer)newBlock + BlockSize;				 // 分配内存块大小
	}
	// 分配
	pointer allocator()
	{
		if (freeSlot != NULL)
		{
			pool_pointer result = freeSlot;
			freeSlot = freeSlot->next;
			return (pointer)result;
		}
		else
		{
			if (currentSlot >= lastSlot)
			{
				allocatorBlock();
			}
			return (pointer)(currentSlot++);
		}
	}
	// 释放
	void deallocator(pointer p)
	{
		if (p != NULL)
		{
			((pool_pointer)p)->next = freeSlot;
			freeSlot = ((pool_pointer)p);
		}
	}

  private:
	struct pool
	{
		pool *next;
	};

	typedef pool *pool_pointer;

	pool_pointer currentBlock;
	pool_pointer currentSlot;
	pool_pointer lastSlot;
	pool_pointer freeSlot;
};

int main()
{
	PoolAllocator<void> pools;
	void *p = (void *)pools.allocator();
	void *p1 = pools.allocator();
	pools.deallocator(p);
	void *p2 = pools.allocator();
	return 0;
}