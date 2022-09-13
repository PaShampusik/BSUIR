import numpy

print("Gaussian elimination \n")


def input():
    b = numpy.array([[4.2], [4.2], [4.2], [4.2], [4.2]])
    C = numpy.array(
        [
            [0.2, 0.0, 0.2, 0.0, 0.0],
            [0.0, 0.2, 0.0, 0.2, 0.0],
            [0.2, 0.0, 0.2, 0.0, 0.2],
            [0.0, 0.2, 0.0, 0.2, 0.0],
            [0.0, 0.0, 0.2, 0.0, 0.2],
        ]
    )
    D = numpy.array(
        [
            [2.33, 0.81, 0.67, 0.92, -0.53],
            [-0.53, 2.33, 0.81, 0.67, 0.92],
            [0.92, -0.53, 2.33, 0.81, 0.67],
            [0.67, 0.92, -0.53, 2.33, 0.81],
            [0.81, 0.67, 0.92, -0.53, 2.33],
        ]
    )
    A = 15 * C + D
    # A = numpy.array([
    #     [0.0, 3.0]
    #     [3.0,2.0]
    # ])
    return (A, b)


def nan(n):
    v = numpy.zeros((n, 1))
    print("V: ", v, end="\n")
    v[:] = numpy.NaN
    return v


def basechoice(A, b):
    n = A.shape[0]

    for i in range(n):
        for k in range(i + 1, n):
            if A[i, i] == 0.0:
                return nan(n)
            q = A[k, i] / A[i, i]
            for j in range(n):
                A[k, j] -= A[i, j] * q
            b[k] -= b[i] * q

    x = numpy.zeros((n, 1))
    for i in range(n - 1, -1, -1):
        for j in range(i + 1, n):
            b[i] -= A[i, j] * x[j]
        if A[i, i] == 0.0:
            return nan(n)
        x[i] = b[i] / A[i, i]

    return x


def partchoice(A, b):
    n = A.shape[0]

    for i in range(n):
        maxi = i
        for k in range(i, n):
            if abs(A[k, i]) > abs(A[maxi, i]):
                maxi = k
        A[[i, maxi]] = A[[maxi, i]]
        b[[i, maxi]] = b[[maxi, i]]

        for k in range(i + 1, n):
            if A[i, i] == 0.0:
                return nan(n)
            q = A[k, i] / A[i, i]
            for j in range(n):
                A[k, j] -= A[i, j] * q
            b[k] -= b[i] * q

    x = numpy.zeros((n, 1))
    for i in range(n - 1, -1, -1):
        for j in range(i + 1, n):
            b[i] -= A[i, j] * x[j]
        if A[i, i] == 0.0:
            return nan(n)
        x[i] = b[i] / A[i, i]

    return x


def fullchoice(A, b):
    n = A.shape[0]

    for i in range(n):
        maxi = (i, 0)
        for k in range(i, n):
            for j in range(n):
                if abs(A[k, j]) > abs(A[maxi[0], maxi[1]]):
                    maxi = (k, j)
        A[[i, maxi[0]]] = A[[maxi[0], i]]
        b[[i, maxi[0]]] = b[[maxi[0], i]]

        for k in range(n):
            if k != i:
                if A[i, maxi[1]] == 0.0:
                    return nan(n)
                q = A[k, maxi[1]] / A[i, maxi[1]]
                for j in range(n):
                    A[k, j] -= A[i, j] * q
                b[k] -= b[i] * q

    x = numpy.zeros((n, 1))
    for j in range(n):
        maxi = (i, 0)
        for i in range(n):
            if abs(A[i, j]) > abs(A[maxi[0], maxi[1]]):
                maxi = (i, j)
        if A[maxi[0], maxi[1]] == 0.0:
            return nan(n)
        x[j] = b[maxi[0]] / A[maxi[0], maxi[1]]

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
    print("--------")


def test(method):
    (A, b) = input()
    x = method(A.copy(), b.copy())
    output(A, x, b)


test(basechoice)
test(partchoice)
test(fullchoice)
