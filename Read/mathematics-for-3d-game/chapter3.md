# 矩阵

## 性质

* 一个$n \times m$矩阵$M$是由$n$行$m$列数字组成的数组。如果$n = m$则称其为方阵
* $i=j$的元素称其为主对角元素，只有主对角元素不等于零的方阵称为对角矩阵：$M=\left[\begin{matrix} 1 & 0 \\ 0 & 1 \end{matrix}\right]$
* $M$的转置矩阵表示为$M^T$
* 标量乘矩阵：$aM=Ma=\left[\begin{matrix} aM_{11} & aM_{12} & \cdots & aM_{1m} \\ aM_{21} & aM_{22} & \cdots & aM_{2m} \\ \vdots & \vdots & \ddots & \vdots \\ aM_{n1} & aM_{n2} & \cdots & aM_{nm} \end{matrix}\right]$
* 矩阵加法：$F+G=\left[\begin{matrix} F_{11}+G_{11} & F_{12}+G_{12} & \cdots & F_{1m}+G_{1m} \\ F_{21}+G_{21} & F_{22}+G_{22} & \cdots & F_{2m}+G_{2m} \\ \vdots & \vdots & \ddots & \vdots \\ F_{n1}+G_{n1} & F_{n2}+G_{n2} & \cdots & F_{nm}+G_{nm} \end{matrix}\right]$
* 当矩阵F的列数等于矩阵G的行数时，这两个矩阵可以相乘，即如果$F$为$n \times m$矩阵，$G$为$m \times p$矩阵，则这两个矩阵的乘积$FG$矩阵为一个$n \times p$的矩阵,其中(i,j)元素等于：$(FG)_{ij}=\sum_{k=1}^mF_{ik}G_{kj}$。矩阵$FG$的(i,j)元素也可以看成矩阵$F$的第$i$行和矩阵$G$的第$j$列对应向量的内积
* 单位矩阵是一个$n \times n$的矩阵：$I_n=\left[\begin{matrix} 1 & 0 & \cdots & 0 \\ 0 & 1 & \cdots & 0 \\ \vdots & \vdots & \ddots & \vdots \\ 0 & 0 & \cdots & 1 \end{matrix}\right]$

### 定理

给定2个标量$a$和$b$，任意3个$n \times n$的矩阵$F$、$G$和$H$

* $F+G=G+F$
* $(F+G)+H=F+(G+H)$
* $a(bF)=(ab)F$
* $a(F+G)=aF+aG$
* $(a+b)F=aF+bF$

给定任意标量$a$，任意一个$n \times m$矩阵$F$、一个$m \times p$矩阵$G$和一个$p \times q$矩阵$H$

* $(aF)G=a(FG)$
* $(FG)H=F(GH)$
* $(FG)^T=G^TF^T$

## 线性方程组

$$
\begin{aligned}
3x+2y-3z=-13 \\
4x-3y+6z=7 \\
x-z=-5 \\
\end{aligned}
$$

可表示为：

$$
\left[
\begin{matrix}
    3 & 2 & -3 \\
    4 & -3 & 6 \\
    1 & 0 & -1 \\
\end{matrix}
\right]
\left[
\begin{matrix}
    x \\
    y \\
    z \\
\end{matrix}
\right]=
\left[
\begin{matrix}
    -13 \\
    7 \\
    -5 \\
\end{matrix}
\right]
$$

## 逆矩阵

对任意$n \times n$矩阵$M$，如果存在一个矩阵$M^{-1}$，使$MM^{-1}=M^{-1}M=I$，则称矩阵可逆，没有逆矩阵的矩阵成为奇异矩阵

## 行列式

矩阵$M$的行列式表示为$detM$
$$ detM=\sum^n_{i=1}M_{ik}C_{ik}(M)(1\leq k \leq n) $$
或
$$ detM=\sum^n_{i=1}M_{kj}C_{kj}(M)(1\leq k \leq n) $$
无论k为何值，以上行列式的值都相同。矩阵$M$的行列式等于任意一行或者一列元素与其代数余子式乘积的和

例：$ \left|\begin{matrix} a & b \\ c & d \end{matrix}\right|=ad-bc $
$$
\left|
\begin{matrix}
    a_{11} & a_{12} & a_{13} \\
    a_{21} & a_{22} & a_{23} \\
    a_{31} & a_{32} & a_{33} \\
\end{matrix}
\right|
\begin{aligned}
    & =a_{11}\left|
    \begin{matrix}
        a_{22} & a_{23} \\
        a_{32} & a_{33} \\
    \end{matrix}
    \right|-
    a_{12}\left|
    \begin{matrix}
        a_{21} & a_{23} \\
        a_{31} & a_{33} \\
    \end{matrix}
    \right|+
    a_{13}\left|
    \begin{matrix}
        a_{21} & a_{22} \\
        a_{31} & a_{32} \\
    \end{matrix}
    \right| \\
    & =a_{11}(a_{22}a_{33}-a_{23}a_{32})-a_{12}(a_{21}a_{33}-a_{23}a_{31})+a_{13}(a_{21}a_{32}-a_{22}a_{31})
\end{aligned}
$$

### 特征值和特征向量

一个$n \times n$矩阵$M$的特征值等于一下特征多项式的根：
$$det(M-\lambda I)$$
通过求解以下齐次线性方程组，可获得与矩阵$M$的特征值对应的特征向量$V$
$$(M-\lambda I)V=0$$
实数对称矩阵的特征值为实数，与对称矩阵不同特征值对应的特征向量正交

### 矩阵对角化

一个$n \times n$的矩阵$M$，如果$V_1,V_2,\cdots,V_n$是矩阵$M$的线性无关的特征向量，以下矩阵$A$可以将$M$对角化：
$$A=[V_1,V_2,\cdots,V_n]$$
即
$$A^{-1}MA=
\left[
\begin{matrix}
    \lambda_1 & 0 & \cdots & 0 \\
    0 & \lambda_2 & \cdots & 0 \\
    \vdots & \vdots & \ddots & \vdots \\
    0 & 0 & \cdots & \lambda_n \\
\end{matrix}
\right]
$$
其中$\lambda_1,\lambda_2,\cdots,\lambda_n$位矩阵$M$的特征值
