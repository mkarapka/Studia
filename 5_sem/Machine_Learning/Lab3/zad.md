$$
\frac{\partial}{\partial\sigma^2}l(\beta, \sigma^2; y; X)= \\
=\frac{\partial}{\partial\sigma^2}l \left(-\frac{N}{2} \ln(2\pi) - \frac{N}{2}\ln{\sigma^2} - \frac{1}{2 \sigma^2} \sum^N_{i=1} (y_i - x_i \beta)^2 \right) = \\
= \frac{1}{2 \sigma^4} \left(\sum^N_{i=1} (y_i - x_i \beta)^2 - N\sigma^2 \right)
$$

if equals zero if
$$
\sum^N_{i=1} (y_i - x_i \beta)^2 - N\sigma^2  = 0
$$

thus 
$$
\hat\sigma^2 = \frac{1}{N} \sum^N_{i=1}(y_i - x_i \beta)^2 
$$

### Subtask B
1. Find the form of the loglikelihood.
2. Compute the gradient of logistic function with respect to $\beta$
#### 1. Find the form of the loglikelihood.
$$
P(y_i=1| x_i) = S(x_i\beta) \\
P(y_i=0| x_i) = 1 - S(x_i\beta)

$$

we can write this two funtions as a one
$$
p(y_i | x_i ; \beta) = (S(x_i\beta))^{y_i}(1-S(x_i\beta))^{1-y_i}
$$

Then we likeliyhood will looks like this
$$
L(\beta) = \prod_{i=1}^n p(\vec{y} \ | \ x ;\beta) = p(y_1 | x_1 ; \beta) \ \cdot \ p(y_2 | x_2 ; \beta) \ \cdot \ ... \ \cdot p(y_n | x_n; \beta) = \\
= (S(x_1\beta))^{y_1}(1-S(x_1\beta))^{1-y_1} \cdot ... \ \cdot (S(x_n\beta))^{y_n}(1-S(x_n\beta))^{1-y_n}
$$

and log likelyhood

$$
\ell(\beta) = \ln L(\beta) = \sum_{i=1}^n y_i \ln S(x_i\beta) + (1-y_i) \ln (1-S(x_i\beta))
$$

To maximize log likelihood we will find OPT $\beta$ using gradient ascent

---
#### 2. Compute the gradient of logistic function with respect to $\beta$

$$
\frac{\partial \ell(\beta)}{\partial \beta^{(j)}}
=  \frac{\partial } {\partial \beta^{(j)}} \Big(y \ln S(x\beta) + (1-y) \ln (1-S(x \beta)) \Big) = \\ 
= \left[ \frac{y}{S(x\beta)}  - \frac{1-y}{1 - S(x\beta)}\right]  \cdot \frac{\partial S(x\beta)}{\partial \beta^{(j)}} \overset{(*)}{=} \\
= \left[ \frac{y}{S(x\beta)}  - \frac{1-y}{1 - S(x\beta)}\right] \cdot (Sx\beta) (y - S(x\beta))x^{(j)} = \\
= (y(1 - S(x\beta)) - (1-y)(Sx\beta)) x^{(j)}= \\
= (y - yS(x\beta) - S(x\beta) + yS(x\beta)) x^{(j)} = \\
= (y - S(x\beta)) x^{(j)}
$$

# Ex 2
How we will maximize the gradient?


To optimize parameter $\beta^{(j)}$ we use 

$$
\beta^{(j)} = \beta^{(j)} - \alpha \cdot \frac{\partial \ell(\beta)}{\partial \beta^{(j)}}
$$
At first we will calculate $\frac{\partial \ell(\beta)}{\partial \beta^{(j)}}$, let's $(x,y)$ be a training example

$$
\frac{\partial \ell(\beta)}{\partial \beta^{(j)}}
=  \frac{\partial } {\partial \beta^{(j)}} \Big(y \ln S(x\beta) + (1-y) \ln (1-S(x \beta)) \Big) = \\ 
= \left[ \frac{y}{S(x\beta)}  - \frac{1-y}{1 - S(x\beta)}\right] \cdot \frac{\partial S(x\beta)}{\partial \beta^{(j)}} = \\
= \left[ \frac{y}{S(x\beta)}  - \frac{1-y}{1 - S(x\beta)}\right] \cdot (Sx\beta) (y - S(x\beta))x^{(j)} = \\
= (y(1 - S(x\beta)) - (1-y)(Sx\beta)) x^{(j)}= \\
= (y - yS(x\beta) - S(x\beta) + yS(x\beta)) x^{(j)} =  \\
= (y - S(x\beta)) x^{(j)}

$$

since

$$ \frac{\partial S(x\beta)}{\partial \beta} = S( x\beta)(y-S( x\beta))x^{(j)} $$

now we end up with:  

$$ \beta^{(j)} = \beta^{(j)} + \alpha(y_i - S(x_i\beta)) x_i^{(j)} $$
$$ \beta = \beta + \alpha(y_i - S(x_i\beta)) x_i $$