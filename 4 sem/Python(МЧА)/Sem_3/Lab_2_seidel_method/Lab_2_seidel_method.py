import numpy

numpy.set_printoptions(suppress=True, precision=4, floatmode="fixed")

print("Iterative method \n")

numpy.seterr(over="ignore")


def input():
    b = numpy.array([[1.2], [2.2], [4.0], [0.0], [-1.2]])
    C = numpy.array(
        [
            [0.02, 0, -0.02, 0, 0],
            [0.01, 0.01, -0.02, 0, 0],
            [0, 0.01, 0.01, 0, -0.02],
            [0, 0, 0.01, 0.01, 0],
            [0, 0, 0, 0.01, 0.01],
        ]
    )
    D = numpy.array(
        [
            [1.33, 0.21, 0.17, 0.12, -0.13],
            [-0.13, -1.33, 0.11, 0.17, 0.12],
            [0.12, -0.13, -1.33, 0.11, 0.17],
            [0.17, 0.12, -0.13, -1.33, 0.11],
            [0.11, 0.67, 0.12, -0.13, -1.33],
        ]
    )
    A = 15 * C + D
    # A = numpy.array([[2.5, 3.0], [2.0, -2.5]])
    return (A, b)


EPS = 10.0**-5


def nan(n):
    v = numpy.zeros((n, 1))
    v[:] = numpy.NaN
    return v


def AlphaMatrix(A):
    n = A.shape[0]
    alpha = numpy.zeros((n, n))
    for i in range(n):
        for j in range(n):
            alpha[i, j] = -A[i, j] / A[i, i]
        alpha[i, i] = 0
    return alpha


def Norms(A):
    n = A.shape[0]
    f = max(numpy.absolute(A[i]).sum() for i in range(n))
    s = max(numpy.absolute(A.T[j]).sum() for j in range(n))
    t = ((A**2).sum()) ** (1 / 2)
    print(f, s, t)
    return (f, s, t)


def simple(A, b):
    n = A.shape[0]

    for i in range(n):
        if A[i, i] == 0.0:
            print("ERROR: Zero diagonal element")
            return nan(n)

    alpha = AlphaMatrix(A)
    if not (min(Norms(alpha)) < 1):
        print("Warning: ||B|| is not < 1")
        # return nan(n)
    beta = numpy.zeros((n, 1))
    for i in range(n):
        beta[i] = b[i] / A[i, i]

    x = numpy.zeros((n, 1))
    count = 0
    deltax = EPS
    deltaf = EPS
    while deltax + deltaf > EPS:
        oldx = x
        x = beta + alpha.dot(x)
        deltax = numpy.absolute((x - oldx)).max()
        deltaf = numpy.absolute((A.dot(x) - b)).max()
        if not numpy.isfinite(deltax + deltaf):
            print("ERROR: Sequence {x} is divergent")
            return nan(n)
        count += 1
        # print(count, ":    ", x, end="\n")

    print("Iteration count in simple method:")
    print(count)
    return x


def seidel(A, b):
    n = A.shape[0]

    for i in range(n):
        if A[i, i] == 0.0:
            print("ERROR: Zero diagonal element")
            return nan(n)

    alpha = AlphaMatrix(A)
    if not (min(Norms(alpha)[:2]) < 1):
        print("Warning: Seidel's method may be divergent")
        # return nan(n)

    x = numpy.zeros((n, 1))
    count = 0
    deltax = EPS
    deltaf = EPS
    while deltax + deltaf > EPS:
        oldx = x.copy()
        for i in range(n):
            s = 0
            for j in range(n):
                s += A[i, j] * x[j]
            s -= b[i]
            x[i] = x[i] - s / A[i, i]
        deltax = numpy.absolute((x - oldx)).max()
        deltaf = numpy.absolute((A.dot(x) - b)).max()
        if not numpy.isfinite(deltax + deltaf):
            print("ERROR: Sequence {x} is divergent")
            return nan(n)
        count += 1
        # print(count, ":    ", x, end="\n")

    print("Iteration count in Seidel's method:")
    print(count)
    return x


def output(A, x, b):

    numpy.set_printoptions(suppress=True, precision=4, floatmode="fixed")

    print("A = ")
    print(A)

    print("x = ")
    print(x.T)

    print("Check: b = ")
    print(b.T)
    print(A.dot(x).T)
    print("----------")


def test(method):
    (A, b) = input()
    x = method(A.copy(), b.copy())
    output(A, x, b)


test(simple)
test(seidel)
