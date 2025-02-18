Weźmy takie $X, Y$, że $X~N(0,1),\ Y=X^2$

$$
f_X(x) = \frac{1}{\sqrt{2\pi}} e^{-x^2/2}$$
$$
E[X] = \int_{- \infin}^{\infin} x f_X(x) = \int_{- \infin}^{0} x f_X(x) + \int_{0}^{\infin} x f_X(x)
$$

Podstawiamy $f_X(x)$

$$
E[X] = \frac{1}{\sqrt{2\pi}}\left[ \int_{- \infin}^{0} x  e^{-x^2/2} + \int_{0}^{\infin} x  e^{-x^2/2}   
\right] =  \frac{1}{\sqrt{2\pi}}\left[ I_1 + I_2 \right]
$$

Podstawiamy dla $I_1$: $u=−x⇒du=−dx$

$$
I_1 = -\int^{\infin}_{0}u^3e^{-u/2}du
$$

Porównujemy to z $I_2$

$$
I_2 = \int_{0}^{\infin} x  e^{-x^2/2} 
$$

Widzimy, że $I_1 = - I_2$

Zatem
$$
E[X] = 0
$$

Skorzystamy ze wzory no konwariancje

$$
\text{cov}(X,Y) = E[X\cdot Y] - EX \cdot EY
$$

$$
E[X^2] = 
$$


# Jeszcze raz 

Let’s take $X, Y$,such that $X \sim  N(0,1),\ Y=X^2$

$$
P_X = 
\begin{cases}
X = -1: \frac{2}{5} \\
X = 0: \frac{1}{5} \\
X = 1: \frac{2}{5} 
\end{cases}

P_Y = 
\begin{cases}
Y = 0: \frac{1}{5} \\
Y = 1: \frac{4}{5} 
\end{cases}
$$



We know that 

$$
   \rho(X, Y) = \frac{\text{Cov}(X, Y)}{\sqrt{\text{Var}(X)\text{Var}(Y)}}
$$

Also, we will use 
$$
\text{cov}(X,Y) = E[XY] - EX \cdot EY
$$


Computing the expected values:

 - $EX = \sum_i x_i p_i = -1 \cdot \frac{2}{5} + 0 \cdot \frac{1}{5} + 1 \cdot \frac{2}{5} = 0$

- $EY =  0 \cdot \frac{1}{5} + 1 \cdot \frac{4}{5} = \frac{4}{5}$

- $E[X^2] = (-1)^2 \cdot \frac{2}{5} + 0^2 \cdot \frac{1}{5} + 1^2 \cdot \frac{2}{5} = \frac{4}{5}$

- $E[Y^2] =  0^2 \cdot \frac{1}{5} + 1^2 \cdot \frac{4}{5} = \frac{4}{5}$
- $E[XY] = E[X^3] = (-1)^3 \cdot \frac{2}{5} + 0^3 \cdot \frac{1}{5} + 1^3 \cdot \frac{2}{5} = 0$

Using the formula:

$$\text{Var}(X) = E[X^2] - (E[X])^2$$
- $\text{Var}(X) = \frac{4}{5} - 0^2 = \frac{4}{5}$
- $\text{Var}(Y) = \frac{4}{5} - (\frac{4}{5})^2 = \frac{4}{25}$

Computing covariance
$$
\text{cov}(X,Y) = 0 - 0 \cdot \frac{4}{5} = 0
$$

Thus, we obtain: 

$$
   \rho(X, Y) = \frac{0}{\sqrt{\text{Var}(X)\text{Var}(Y)}} = 0,  \ \text{cause} \ \text{Var}(X)\text{Var}(Y) > 0
$$

## 2 zadanie