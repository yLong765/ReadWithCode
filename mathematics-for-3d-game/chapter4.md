# 坐标变换

## 线性变换

给予坐标系$C、C^`$，$C^`$中坐标$<x^`,y^`,z^`>$可表示为坐标系$C$中的$<x,y,z>$坐标的线性函数
$$
\begin{aligned}
    x^`(x,y,z) = U_1x+V_1y+W_1z+T_1 \\
    y^`(x,y,z) = U_2x+V_2y+W_2z+T_2 \\
    z^`(x,y,z) = U_3x+V_3y+W_3z+T_3 \\
\end{aligned}
$$
用矩阵表示为:
$$
\begin{aligned}
    \left[
    \begin{matrix}
        x^` \\
        y^` \\
        z^` \\
    \end{matrix}
    \right]=
    \left[
    \begin{matrix}
        U_1 & V_1 & W_1 \\
        U_2 & V_2 & W_2 \\
        U_3 & V_3 & W_3 \\
    \end{matrix}
    \right]
    \left[
    \begin{matrix}
        x \\
        y \\
        z \\
    \end{matrix}
    \right]+
    \left[
    \begin{matrix}
        T_1 \\
        T_2 \\
        T_3 \\
    \end{matrix}
    \right]
\end{aligned}
$$

向量$T$表示从$C$坐标系原点到$C^`$坐标系原点的平移向量
列向量$U、V和W$的矩阵表示从$C$坐标系到$C^`$坐标系变换时，坐标系的坐标轴方向变换方式
