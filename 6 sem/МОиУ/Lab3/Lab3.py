import numpy as np
from scipy.optimize import linprog

# from Lab2 import simplex_method


def initial_phase(c, A, b):
    m, n = A.shape

    # Шаг 1: Преобразование задачи
    negative_indices = np.where(b < 0)[0]
    A[negative_indices] *= -1
    b[negative_indices] *= -1

    # Шаг 2: Составление вспомогательной задачи
    ec = np.concatenate((np.zeros(n), -np.ones(m)))
    Ae = np.hstack((A, np.eye(m)))
    xe = np.concatenate((np.zeros(n), b))

    # Шаг 3: Начальный базисный допустимый план
    B = np.arange(n, n + m)
    x = xe[:n]

    while True:
        # Шаг 4: Решение вспомогательной задачи
        res = linprog(c=ec, A_eq=Ae, b_eq=B, method="simplex")

        # Получение решения и базиса
        x = res.x[:n]
        B = np.where(res.x[n:] != 0)[0]

        # Шаг 5: Проверка условий совместности
        if np.allclose(res.x[3], 0):
            break

        # Шаг 6: Формирование допустимого плана
        j = np.argmax(res.x)
        k = len(B)
        i = j - k

        # Корректировка множества B/////////////

        # Шаг 8: Поиск индекса j, удовлетворяющего условию (ℓ(j))k ≠ 0
        found_j = False
        for p in enumerate(range(n)):
            if p in B:
                r = Ae[:, B]
                L = r.dot(Ae[:, j])
                if L[k - 1] != 0:
                    found_j = True
                    break

        if not found_j:
            Ae = np.delete(Ae, i, axis=0)
            xe = np.delete(xe, i, axis=0)
            B = np.delete(B, np.where(B == n + i)[0][0])

        if found_j:
            for val in B:
                if val == n + i:
                    val = j

    return x, B


# Пример использования
c = np.array([1, 0, 0])
A = np.array([[1, 1, 1], [2, 2, 2]])
b = np.array([0, 0])

x, V = initial_phase(c, A, b)
print("Базисный допустимый план:")
print("x =", x)
print("B =", V)
