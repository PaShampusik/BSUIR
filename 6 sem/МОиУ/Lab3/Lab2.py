import numpy as np


def simplex_method(c, A, b, B):
    m, n = A.shape
    iterations = 0

    while True:
        iterations += 1

        # Шаг 1: Строим базисную матрицу и находим ее обратную
        AB = A[:, B]
        AB_inv = np.linalg.inv(AB)

        # Шаг 2: Формируем вектор cB
        cB = c[B]

        # Шаг 3: Находим вектор потенциалов u
        u = np.dot(cB, AB_inv)

        # Шаг 4: Находим вектор оценок ∆
        delta = np.dot(u, A) - c

        # Шаг 5: Проверяем условие оптимальности
        if np.all(delta >= 0):
            # Текущий план является оптимальным
            return b

        # Шаг 6: Находим первую отрицательную компоненту в ∆
        j0 = np.argmin(delta)

        # Шаг 7: Вычисляем вектор z
        Aj0 = A[:, j0]
        z = np.dot(AB_inv, Aj0)

        # Шаг 8: Вычисляем вектор θ
        theta = np.full(m, np.inf)
        positive_indices = np.where(z > 0)[0]
        theta[positive_indices] = np.take(b, B[positive_indices]) / z[positive_indices]

        # Шаг 9: Находим минимальное θ0
        theta0 = np.min(theta)

        # Шаг 10: Проверяем условие неограниченности
        if theta0 == np.inf:
            return "Целевой функционал неограничен сверху"

        # Шаг 11: Находим индекс j*
        k = np.argmin(theta)
        j_star = B[k]

        # Шаг 12: Заменяем j* на j0 в базисном множестве B
        B[k] = j0

        # Шаг 13: Обновляем план x
        b[j0] = theta0
        for i in range(m):
            if i != k:
                if i != j_star:
                    b[B[i]] -= theta0 * z[i]
                else:
                    b[B[i]] = 0
        b[j_star] = 0

        # Переходим к следующей итерации


# Пример задачи:
c = np.array([0, 0, 0, -1, -1])
A = np.array([[1, 1, 1, 1, 0], [2, 2, 2, 0, 1]])
b = np.array([0, 0, 1, 3, 2])
B = np.array([2, 3, 4])  # Начальное базисное множество

result = simplex_method(c, A, b, B)
print("Оптимальный план:", result)
