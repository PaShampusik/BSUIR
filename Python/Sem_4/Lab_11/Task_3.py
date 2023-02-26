import numpy as np
import math
import scipy as sp
from scipy import sparse
import matplotlib.pyplot as plt


INTERVAL: tuple = (0.2, 0.5)


def get_norm(values: list, step: float) -> float:
    summ: float = 0.0

    for value in values:
        summ += value * value * step

    return math.sqrt(summ)
    return max(*values[0:-1])


# initial conditions are "hardcoded" in this solution below:
def get_3_task_solution_with_number_of_subranges(n: int) -> tuple:
    step: float = (INTERVAL[1] - INTERVAL[0]) / n

    y_kprev = lambda x: 1 + x * step
    y_k = lambda x: -2 / x * step * step - 4
    y_knext = lambda x: 1 - x * step

    b_k = lambda x: 3 * 2 * step * step  # for free coefficients vector

    # coefficients matrices with first initial condition already
    free_coefficients: list[float] = [4 * step]
    main_coefficients: list[list[float]] = [[0] * (n + 1)]
    main_coefficients[0][0] = 2 * step + 1.5
    main_coefficients[0][1] = -2
    main_coefficients[0][2] = -1

    x_array: list[float] = [INTERVAL[0]]

    for k in range(1, n):
        new_row: list[float] = [0] * (n + 1)
        new_row[k - 1] = y_kprev(x_array[-1])
        x_array.append(x_array[-1] + step)
        new_row[k] = y_k(x_array[-1])
        new_row[k + 1] = y_knext(x_array[-1] + step)

        main_coefficients.append(new_row)
        free_coefficients.append(b_k(x_array[-1]))

    x_array.append(INTERVAL[1])

    main_coefficients.append([0] * (n + 1))
    main_coefficients[-1][-1] = 1
    free_coefficients.append(1)

    y_array: list[float] = list(np.linalg.solve(main_coefficients, free_coefficients))

    plt.plot(x_array, y_array, mew=2, ms=10)
    plt.show()

    return x_array, y_array, get_norm(y_array, step)


def get_3_task_solution(epsilon: float) -> None:
    number_of_ranges: int = 3

    first_solution = get_3_task_solution_with_number_of_subranges(number_of_ranges)
    print(number_of_ranges)

    number_of_ranges *= 2
    print(number_of_ranges)

    second_solution = get_3_task_solution_with_number_of_subranges(number_of_ranges)
    print(abs(first_solution[2] - second_solution[2]))

    while abs(first_solution[2] - second_solution[2]) > epsilon:
        number_of_ranges *= 2
        first_solution = second_solution
        second_solution = get_3_task_solution_with_number_of_subranges(number_of_ranges)
        print(number_of_ranges)
        print(abs(first_solution[2] - second_solution[2]))


def solve_task3() -> None:
    epsilon: float = 0.0
    get_3_task_solution(epsilon)


solve_task3()
