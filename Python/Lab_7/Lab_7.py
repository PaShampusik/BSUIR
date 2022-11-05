print("Cubic spline interpolation \n")

import numpy as np
import matplotlib.pyplot as plt

plotdots = 10**4


def input():

    # def f(x): return np.sin(4 * x)
    # LEFT, DOTS_COUNT, RIGHT = -1, 7, 1

    # def f(x):
    #     return np.sin(x) + np.cos(4 * x)

    # LEFT, DOTS_COUNT, RIGHT = -10, 7, 10

    def f(x):
        return np.cosh(x)

    LEFT, DOTS_COUNT, RIGHT = 0, 120, 2

    dots = []
    for i in range(DOTS_COUNT):
        x = LEFT + (RIGHT - LEFT) * i / (DOTS_COUNT - 1)
        y = f(x)
        dots += [(x, y)]

    return dots, f


dots, f = input()
(x, y) = map(list, zip(*dots))
print("(x,y) =", dots, "\n")

plt.plot(x, y, "og")
xplot = np.linspace(min(x), max(x), plotdots)

yplot = [f(xdot) for xdot in xplot]
plt.plot(xplot, yplot, "black")


def tridiag_solve(A, b):
    A = A.copy()
    b = b.copy()
    n = len(A)

    A[0][1] /= A[0][0]
    for i in range(1, n - 1):
        A[i][i + 1] /= A[i][i] - A[i][i - 1] * A[i - 1][i]

    b[0] /= A[0][0]
    for i in range(1, n):
        b[i] = (b[i] - A[i][i - 1] * b[i - 1]) / (A[i][i] - A[i][i - 1] * A[i - 1][i])

    x = np.zeros(n)
    x[-1] = b[-1]
    for i in range(n - 2, -1, -1):
        x[i] = b[i] - A[i][i + 1] * x[i + 1]

    return x


def Spline(dots):

    n = len(dots) - 1
    (x, y) = map(list, zip(*dots))

    h = [None]
    for i in range(1, n + 1):
        h += [x[i] - x[i - 1]]

    A = [[None] * (n) for i in range(n)]
    for i in range(1, n):
        for j in range(1, n):
            A[i][j] = 0.0
    for i in range(1, n - 1):
        A[i + 1][i] = h[i + 1]
    for i in range(1, n):
        A[i][i] = 2 * (h[i] + h[i + 1])
    for i in range(1, n - 1):
        A[i][i + 1] = h[i + 1]

    F = []
    for i in range(1, n):
        F += [3 * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i])]

    A = [A[i][1:] for i in range(len(A)) if i]

    c = tridiag_solve(A, F)
    c = [0.0] + list(c) + [0.0]

    def evaluate(xdot):
        for i in range(1, len(x)):
            if x[i - 1] <= xdot <= x[i]:
                val = 0
                val += y[i]
                b = (y[i] - y[i - 1]) / h[i] + (2 * c[i] + c[i - 1]) * h[i] / 3
                val += b * (xdot - x[i])
                val += c[i] * ((xdot - x[i]) ** 2)
                d = (c[i] - c[i - 1]) / (3 * h[i])
                val += d * ((xdot - x[i]) ** 3)
                return val
        return None

    def cout():
        print("Cubic spline:", "\n")
        for i in range(1, len(x)):
            val = 0
            b = (y[i] - y[i - 1]) / h[i] + (2 * c[i] + c[i - 1]) * h[i] / 3
            d = (c[i] - c[i - 1]) / (3 * h[i])
            print(x[i - 1], x[i], "->")
            print(np.poly1d([d, c[i], b, y[i]]), "\n")

    return evaluate, cout


spl, cout = Spline(dots)
yplot = [spl(xdot) for xdot in xplot]
plt.plot(xplot, yplot, "b")

cout()

xdot = 1.0
print(f"          f({xdot}) =", f(xdot))
print(f"CubicSpline({xdot}) =", spl(xdot))
print(f"      delta({xdot}) =", abs(f(xdot) - spl(xdot)))

plt.show()
