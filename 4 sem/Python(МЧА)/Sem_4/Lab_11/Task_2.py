import numpy as np

import math
import scipy as sp
from scipy import sparse
import matplotlib.pyplot as plt

# variant number
K = 30


def solve_de(px, fx, a, b, n=2000):
    h = (b - a) / n
    X = np.linspace(a, b, n + 1)  # строим сетку иксов
    P = px(X)

    # data содержит три вектора:
    # первый - значения диагонали ниже главной;
    # второй - значения главной диагонали;
    # третий - значения диагонали выше главной.

    data = np.array(
        [[1] * (n - 1), [-(h * h * P[i] + 2) for i in range(1, n)], [1] * (n - 1)]
    )

    offsets = [-1, 0, 1]  # отступы относительно главной диагонали

    # строим трехдиагональную матрицу
    M = sparse.dia_matrix((data, offsets), shape=(n - 1, n - 1)).toarray()
    M = np.insert(M, 0, np.array([0] * (n - 1)), 0)
    M = np.insert(M, n, np.array([0] * (n - 1)), 0)
    M = np.insert(M, 0, np.array([1, 1] + [0] * (n - 1)), 1)
    M = np.insert(M, n, np.array([0] * (n - 1) + [1, 1]), 1)
    print(M)

    F = fx(X) * h * h
    F[0] = 0
    F[-1] = 0

    print(F)
    solution = np.linalg.solve(M, F)
    return X, solution


# Второй случай
def px2(x):
    return -(1 + np.cos(K) * x * x) / np.sin(K)


def fx2(x):
    return (x - x) - 1 / np.sin(K)


X, sol2 = solve_de(px2, fx2, -1, 1)

plt.plot(X, sol2)
plt.xlabel("$x$")
plt.ylabel("$y$")


print(np.min(sol2))

nset = [10, 20, 100, 200, 500]

for i in nset:
    X, solution = solve_de(px2, fx2, -1, 1, i)
    plt.plot(X, solution)
