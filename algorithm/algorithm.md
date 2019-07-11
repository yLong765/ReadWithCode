[TOC]

## 常用算法记录

### 最大公约数

#### 辗转相除法

两个数疯狂取余，最后为0则返回除数，为最大公约数

```c++
// 辗转相除法
int func(int a, int b)
{
    a %= b;
    if (a == 0)
    {
        return b;
    }
    return func(b, a);
}
```

#### 变换法（用于多个数取最大公约数）

```c++
//变换法
int func(vector<int> v)
{
    if (v != NULL && v.size() > 0)
    {
        // 取非零最小值
        int minN = v[0];
        for (int i = 0; i < v.size(); i++)
        {
            minN = min(minN, v[i]);
        }
        
        // 对所有数取余，余数为0则删除
        for (int i = 0; i < v.size(); i++)
        {
            v[i] %= minN;
            if (v[i] == 0)
            {
                v.erase(v.begin() + i);
            }
        }
        
        // 如果空则最小值为最大公约数
        if (v.empty())
        {
            return minN;
        }
    }
}
```

### 判断矩形是否相交

```c++
// 判断不相交
bool func(vector<int> rec1, vector<int> rec2)
{
	if (rec2[0] >= rec1[2] or rec2[1] >= rec1[3] or rec2[2] <= rec1[0] or rec2[3] <= rec1[1])
        {
            return false;
        }
        return true;
}
```

