import numpy as np


def modify_matrix(A, A_inv, x, i):
    n = A.shape[0]  # Размерность матрицы A
    e = np.zeros(n)
    e[i] = -1

    l = np.dot(A_inv, x)  # Шаг 1
    if l[i] == 0:
        return None  # Матрица A необратима

    le = np.copy(l)
    le[i] = -1  # Шаг 2

    hat_l = -1 / l[i] * le  # Шаг 3

    Q = np.eye(n)
    Q[:, i] = hat_l  # Шаг 4

    A_inv_modified = np.dot(Q, A_inv)  # Шаг 5

    return A_inv_modified


# Генерация случайной квадратной матрицы и вектора

A = np.array([[1, -1, 0], [0, 1, 0], [0, 0, 1]])
A_inv = np.linalg.inv(A)
x = np.array([1, 0, 1])


i = 2
# n = 3  # Размерность матрицы
# A = np.random.rand(n, n)
# A_inv = np.linalg.inv(A)
# x = np.random.rand(n)

print(A)
print(x)
A_inv_modified = modify_matrix(A, A_inv, x, i)
if A_inv_modified is not None:
    print("Матрица A обратима.")
    print("Обратная матрица (A)^(-1):")
    print(A_inv_modified)
else:
    print("Матрица A необратима.")
