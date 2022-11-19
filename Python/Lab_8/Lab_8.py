print("Numerical Differentiation and Integration \n")

import numpy as np
import math

np.random.seed(42)


L, R, DerXdot = 0, 2, 1


def f(x):
    return np.arctan(np.sqrt(x))


def F(x):
    return x * np.arctan(np.sqrt(x)) - np.sqrt(x) + np.arctan(np.sqrt(x))


def fd1(x):
    return 1 / (2 * (x ** (1 / 2)) * (1 + x))


def fd2(x):
    return -1 / (4 * x ** (3 / 2) * (1 + x)) - 1 / (2 * (x ** (1 / 2)) * (1 + x) ** 2)


def fd3(x):
    return (
        3 / (8 * x ** (5 / 2) * (1 + x))
        + 1 / (2 * x ** (3 / 2) * (1 + x) ** 2)
        + 1 / ((x ** (1 / 2)) * (1 + x) ** 3)
    )


def fd4(x):
    return (
        -15 / (16 * x ** (7 / 2) * (1 + x))
        - 9 / (8 * x ** (5 / 2) * (1 + x) ** 2)
        - 3 / (2 * x ** (3 / 2) * (1 + x) ** 3)
        - 3 / ((x ** (1 / 2)) * (1 + x) ** 4)
    )


M2deLR, M4deLR = 0, 0

L, R, DerXdot = -1, 3, 1


def f(x):
    return np.exp(x)


def F(x):
    return np.exp(x)


def fd1(x):
    return np.exp(x)


def fd2(x):
    return np.exp(x)


def fd3(x):
    return np.exp(x)


def fd4(x):
    return np.exp(x)


M2deLR, M4deLR = np.exp(R), np.exp(R)
M2deLR, M4deLR = 0, 0

# L, R, DerXdot = 0, 2, 1


# def f(x):
#     return -(x**4)


# def F(x):
#     return -(x**5) / 5


# def fd1(x):
#     return -4 * x**3


# def fd2(x):
#     return -12 * x**2


# def fd3(x):
#     return -24 * x


# def fd4(x):
#     return -24


# M2deLR, M4deLR = 0, 0

# L, R, DerXdot = 0, 2 * np.pi, np.pi
# BIG_CONST = np.pi


# def f(x):
#     return -np.cos(x)


# def F(x):
#     return -np.sin(x)


# def fd1(x):
#     return np.sin(x)


# def fd2(x):
#     return np.cos(x)


# def fd3(x):
#     return -np.sin(x)


# def fd4(x):
#     return -np.cos(x)


# M2deLR, M4deLR = BIG_CONST**3, BIG_CONST**5
# M2deLR, M4deLR = 0, 0


# from sympy import *
# from mpmath import *
# L, R = 0, 1
# def f(x): return Float(besselj(0, 100*x))
# def F(x): return 0
# M2deLR, M4deLR = 0, 0


IntEps = 0.000001
IntFormatString = "{:.7f}"

DerEps = 0.01
DerFormatString = "{:.3f}"


def DerivativeFirst(f, x, d):
    return (f(x + d) - f(x - d)) / (2 * d)


def DerivativeFirstViaEstimation(f, x):
    M2 = abs(fd2(x))
    df = 2 * DerEps / M2
    M3 = abs(fd3(x))
    ds = (6 * DerEps / M3) ** (1 / 2)
    return DerivativeFirst(f, x, min(df, ds))


def DerivativeFirstViaTenInMinus5(f, x):
    d = 10.0**-5
    return DerivativeFirst(f, x, d)


def DerivativeSecond(f, x, d):
    return (f(x + d) - 2 * f(x) + f(x - d)) / (d**2)


def DerivativeSecondViaEstimation(f, x):
    M4 = abs(fd4(x))
    d = (12 * DerEps / M4) ** (1 / 2)
    return DerivativeSecond(f, x, d)


def DerivativeSecondViaTenInMinus4(f, x):
    d = 10.0**-4
    return DerivativeSecond(f, x, d)


print()


def delta(derappr):
    return np.ceil(abs(derappr - fd1(DerXdot)) * (1 / (DerEps / 10))) * (DerEps / 10)


print("First Derivative = " + DerFormatString.format(fd1(DerXdot)))
print(
    "ViaEstimation    = "
    + DerFormatString.format(DerivativeFirstViaEstimation(f, DerXdot)),
    " | delta = "
    + DerFormatString.format(delta(DerivativeFirstViaEstimation(f, DerXdot))),
)
print(
    "ViaTenInMinus5   = "
    + DerFormatString.format(DerivativeFirstViaTenInMinus5(f, DerXdot)),
    " | delta = "
    + DerFormatString.format(delta(DerivativeFirstViaTenInMinus5(f, DerXdot))),
)
print()


def delta(derappr):
    return np.ceil(abs(derappr - fd2(DerXdot)) * (1 / (DerEps / 10))) * (DerEps / 10)


print("Second Derivative = " + DerFormatString.format(fd2(DerXdot)))
print(
    "ViaEstimation     = "
    + DerFormatString.format(DerivativeSecondViaEstimation(f, DerXdot)),
    " | delta = "
    + DerFormatString.format(delta(DerivativeSecondViaEstimation(f, DerXdot))),
)
print(
    "ViaTenInMinus4    = "
    + DerFormatString.format(DerivativeSecondViaTenInMinus4(f, DerXdot)),
    " | delta = "
    + DerFormatString.format(delta(DerivativeSecondViaTenInMinus4(f, DerXdot))),
)
print()


def IntegralViaMiddleRectangles(f, L, R, N):
    h = (R - L) / N
    x = L + h / 2
    s = 0.0
    while x < R:
        s += f(x) * h
        x += h
    return s


def IntegralViaTrapezoids(f, L, R, N):
    h = (R - L) / N
    x = L + h / 2
    s = 0.0
    while x < R:
        s += ((f(x - h / 2) + f(x + h / 2)) / 2) * h
        x += h
    return s


def IntegralViaSimpson(f, L, R, N):
    h = (R - L) / N
    x = L + h / 2
    s = 0.0
    while x < R:
        fa = f(x - h / 2)
        fm = f(x)
        fb = f(x + h / 2)
        s += (fa + 4 * fm + fb) * h / 6
        x += h
    return s


def IntegralViaRandomSegments(method, f, L, R):
    LeftCoeff, RightCoeff = 1 / 3, 1 / 2
    h_prev = R - L
    ans_prev = method(f, L, R, 1)
    while True:
        h_new = h_prev * (LeftCoeff + (RightCoeff - LeftCoeff) * np.random.rand())
        N = math.floor((R - L) / h_new)
        M = L + h_new * N
        ans_new = method(f, L, M, N) + method(f, M, R, 1)
        if abs(ans_new - ans_prev) < IntEps:
            print("\nRandom intervals: N =", N)
            return ans_new
        ans_prev = ans_new
        h_prev = h_new


def IntegralViaMiddleRectanglesViaEstimation(f, L, R):
    if M2deLR > 0.0:
        M2 = M2deLR
        h = (24 * IntEps / (R - L) / M2) ** (1 / 2)
        N = np.ceil((R - L) / h)
        return IntegralViaMiddleRectangles(f, L, R, N)
    else:
        return IntegralViaRandomSegments(IntegralViaMiddleRectangles, f, L, R)


def IntegralViaTrapezoidsViaEstimation(f, L, R):
    if M2deLR > 0.0:
        M2 = M2deLR
        h = (12 * IntEps / (R - L) / M2) ** (1 / 2)
        N = np.ceil((R - L) / h)
        return IntegralViaTrapezoids(f, L, R, N)
    else:
        return IntegralViaRandomSegments(IntegralViaTrapezoids, f, L, R)


def IntegralViaSimpsonViaEstimation(f, L, R):
    if M4deLR > 0.0:
        M4 = M4deLR
        h = (180 * IntEps / (R - L) / M4) ** (1 / 4)
        N = np.ceil((R - L) / h)
        return IntegralViaSimpson(f, L, R, N)
    else:
        return IntegralViaRandomSegments(IntegralViaSimpson, f, L, R)


print()
intprecised = F(R) - F(L)
print("Integral =            " + IntFormatString.format(intprecised))


def delta(intappr):
    return np.ceil(abs(intappr - intprecised) * (1 / (IntEps / 10))) * (IntEps / 10)


intappr = IntegralViaMiddleRectanglesViaEstimation(f, L, R)
print(
    (
        "ViaMiddleRectangles = " + IntFormatString + " | delta = " + IntFormatString
    ).format(intappr, delta(intappr))
)
intappr = IntegralViaTrapezoidsViaEstimation(f, L, R)
print(
    (
        "ViaTrapezoids       = " + IntFormatString + " | delta = " + IntFormatString
    ).format(intappr, delta(intappr))
)
intappr = IntegralViaSimpsonViaEstimation(f, L, R)
print(
    (
        "ViaSimpson          = " + IntFormatString + " | delta = " + IntFormatString
    ).format(intappr, delta(intappr))
)
print()
