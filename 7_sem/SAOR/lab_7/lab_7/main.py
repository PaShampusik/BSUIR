import numpy as np
from methods import hungarian_algorithm

if __name__ == "__main__":
    C = np.array([
        [7, 2, 1, 9, 4],
        [9, 6, 9, 5, 5],
        [3, 8, 3, 1, 8],
        [7, 9, 4, 2, 2],
        [8, 4, 7, 4, 8]
    ])

    positions = hungarian_algorithm(C)
    print(C, "\n", positions)