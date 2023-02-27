# import numpy as np
# import math
# import scipy as sp
# from scipy import sparse
# import matplotlib.pyplot as plt


# INTERVAL: tuple = (0.2, 0.5)


# def get_norm(values: list, step: float) -> float:
#     summ: float = 0.0

#     for value in values:
#         summ += value * value * step

#     return math.sqrt(summ)
#     return max(*values[0:-1])


# # initial conditions are "hardcoded" in this solution below:
# def get_3_task_solution_with_number_of_subranges(n: int) -> tuple:
#     step: float = (INTERVAL[1] - INTERVAL[0]) / n

#     y_kprev = lambda x: 1 + x * step
#     y_k = lambda x: -2 / x * step * step - 4
#     y_knext = lambda x: 1 - x * step

#     b_k = lambda x: 3 * 2 * step * step  # for free coefficients vector

#     # coefficients matrices with first initial condition already
#     free_coefficients: list[float] = [4 * step]
#     main_coefficients: list[list[float]] = [[0] * (n + 1)]
#     main_coefficients[0][0] = 2 * step + 1.5
#     main_coefficients[0][1] = -2
#     main_coefficients[0][2] = -1

#     x_array: list[float] = [INTERVAL[0]]

#     for k in range(1, n):
#         new_row: list[float] = [0] * (n + 1)
#         new_row[k - 1] = y_kprev(x_array[-1])
#         x_array.append(x_array[-1] + step)
#         new_row[k] = y_k(x_array[-1])
#         new_row[k + 1] = y_knext(x_array[-1] + step)

#         main_coefficients.append(new_row)
#         free_coefficients.append(b_k(x_array[-1]))

#     x_array.append(INTERVAL[1])

#     main_coefficients.append([0] * (n + 1))
#     main_coefficients[-1][-1] = 1
#     free_coefficients.append(1)

#     y_array: list[float] = list(np.linalg.solve(main_coefficients, free_coefficients))

#     plt.plot(x_array, y_array, mew=2, ms=10)
#     plt.show()

#     return x_array, y_array, get_norm(y_array, step)


# def get_3_task_solution(epsilon: float) -> None:
#     number_of_ranges: int = 3

#     first_solution = get_3_task_solution_with_number_of_subranges(number_of_ranges)
#     print(number_of_ranges)

#     number_of_ranges *= 2
#     print(number_of_ranges)

#     second_solution = get_3_task_solution_with_number_of_subranges(number_of_ranges)
#     print(abs(first_solution[2] - second_solution[2]))

#     while abs(first_solution[2] - second_solution[2]) > epsilon:
#         number_of_ranges *= 2
#         first_solution = second_solution
#         second_solution = get_3_task_solution_with_number_of_subranges(number_of_ranges)
#         print(number_of_ranges)
#         print(abs(first_solution[2] - second_solution[2]))


# def solve_task3() -> None:
#     epsilon: float = 0.0
#     get_3_task_solution(epsilon)


# solve_task3()


from abc import abstractmethod
from math import *

import matplotlib.pyplot as plt
import numpy as np


class Metrics:
    @staticmethod
    def l_1_norm(first_vector, second_vector):
        return np.sum(np.abs(first_vector - second_vector))

    @staticmethod
    def l_2_norm(first_vector, second_vector):
        return np.sum((first_vector - second_vector) ** 2)

    @staticmethod
    def l_infinity_norm(first_vector, second_vector):
        return np.max(np.abs(first_vector - second_vector))


def solve_tridigional_matrix(
    upper_diagonal, middle_diagonal, lower_diagonal, result_vector
):
    c_prime = np.zeros(middle_diagonal.size - 1)
    d_prime = np.zeros(middle_diagonal.size)

    c_prime[0] = upper_diagonal[0] / middle_diagonal[0]
    for i in range(1, middle_diagonal.size - 1):
        c_prime[i] = upper_diagonal[i] / (
            middle_diagonal[i] - lower_diagonal[i - 1] * c_prime[i - 1]
        )

    d_prime[0] = result_vector[0] / middle_diagonal[0]
    for i in range(1, middle_diagonal.size):
        d_prime[i] = (result_vector[i] - lower_diagonal[i - 1] * d_prime[i - 1]) / (
            middle_diagonal[i] - lower_diagonal[i - 1] * c_prime[i - 1]
        )

    solution = np.zeros(middle_diagonal.size)
    solution[-1] = d_prime[-1]

    for i in reversed(range(middle_diagonal.size - 1)):
        solution[i] = d_prime[i] - c_prime[i] * solution[i + 1]
    return solution


class AbstractDifferenceSchemeSolver:
    def __init__(
        self,
        p_function,
        q_function,
        f_function,
        left_bound,
        right_bound,
        h=0.1,
        amount_points=None,
        left_condition=None,
        right_condition=None,
    ):
        self.p = p_function
        self.q = q_function
        self.f = f_function

        self.left_condition = left_condition
        self.right_condition = right_condition

        self.left_bound = left_bound
        self.right_bound = right_bound

        if (
            amount_points is not None
            and left_condition is not None
            and right_condition is not None
        ):
            self.set_h((right_bound - left_bound) / (amount_points - 1))
        elif h is not None:
            self.set_h(h)
        else:
            raise ValueError

    def set_h(self, new_h):
        self.h = new_h
        self.x_points = np.arange(self.left_bound, self.right_bound + self.h, self.h)
        self.y_points = None

    @abstractmethod
    def _get_difference_scheme_vectors(self):
        raise NotImplemented

    def get_accuracy(self, metrics):
        if self.y_points is None:
            raise ValueError
        double_h_solver = self.__class__(
            self.p,
            self.q,
            self.f,
            self.left_bound,
            self.right_bound,
            h=self.h * 2.0,
            left_condition=self.left_condition,
            right_condition=self.right_condition,
        )
        double_h_solver.solve()
        return metrics(
            self.y_points[::2],
            double_h_solver.y_points
            if self.y_points.size % 2 == 1
            else double_h_solver.y_points[:-1],
        ) / (2**self._order - 1)

    def get_solution_according_accuracy(
        self, metrics=Metrics.l_infinity_norm, eps=0.001, step=0.001
    ):
        current_accuracy = self.get_accuracy(metrics)
        while current_accuracy >= eps:
            self.set_h(self.h - step)
            self.solve()
            current_accuracy = self.get_accuracy(metrics)
        return self.h, current_accuracy

    def solve(self):
        self.y_points = solve_tridigional_matrix(*self._get_difference_scheme_vectors())

    def plot_solution(self, mode="smooth"):
        if mode == "smooth":
            plt.plot(self.x_points, self.y_points)
        elif mode == "scatter":
            plt.scatter(self.x_points, self.y_points, facecolors="none", edgecolors="r")


class SecondOrderSchemeSolver(AbstractDifferenceSchemeSolver):
    def __init__(
        self,
        p_function,
        q_function,
        f_function,
        left_bound,
        right_bound,
        h=0.1,
        amount_points=None,
        left_condition=None,
        right_condition=None,
    ):
        super().__init__(
            p_function,
            q_function,
            f_function,
            left_bound,
            right_bound,
            h=h,
            amount_points=amount_points,
            left_condition=left_condition,
            right_condition=right_condition,
        )
        self._order = 2

    def _get_difference_scheme_vectors(self):
        diagonal = np.ones(self.x_points.size)
        upper_diagonal = np.zeros(self.x_points.size - 1)
        lower_diagonal = np.zeros(self.x_points.size - 1)

        diagonal[1:-1] = np.vectorize(lambda x: (self.h**2) * self.q(x) - 2)(
            self.x_points[1:-1]
        )
        upper_diagonal[1:] = np.vectorize(lambda x: 1 + self.h * self.p(x) / 2.0)(
            self.x_points[1:-1]
        )
        lower_diagonal[:-1] = np.vectorize(lambda x: 1 - self.h * self.p(x) / 2.0)(
            self.x_points[1:-1]
        )

        result = (self.h**2) * np.vectorize(self.f)(self.x_points)
        result[0] = (
            self.left_condition(self.h)
            if callable(self.left_condition)
            else self.left_condition
        )
        result[-1] = (
            self.right_condition(self.h)
            if callable(self.right_condition)
            else self.right_condition
        )

        return upper_diagonal, diagonal, lower_diagonal, result


class SecondOrderSchemeSolverBoundaryConditions(SecondOrderSchemeSolver):
    def __init__(
        self,
        p_function,
        q_function,
        f_function,
        left_bound,
        right_bound,
        h=0.1,
        amount_points=None,
        left_condition=None,
        right_condition=None,
    ):
        super().__init__(
            p_function,
            q_function,
            f_function,
            left_bound,
            right_bound,
            h=h,
            amount_points=amount_points,
            left_condition=left_condition[0],
            right_condition=right_condition[0],
        )
        self.left_condition_function = left_condition[1]
        self.left_condition_derivative_function = left_condition[2]

        self.right_condition_function = right_condition[1]
        self.right_condition_derivative_function = right_condition[2]

    def get_accuracy(self, metrics):
        if self.y_points is None:
            raise ValueError
        left_condition = (
            self.left_condition,
            self.left_condition_function,
            self.left_condition_derivative_function,
        )
        right_condition = (
            self.right_condition,
            self.right_condition_function,
            self.right_condition_derivative_function,
        )

        double_h_solver = self.__class__(
            self.p,
            self.q,
            self.f,
            self.left_bound,
            self.right_bound,
            h=self.h * 2.0,
            left_condition=left_condition,
            right_condition=right_condition,
        )
        double_h_solver.solve()
        return metrics(
            self.y_points[::2],
            double_h_solver.y_points
            if self.y_points.size % 2 == 1
            else double_h_solver.y_points[:-1],
        ) / (2**self._order - 1)

    def _get_difference_scheme_vectors(self):
        (
            upper_diagonal,
            diagonal,
            lower_diagonal,
            result,
        ) = super()._get_difference_scheme_vectors()

        diagonal[0] = (
            (-3 / 2.0 + lower_diagonal[0] / (2 * upper_diagonal[1]))
            * self.left_condition_derivative_function
            + self.left_condition_function * self.h
        )
        upper_diagonal[0] = (
            2 + diagonal[1] / (2 * upper_diagonal[1])
        ) * self.left_condition_derivative_function
        result[0] += (
            result[1]
            * self.left_condition_derivative_function
            / (2 * upper_diagonal[1])
        )

        lower_diagonal[-1] = (
            -2 - diagonal[-2] / (2.0 * lower_diagonal[-2])
        ) * self.right_condition_derivative_function
        diagonal[-1] = (
            (3 / 2 - upper_diagonal[-1] / (2.0 * lower_diagonal[-2]))
            * self.right_condition_derivative_function
            + self.right_condition_function * self.h
        )
        result[-1] -= (
            result[-2] / (2.0 * lower_diagonal[-2])
        ) * self.right_condition_derivative_function

        return upper_diagonal, diagonal, lower_diagonal, result


def p(x):
    return 2


def q(x):
    return -1 / x


def f(x):
    return 3


left_bound = 0.2
right_bound = 0.5

left_condition = (lambda h: 2 * h, 1, 0)
right_condition = (lambda h: 1 * h, 0.5, -1)
eps = 0.001

solver = SecondOrderSchemeSolverBoundaryConditions(
    p,
    q,
    f,
    left_bound,
    right_bound,
    h=0.01,
    left_condition=left_condition,
    right_condition=right_condition,
)
solver.solve()
h, error = solver.get_solution_according_accuracy(Metrics.l_infinity_norm, eps=eps)
print(
    f"Шаг, при котором достигается точность порядка {eps}, равен {h=}, при этом ошибка"
    f" равна {error=}"
)

plt.title(
    f"Результат решения уравнения \n методом конечных разностей с точностью {eps}"
)
plt.xlabel("x")
plt.ylabel("y")
solver.plot_solution(mode="smooth")
plt.show()
