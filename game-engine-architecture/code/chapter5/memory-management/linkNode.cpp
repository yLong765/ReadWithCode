/// Description: 各种链表的实现形式
/// Anthor: Yinl
/// Reference: Game Engine Architecture

// 外露式表(extrusive list)
template<typename T>
struct Link
{
    Link<T>* m_pPrev; // 前节点指针
    Link<T>* m_pNext; // 后节点指针
    T* m_pELem; // 元素指针
};
// 优点：一个元素能同时置于多个链表
// 缺点：必须动态分配内存，可以用池分配器解决效率和内存碎片(STL所有容器都为外露式)

// 侵入式表(intruslive list)
// 1.非派生类实现(Link同外露式链表)
class Element
{
    Link<Element> m_link;
};

// 2.派生类实现
template<typename T>
struct Link
{
    Link<T>* m_pPrev;
    Link<T>* m_pNext;
};

class Element : public Link<Element>
{
    // 其他成员
};
// 优点：不用动态分配内存
// 缺点：每个元素不能同时置于多个链表中

// 循环链表(circular linked list)
template<typename T>
class LinkedList
{
private:
    Link<T> m_root; // 包含头尾指针

public:
    void remove(Link<T>& link) // 循环链表没有空指针，所以可以直接删除
    {
        ASSERT(link.m_pNext != NULL);
        ASSERT(link.m_pPrev != NULL);

        link.m_pNext->m_pPrev = link.m_pPrev;
        link.m_pPrev->m_pNext = link.m_pNext;

        link.m_pPrev = link.m_pNext = NULL;
    }   
};

// 解决散列表碰撞问题
// 1.开放式散列(open hashing)：在同一个位置利用链表来存储碰撞的键值对
// 2.闭合式散列(closed hashing)：

int main()
{
    return 0;
}