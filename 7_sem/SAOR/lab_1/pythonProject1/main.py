import numpy as np
from scipy.optimize import linprog

def branch_and_bound(c, A, b, d_minus, d_plus):
    # Шаг 1: Преобразование задачи
    for i in range(len(c)):
        if c[i] > 0:
            c[i] *= -1
            A[:, i] *= -1
            d_minus[i], d_plus[i] = d_plus[i], d_minus[i]

    # Шаг 2: Приведение к канонической форме
    n = len(c)
    m = len(b)
    c = np.concatenate((c, np.zeros(2 * n + m)))
    A = np.block([[A, np.eye(n)], [np.zeros((m, 2 * n + m))]])
    b = np.concatenate((b, d_plus))

    # Инициализация переменных
    x_star = None
    r = -np.inf
    S = [(c, A, b, d_minus)]  # Стек задач

    while S:
        # Извлечение задачи из стека
        c, A, b, d_minus = S.pop()

        # Шаг 3: Решение задачи линейного программирования
        res = linprog(c, A_eq=A, b_eq=b, bounds=(None, None), method='highs')

        if res.success:
            x_e = res.x[:n]  # Оптимальный план
            if np.all(np.floor(x_e) == x_e):  # Проверка на целочисленность
                # Восстановление допустимого плана
                x_hat = x_e + d_minus
                if r < np.dot(c, x_hat):
                    x_star = x_hat
                    r = np.dot(c, x_hat)
            else:
                # Выбор дробной компоненты
                fractional_index = np.argmax(x_e - np.floor(x_e))
                floor_value = np.floor(x_e[fractional_index])
                ceil_value = np.ceil(x_e[fractional_index])

                # Создание двух новых задач
                b_new1 = b.copy()
                b_new1[m + fractional_index] = floor_value
                S.append((c, A, b_new1, d_minus))

                b_new2 = b.copy()
                b_new2[m + fractional_index] = ceil_value
                d_minus_new = d_minus.copy()
                d_minus_new[fractional_index] = 0
                S.append((c, A, b_new2, d_minus_new))

    # Шаг 4: Возврат результата
    if x_star is None:
        return "Задача несовместна"
    else:
        return x_star

# Пример использования
c = np.array([1, 1])  # Вектор коэффициентов
A = np.array([[5, 9], [9, 5]])  # Матрица ограничений
b = np.array([63, 63])  # Вектор правых частей
d_minus = np.array([1, 6])  # Нижние границы
d_plus = np.array([1, 6])  # Верхние границы

result = branch_and_bound(c, A, b, d_minus, d_plus)
print(result)
