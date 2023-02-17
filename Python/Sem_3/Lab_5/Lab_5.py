import numpy

print("Eigenvalues and eigenvectors \n")


EPS = 10.0**-6

numpy.set_printoptions(suppress=True, precision=4, floatmode="fixed")


def input():
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
            [0.81, 2.33, 0.81, 0.67, 0.92],
            [0.67, 0.81, 2.33, 0.81, 0.92],
            [0.92, 0.67, 0.81, 2.33, -0.53],
            [-0.53, 0.92, 0.92, -0.53, 2.33],
        ]
    )

    A = 15 * C + D
    # A = numpy.array(
    #     [
    #         [1.0, 0.0],
    #         [0.0, 2.0],
    #     ]
    # )
    return A


A = input()
n = len(A)
print("A = ")
print(A)

if abs((A - A.T) ** 2).sum() > EPS:
    # if (abs(A - A.T).sum() > EPS):
    raise ValueError("Matrix A is non-symmetric")

iters = 0
# метод вращения Якоби
ansV = numpy.eye(n)
while True:
    iters += 1
    maxelem = (0, 1)
    for i in range(n):
        for j in range(i + 1, n):
            if abs(A[i][j]) > abs(A[maxelem]):
                maxelem = (i, j)
    (i, j) = maxelem
    if A[i][i] == A[j][j]:
        p = numpy.pi / 4
    else:
        p = 2 * A[i][j] / (A[i][i] - A[j][j])
    c = numpy.cos(1 / 2 * numpy.arctan(p))
    s = numpy.sin(1 / 2 * numpy.arctan(p))
    V = numpy.eye(n)
    V[i][i] = c
    V[i][j] = -s
    V[j][i] = s
    V[j][j] = c
    A = V.T @ A @ V
    ansV = ansV @ V
    # if ((A ** 2).sum() - (numpy.diag(A) ** 2).sum() < EPS):
    if abs(A - numpy.diag(numpy.diag(A))).sum() < EPS:
        ansW = numpy.diag(A)
        break


def Normalization(W, V):
    V = numpy.array([(-i if i[0] < 0 else i) for i in V.T]).T
    (W, V) = list(zip(*(sorted(list(zip(W, V.T)), key=lambda t: t[0]))))
    W = numpy.array(W)
    V = numpy.array(V).T
    return (W, V)


A = input()

print("-----")
print("Answer:")
(W, V) = Normalization(ansW, ansV)
print("Eigenvalues =")
print(W)
print("Eigenvectors =")
print(V)
print("Iterations count =", iters)

print("-----\n\n-----")
print("Check:")
(npW, npV) = Normalization(*numpy.linalg.eig(input()))
print(npW)
print(npV)

print("-----")
print("Test:")
print(
    "Max of elems in [AX – ЛX] = {:.4f}".format(
        max(abs(A[:, :] @ V[:, i] - W[i] * V[:, i]).max() for i in range(n))
    )
)
print(
    "Max of elems in etalon [AX – ЛX] = {:.4f}".format(
        max(abs(A[:, :] @ npV[:, i] - npW[i] * npV[:, i]).max() for i in range(n))
    )
)

print("-----P.S.-----")
A = input()
r = numpy.ones(len(A))
iters = 0
while True:
    iters += 1
    oldu = (r.T @ A @ r) / (r.T @ r)
    r = (A @ r) / numpy.sqrt(sum((A @ r) ** 2))
    u = (r.T @ A @ r) / (r.T @ r)
    if abs(u - oldu) < EPS:
        break
print("Max eigenvalue and it's eigenvector via Power iteration:")
print("{:.4f} ; {}".format(u, r))
print("Iterations count =", iters)
print("Max of elems in [AX – ЛX] = {:.4f}".format(abs(A @ r - u * r).max()))
