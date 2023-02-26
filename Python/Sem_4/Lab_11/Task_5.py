import numpy as np
import math
import scipy as sp
from scipy import sparse
import matplotlib.pyplot as plt

K = 30


def p(x: float) -> float:
    return 0.5 * math.sqrt(1 + x**2)


def q(x) -> float:
    return 5 * (1 + x**2)


def f(x) -> float:
    return 10 * math.e ** (-x)


def get_norm(values: list, step: float) -> float:
    # summ: float = 0.0
    #
    # for value in values:
    #     summ += value * value * step
    #
    # return math.sqrt(summ)
    return max(*values[0:-1])


def get_2_task_solution_with_number_of_subranges(
    n: int, Ua: float, Ub: float, interval: tuple
) -> tuple:
    step: float = (interval[1] - interval[0]) / n

    y_kprev = lambda x: 2 - p(x) * step
    y_k = lambda x: q(x) * 2 * step * step - 4
    y_knext = lambda x: 2 + p(x) * step

    b_k = lambda x: 2 * step * step * f(x)  # for free coefficients vector

    free_coefficients: list[float] = [Ua]
    main_coefficients: list[list[float]] = [[0] * (n + 1)]
    main_coefficients[0][0] = 1

    x_array: list[float] = [interval[0]]

    for k in range(1, n):
        new_row: list[float] = [0] * (n + 1)
        new_row[k - 1] = y_kprev(x_array[-1])
        x_array.append(x_array[-1] + step)
        new_row[k] = y_k(x_array[-1])
        new_row[k + 1] = y_knext(x_array[-1] + step)

        main_coefficients.append(new_row)
        free_coefficients.append(b_k(x_array[-1]))

    x_array.append(interval[1])

    main_coefficients.append([0] * (n + 1))
    main_coefficients[-1][-1] = 1
    free_coefficients.append(Ub)

    y_array: list[float] = list(np.linalg.solve(main_coefficients, free_coefficients))

    plt.plot(x_array, y_array, mew=2, ms=10)
    plt.show()

    return x_array, y_array, get_norm(y_array, step)


def get_2_task_solution(epsilon: float, Ua: float, Ub: float, interval: tuple) -> None:
    number_of_ranges: int = 3

    first_solution = get_2_task_solution_with_number_of_subranges(
        number_of_ranges, Ua, Ub, interval
    )
    print(number_of_ranges)

    number_of_ranges *= 2
    print(number_of_ranges)

    second_solution = get_2_task_solution_with_number_of_subranges(
        number_of_ranges, Ua, Ub, interval
    )
    print(abs(first_solution[2] - second_solution[2]))

    while abs(first_solution[2] - second_solution[2]) > epsilon:
        number_of_ranges *= 2
        first_solution = second_solution
        second_solution = get_2_task_solution_with_number_of_subranges(
            number_of_ranges, Ua, Ub, interval
        )
        print(number_of_ranges)
        print(abs(first_solution[2] - second_solution[2]))


def solve_task2() -> None:
    Ua, Ub = 0, 0
    interval: tuple[float, float] = (0, 2.5)
    epsilon: float = 0.2
    get_2_task_solution(epsilon, Ua, Ub, interval)


solve_task2()
