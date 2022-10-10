import numpy
import sympy

print("System of nonlinear equations \n")


m = 0.1
a = 0.6

EPS = 10.0**-5


# Исходные уравнения в формате f(x,y) = 0
(x, y) = sympy.symbols("x y")
eq1 = sympy.tan(x * y + m) - x
eq2 = a * (x**2) + 2 * (y**2) - 1

print(eq1, "= 0")
print(eq2, "= 0")
print()

# Подстановка в исходные уравнения для вычисления значения f(x,y)
def val1(x, y):
    return numpy.tan(x * y + m) - x


def val2(x, y):
    return a * (x**2) + 2 * (y**2) - 1


# Выраженные из исходных уравнений x = функция(x,y), y = функция(x,y)
def eqx(x, y):
    return numpy.tan(x * y + m)


def eqy(x, y):
    return numpy.sqrt((1 - a * (x**2)) / 2)


# Вычисление матрицы Якоби
def W(x, y):
    return numpy.array(
        [
            [
                (1 + numpy.tan(x * y + m) ** 2) * y - 1,
                (1 + numpy.tan(x * y + m) ** 2) * x,
            ],
            [2 * a * x, 4 * y],
        ]
    )


# Графики исходных уравнений
plots = sympy.plot_implicit(
    sympy.Eq(eq1, 0), (x, -2, 2), (y, -2, 2), line_color="blue", show=False
)
plots.extend(
    sympy.plot_implicit(
        sympy.Eq(eq2, 0), (x, -2, 2), (y, -2, 2), line_color="red", show=False
    )
)
# plots.show()


iters = 0


def SimpleSolve(x0, y0):
    global iters
    iters = 0
    (x, y) = (x0, y0)
    while True:
        iters += 1
        oldx = x
        oldy = y
        x = eqx(x, y)
        y = eqy(x, y)
        if not (numpy.isfinite(x) and numpy.isfinite(y)):
            raise RuntimeError("Sequence {x} is divergent")
        if max(abs(x - oldx), abs(y - oldy)) < EPS:
            return (x, y)


def NewtonSolve(x0, y0):
    global iters
    iters = 0
    (x, y) = (x0, y0)
    while True:
        iters += 1
        w = W(x, y)
        f = numpy.array([[val1(x, y)], [val2(x, y)]])
        deltas = numpy.linalg.solve(w, -f)
        x += deltas[0][0]
        y += deltas[1][0]
        if not (numpy.isfinite(x) and numpy.isfinite(y)):
            raise RuntimeError("Sequence {x} is divergent")
        if max(abs(deltas)) < EPS:
            return (x, y)


x0 = 1.0
y0 = 0.5
print("Initial guess =", (x0, y0))
print()


def test(method):
    global iters
    try:
        (x, y) = method(x0, y0)
        print("(x, y) = ({:.4f}, {:.4f})".format(x, y))
        print(" via {} method (with {} iterations)".format(method.__name__, iters))
    except Exception as ex:
        print(
            "ERROR: {} - in {} method (with {} iterations)".format(
                ex, method.__name__, iters
            )
        )
    print()


test(SimpleSolve)
test(NewtonSolve)


plots.show()
