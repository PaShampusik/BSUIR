print("Polynomial interpolation \n")

import numpy as np
import matplotlib.pyplot as plt


def input():

    x = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
    p = [0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01]
    k = 13
    m = 5.33
    y = [(p[i] + ((-1) ** k) * m) for i in range(len(x))]
    dots = list(zip(x, y))

    # dots = [(3, 2), (2, 3)]
    # dots = [(2, 1), (3, 2), (4, 1), (5, 3)]
    # dots = [(1, 2), (2, 4), (3, 6), (4, 8), (5, 10)]
    # dots = [(1, 1), (2, 3), (3, 5), (4, 7), (5, 217341)]
    # dots = [
    #     (-1.5, np.arctan(-1.5)),
    #     (-0.75, np.arctan(-0.75)),
    #     (0, np.arctan(0)),
    #     (0.75, np.arctan(0.75)),
    #     (1.5, np.arctan(1.5)),
    # ]

    # dots = [(, ), ]

    return dots


dots = input()
(x, y) = map(list, zip(*dots))
print("(x,y) =", dots, "\n")


def Lagrange(dots):
    n = len(dots)
    (x, y) = map(list, zip(*dots))
    polynom = np.poly1d([0])
    for i in range(n):
        p = np.poly1d([1])
        for j in range(n):
            if j != i:
                p *= np.poly1d([1, -x[j]]) / (x[i] - x[j])
        polynom += y[i] * p
    return polynom


lagr = Lagrange(dots)
print("Lagrange polynom =")
print(lagr, "\n")


def DividedDifferences(xs):
    n = len(xs)
    diffs = [[None for j in range(n - i)] for i in range(n)]
    for i in range(n):
        diffs[i][0] = y[i]
    for j in range(1, n):
        for i in range(n - j):
            diffs[i][j] = (diffs[i][j - 1] - diffs[i + 1][j - 1]) / (xs[i] - xs[i + j])
    return diffs


def Inaccuracy(xs, xdot):
    n = len(xs)
    diffs = DividedDifferences(xs)
    maxdiff = 0.0
    for i in range(len(diffs)):
        for j in range(len(diffs[i])):
            maxdiff = max(maxdiff, abs(diffs[i][j]))
    w = 1
    for i in range(n):
        w *= xdot - xs[i]
    f = 1
    for i in range(1, n + 1 + 1):
        f *= i
    R = maxdiff * w / f
    return R


def Newton(dots):
    n = len(dots)
    (x, y) = map(list, zip(*dots))

    diffs = DividedDifferences(x)

    polynom = np.poly1d([0])
    for i in range(n):
        p = np.poly1d([1])
        for j in range(i):
            p *= np.poly1d([1, -x[j]])
        polynom += p * diffs[0][i]

    return polynom


newt = Newton(dots)
print("Newton polynom =")
print(newt, "\n")


def Simple(dots):
    n = len(dots)
    (x, y) = map(list, zip(*dots))
    A = []
    for i in range(n):
        A.append([])
        for j in range(n):
            A[i].append(x[i] ** j)
    polynom = np.poly1d(np.linalg.solve(A, y)[::-1])
    return polynom


xdot = 0.47
print(f"Largange({xdot}) =", lagr(xdot))
print(f"Newton({xdot}) =", newt(xdot))

print("|Largange - Newton| =", abs(lagr(xdot) - newt(xdot)))

print(f"Inaccuracy({xdot}) = ", Inaccuracy(x, xdot))


plotdots = 10**4

plt.plot(x, y, "og")

xplot = np.linspace(min(x), max(x), plotdots)


yplot = [lagr(xdot) for xdot in xplot]
plt.plot(xplot, yplot, "b")

yplot = [newt(xdot) for xdot in xplot]
plt.plot(xplot, yplot, "r--")


plt.show()
