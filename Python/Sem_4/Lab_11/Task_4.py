import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp


def shooting_method(f, y_a, y_b, y_prime_a, y_prime_b, h=0.01, eps=1e-6, max_iter=100):
    """
    Решает краевую задачу вида y''(x) = f(x, y(x)), y(a) = y_a, y(b) = y_b, y'(a) = y_prime_a, y'(b) = y_prime_b
    методом стрельбы.
    :param f: функция правой части дифференциального уравнения
    :param y_a: значение функции y(a)
    :param y_b: значение функции y(b)
    :param y_prime_a: значение производной функции y(a)
    :param y_prime_b: значение производной функции y(b)
    :param h: шаг сетки для численного решения задачи Коши
    :param eps: точность, с которой ищется решение
    :param max_iter: максимальное число итераций метода
    :return: массив значений функции y на сетке
    """
    # Находим начальное приближение для y'(a) методом секущих
    y_prime_0 = y_prime_a - (
        y_b
        - y_a
        - (y_prime_b - y_prime_a) * (y_prime_a - y_prime_a) / (y_prime_b - y_prime_a)
    ) / (y_prime_b - y_prime_a)

    # Решаем задачу Коши для начальных значений y(a), y'(a)
    def y_deriv(x, y):
        return np.array([y[1], f(x, y[0])])

    sol = solve_ivp(y_deriv, (a, b), (y_a, y_prime_0), t_eval=np.arange(a, b + h, h))

    # Ищем значение y на конце сетки
    y_end = sol.y[0, -1]

    # Основной цикл метода стрельбы
    iter_num = 0
    while abs(y_end - y_b) > eps and iter_num < max_iter:
        # Корректируем значение y'(a)
        y_prime_0 -= (y_end - y_b) / (y_prime_b - y_prime_a)

        # Решаем задачу Коши для новых начальных значений y(a), y'(a)
        sol = solve_ivp(
            y_deriv, (a, b), (y_a, y_prime_0), t_eval=np.arange(a, b + h, h)
        )

    # Ищем значение y на конце сетки
    y_end = sol.y[0, -1]

    # Обновляем значения y'(a) и y'(b)
    y_prime_a = y_prime_0
    y_prime_b = sol.y[1, -1]

    iter_num += 1

    # Проверяем, достигнута ли точность решения
    if abs(y_end - y_b) > eps:
        raise ValueError("Метод стрельбы не сошелся")

    # Возвращаем массив значений функции y на сетке
    return sol.y[0]


def f(x, y):
    return -y


# Задаем границы отрезка, на котором решается уравнение
a = 0
b = 1

# Задаем начальные значения y(a), y(b), y'(a), y'(b)
y_a = 1
y_b = np.exp(-1)
y_prime_a = 0
y_prime_b = -y_b

# Решаем краевую задачу методом стрельбы
y = shooting_method(f, y_a, y_b, y_prime_a, y_prime_b)

# Строим график
x = np.linspace(a, b, len(y))
plt.plot(x, y)
plt.xlabel("x")
plt.ylabel("y")
plt.title("График решения краевой задачи")
plt.show()
