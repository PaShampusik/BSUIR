import matplotlib.pyplot as plt
import numpy as np
from scipy.integrate import solve_ivp


def shooting_method(f, a, b, alpha, beta, tol=1e-6, max_iter=100):
    """
    Решает краевую задачу методом стрельбы.

    Аргументы:
        f: функция, описывающая дифференциальное уравнение второго порядка y'' = f(x, y, y'),
           где x - независимая переменная, y - зависимая переменная.
        a, b: левый и правый концы отрезка, на котором задана краевая задача.
        alpha, beta: граничные условия в точках x=a и x=b соответственно, например,
                     alpha = [y(a), y'(a)] и beta = [y(b), y'(b)].
        tol: допустимая точность решения.
        max_iter: максимальное число итераций.

    Возвращает:
        Массив x значений независимой переменной.
        Массив y значений зависимой переменной.
    """

    def f_system(x, y):
        """
        Переводит дифференциальное уравнение второго порядка в систему двух уравнений первого порядка.
        y = [y_1, y_2], где y_1=y, y_2=y'.
        """
        y1, y2 = y
        return [y2, f(x, y1, y2)]

    def residual(guess):
        """
        Вычисляет отклонение решения от граничных условий на правом конце отрезка.
        guess - начальное значение производной на левом конце.
        """
        y_a = alpha
        y_b = solve_ivp(f_system, (a, b), [0, guess], rtol=tol, atol=tol).y[:, -1]
        return y_b - beta

    # Находим начальное значение производной на левом конце, которое удовлетворяет граничным условиям.
    guess = 0.0
    guess_low = -1.0
    guess_high = 1.0
    for i in range(max_iter):
        y_b = solve_ivp(f_system, (a, b), [0, guess], rtol=tol, atol=tol).y[:, -1]
        res = residual(guess)
        if np.abs(res[0]) < tol:
            break
        elif res[0] > 0:
            guess_high = guess
            guess = 0.5 * (guess_low + guess)
        else:
            guess_low = guess
            guess = 0.5 * (guess + guess_high)

    # Решаем дифференциальное уравнение с найденным начальным значением производной на левом конце.
    sol = solve_ivp(f_system, (a, b), [0, guess], rtol=tol, atol=tol)

    return sol.t, sol.y[0]


def f(x, y, yp):
    return [yp, y / x + 3 - 2 * yp]


a, b = 0.2, 0.5
alpha = [0.2, 2]
beta = [0.5, 1]

x, y = shooting_method(f, a, b, alpha, beta, tol=1e-3)

plt.plot(x, y[0])
plt.xlabel("x")
plt.ylabel("y")
plt.title("Solution of y\" + 2*y' - y/x = 3")
plt.show()
