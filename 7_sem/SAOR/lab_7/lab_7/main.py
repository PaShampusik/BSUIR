import numpy as np


def hungarian_algorithm(cost_matrix):
    # Преобразуем матрицу стоимости в numpy массив
    cost_matrix = np.array(cost_matrix)

    # Количество строк и столбцов
    n, m = cost_matrix.shape

    # Добавляем дополнительные строки и столбцы, если необходимо
    if n < m:
        cost_matrix = np.pad(cost_matrix, ((0, m - n), (0, 0)), mode='constant', constant_values=0)
    elif m < n:
        cost_matrix = np.pad(cost_matrix, ((0, 0), (0, n - m)), mode='constant', constant_values=0)

    # Количество строк и столбцов после дополнения
    n, m = cost_matrix.shape

    # Инициализация
    u = np.zeros(n)
    v = np.zeros(m)
    p = np.zeros(m, dtype=int) - 1
    way = np.zeros(m, dtype=int)

    for i in range(n):
        links = np.zeros(m, dtype=int) - 1
        mins = np.full(m, np.inf)
        visited = np.zeros(m, dtype=bool)
        marked_i = i
        marked_j = -1
        j0 = 0

        while True:
            visited[j0] = True
            i0 = marked_i
            delta = np.inf
            j1 = -1

            for j in range(m):
                if not visited[j]:
                    cur = cost_matrix[i0, j] - u[i0] - v[j]
                    if cur < mins[j]:
                        mins[j] = cur
                        links[j] = j0
                    if mins[j] < delta:
                        delta = mins[j]
                        j1 = j

            for j in range(m):
                if visited[j]:
                    u[p[j]] += delta
                    v[j] -= delta
                else:
                    mins[j] -= delta

            marked_j = j1
            marked_i = p[j1]
            j0 = marked_j

            if marked_i == -1:
                break

        while True:
            if links[j0] == -1:
                break
            p[j0] = p[links[j0]]
            j0 = links[j0]

    # Формируем результат
    result = []
    for j in range(m):
        if p[j] != -1:
            result.append((p[j], j))

    return result, u, v


# Пример использования
cost_matrix = [
    [4, 2, 8],
    [2, 4, 6],
    [8, 6, 4]
]

assignments, u, v = hungarian_algorithm(cost_matrix)
print("Оптимальные назначения:", assignments)
