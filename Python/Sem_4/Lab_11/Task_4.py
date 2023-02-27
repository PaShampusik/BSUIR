import matplotlib.pyplot as plt
import numpy as np

a, b = 0.2, 0.5
A, B = 2, np.e
n = 10
h = (b - a) / n
D0, D1 = A + h, h

y = [[A, D0], [0, D1]]


def p(x):
    return 2


def q(x):
    return -1 / x


def f(x):
    return 3


def get_c1():
    global n
    return (B - y[0][n]) / y[1][n]


def get_solv_y_i(i):
    return y[0][i] + get_c1() * y[1][i]


x = np.linspace(a, b, n + 1)


def div(a, b):
    return a / b


for i in range(1, n):
    y[0].append(
        div(
            (
                h**2 * f(x[i])
                - (1.0 - (h / 2) * p(x[i])) * y[0][i - 1]
                - (h**2 * q(x[i]) - 2) * y[0][i]
            ),
            1 + h / 2 * p(x[i]),
        )
    )
    y[1].append(
        div(
            -(1 - h / 2 * p(x[i])) * y[1][i - 1] - (h**2 * q(x[i]) - 2) * y[1][i],
            1 + h / 2 * p(x[i]),
        )
    )

plt.plot(x, [get_solv_y_i(i) for i in range(n + 1)])
plt.show()

for i in range(n):
    print(x[i], get_solv_y_i(i))
