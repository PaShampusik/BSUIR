print("Adams' method \n")

import numpy as np
import matplotlib.pyplot as plt
import math

plotdots = 20  # 10**3
eps = 10**-3


# def yder(x, y):
#     return y


# y0 = 1
# LEFT, RIGHT = -1, 1


# def ans(x):
#     return np.exp(x)


# xplot = np.linspace(LEFT, RIGHT, plotdots)
# yplot = [ans(xdot) for xdot in xplot]
# plt.plot(xplot, yplot, "black")


# def yder(x, y):
#     return x**2 - y


# y0 = 1
# LEFT, RIGHT = -1, 1


# def ans(x):
#     return x**2 - 2 * x + 2 - math.exp(-x)


# xplot = np.linspace(LEFT, RIGHT, plotdots)
# yplot = [ans(xdot) for xdot in xplot]
# plt.plot(xplot, yplot, "black")


# def yder(x, y):
#     return np.exp(-x)


# y0 = -1
# LEFT, RIGHT = -1, 1


# def ans(x):
#     return -np.exp(-x)


# xplot = np.linspace(LEFT, RIGHT, plotdots)
# yplot = [ans(xdot) for xdot in xplot]
# plt.plot(xplot, yplot, "black")

m, a = 1.0, 0.9


def yder(x, y):
    return (a * (1 - y**2)) / ((1 + m) * x**2 + y**2 + 1)


y0 = 0
LEFT, RIGHT = 0, 1


def RungeKutta(xdot, N):
    ydots = [y0]
    h = xdot / N
    for i in range(N):
        x = i * h
        y = ydots[-1]
        K1 = h * yder(x, y)
        K2 = h * yder(x + h / 2, y + K1 / 2)
        K3 = h * yder(x + h / 2, y + K2 / 2)
        K4 = h * yder(x + h, y + K3)
        ydots += [y + 1 / 6 * (K1 + 2 * K2 + 2 * K3 + K4)]
    return ydots


def GetValueAtPoint(method, x):
    n = 1
    while True:
        olddots, newdots = method(x, n), method(x, 2 * n)
        if max(abs(newdots[2 * i] - olddots[i]) for i in range(n + 1)) < eps:
            if method == Adams:
                with open("Lab_10.txt", "a") as file:
                    file.write(str(2 * n) + ", ")
            return newdots[-1], 2 * n
            # print(max(abs(newdots[i] - ans(LEFT + i * (RIGHT - LEFT) / (2*n))) for i in range(2*n+1)))
            # if (
            #     max(
            #         abs(newdots[i] - ans(LEFT + i * (RIGHT - LEFT) / (2 * n)))
            #         for i in range(2 * n + 1)
            #     )
            #     < eps
            # ):
            return 2 * n
        else:
            n *= 2


def CreateYdots(method, xdots):
    ydots = []
    maxn = 0
    midn = []
    for x in xdots:
        y, n = GetValueAtPoint(method, x)
        ydots.append(y)
        maxn = max(maxn, n)
        midn += [n]
    midn = sum(midn) / len(xdots)
    return ydots, midn, maxn


def Adams(xdot, N):
    ydots = [y0]
    h = xdot / N
    xprev = -h
    yprev = GetValueAtPoint(RungeKutta, xprev)[0]
    fprev = yder(xprev, yprev)
    for i in range(N):
        x = i * h
        y = ydots[-1]
        flast = yder(x, y)
        ydots += [y + h * (3 / 2 * flast - 1 / 2 * fprev)]
        fprev = flast
    return ydots


print("Dots for calculating = ", plotdots)
print("Epsilon = ", eps)
xdots = [LEFT + (RIGHT - LEFT) / plotdots * i for i in range(plotdots + 1)]
print(len(xdots))


ydots, midn, maxn = CreateYdots(Adams, xdots)
# miss = sum(abs(ydots[i] - ans(xdots[i])) for i in range(len(xdots)))
# miss = miss / len(xdots)


print("\n MidN / MaxN per dot in " + "Adams" + " method       = ", midn, " / ", maxn)
# print("Miss per dot in " + "Adams" + " method       = ", miss)
plt.plot(xdots, ydots, "g")

plt.show()
