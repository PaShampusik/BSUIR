import math
import sympy

x = sympy.Symbol("x")

VARIANT = 30
VARIABLES = 3
DIFF_POINTS = 5

a = -1
b = 1

COEFFS = [
    lambda c: 1 + math.cos(VARIANT) * c**2,
    lambda c: 0,
    lambda c: math.sin(VARIANT),
]

# COEFFS = [lambda c: 1 + c**2, lambda c: 0, lambda c: 1]

f = lambda d: -1
