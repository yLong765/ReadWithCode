# Chapter 2 : 向量

## 性质

* 列向量：$ \vec{V} = \left[\begin{matrix} V_1 \\ V_2 \\ \vdots \\ V_n \end{matrix}\right] $
* 转置（形式为行向量）：$ \vec{V}^T = \left[\begin{matrix} V_1 & V_2 & \cdots & V_n \end{matrix}\right] $
* 向量与标量$a$相乘：$ a\vec{V} = \vec{V}a = <aV_1, aV_2, \cdots, aV_n> $（当$a = -1$时，结果为$-V$）
* 向量的加法和减法是按分量逐个相加或相减完成的：$ \vec{P} + \vec{P} = <P_1 + Q_1, P_2 + Q_2, \cdots, P_n + Q_n> (P - Q = P + (-Q)) $
* $P + Q = Q + P$
* $(P + Q) + R = P + (Q + R)$
* $(ab)P = a(bP)$
* $a(P + Q) = aP + aQ$
* $(a + b)P = aP + bP$
* $||P|| \geq 0 $
* $||aP|| = |a|\quad||P||$
* $||p+Q||\leq||P||+||Q||$

## 内积

* 定义：$P \cdot Q = \sum_{i = 1}^n P_iQ_i$
* 对于三维向量：$P \cdot Q = P_xQ_x + P_yQ_y + P_zQ_z$
* 矩阵表示：$P^T \cdot Q = \left[\begin{matrix} P_1 & P_2 & \cdots & P_n \end{matrix}\right] \left[\begin{matrix} Q_1 \\ Q_2 \\ \vdots \\ Q_n \end{matrix}\right]$
* $P \cdot Q = ||P|| \quad ||Q||cos\alpha$
  * 结论1：$P \cdot Q = 0$，则向量$P$和$Q$互相垂直
  * 结论2：向量内积的符号反应两个向量的指向方向，如$P \cdot Q > 0$则夹角小于90°，若$P \cdot Q < 0$则夹角为大于90°


## 向量投影

* 向量$P$在向量$Q$上的投影$proj_QP$可表示为：$proj_QP = \frac{P \cdot Q}{||Q||^2}Q$
* 向量$P$相对于向量$Q$的垂直分量$perp_QP$可表示为：$perp_QP = P - proj_QP$

## 外积

* 两个向量的外积可以产生一个与这两个向量都垂直的向量(以下例子都为三维向量)
* $P \times Q = <P_yQ_z - P_zQ_y, P_zQ_x - P_xQ_z, P_xQ_y - P_yQ_x>$
* 矩阵与向量相乘的形式：$P \times Q = \left[\begin{matrix} 0 & -P_z & P_y \\ P_z & 0 & -P_x \\ -P_y & P_x & 0 \end{matrix}\right] \left[\begin{matrix} Q_x \\ Q_y \\ Q_z \end{matrix}\right]$
* $(P \times Q) \cdot P = (P \times Q) \cdot Q = 0$
* $||P \times Q|| = ||P||\quad||Q||sin\alpha$