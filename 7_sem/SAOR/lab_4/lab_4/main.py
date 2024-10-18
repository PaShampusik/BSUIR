def knapsack(volumes, values, capacity):
    n = len(values)
    # Создаем таблицу для хранения максимальных ценностей
    dp = [[0 for _ in range(capacity + 1)] for _ in range(n + 1)]
    
    # Заполняем таблицу
    for i in range(1, n + 1):
        for v in range(capacity + 1):
            if volumes[i - 1] <= v:
                dp[i][v] = max(dp[i - 1][v], dp[i - 1][v - volumes[i - 1]] + values[i - 1])
            else:
                dp[i][v] = dp[i - 1][v]
    
    # Определяем, какие предметы были выбраны
    v = capacity
    selected_items = []
    for i in range(n, 0, -1):
        if dp[i][v] != dp[i - 1][v]:
            selected_items.append(i - 1)  # Предмет i-1 выбран
            v -= volumes[i - 1]

    return dp[n][capacity], selected_items

# Данные задачи
volumes = [10, 20, 30, 40]  
values = [60, 100, 120, 240] 
capacity = 50                

# Решение задачи
max_value, items_selected = knapsack(volumes, values, capacity)

# Вывод результатов
print("Максимальная ценность:", max_value)
print("Выбранные предметы (индексы):", items_selected)