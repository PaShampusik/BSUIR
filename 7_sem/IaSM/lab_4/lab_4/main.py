import random
import numpy as np
from collections import deque

from matplotlib import pyplot as plt

# Параметры СМО
n = 6  # Количество каналов
lambd = 3  # Интенсивность поступления заявок
mu = 1  # Интенсивность обслуживания одним каналом
T = 100  # Время моделирования

# Вспомогательные функции
def exponential(rate):
    return random.expovariate(rate)

def poisson(rate, time):
    return np.random.poisson(rate * time)

# Класс для имитации СМО
class QueueingSystem:
    def __init__(self, n, lambd, mu):
        self.n = n
        self.lambd = lambd
        self.mu = mu
        self.queue = deque()
        self.active_channels = [0] * n
        self.total_time = 0
        self.total_customers = 0
        self.states = []
        self.total_work_time = 0
        self.total_waiting_time = 0

    def run(self, T):
        t = 0
        while t < T:
            # Генерация новых заявок
            new_customers = poisson(self.lambd, 1)
            self.queue.extend([t + exponential(self.lambd)] for _ in range(new_customers))
            self.total_customers += new_customers
            print(f"Новые заявки: {new_customers}")

            # Обслуживание заявок
            for i in range(self.n):
                if self.active_channels[i] > 0:
                    self.active_channels[i] -= 1
                    self.total_work_time += 1
                    if self.active_channels[i] <= 0:
                        if self.queue:
                            wait_time = t - self.queue[0][0]
                            if(wait_time > 1):
                                self.total_waiting_time += wait_time
                            self.active_channels[i] = exponential(self.mu)
                            self.queue.popleft()
                            print(f"Заявка из очереди обслужена в канале {i}")
                        else:
                            self.active_channels[i] = 0

            # Распределение заявок из очереди по каналам
            while self.queue and any(c == 0 for c in self.active_channels):
                for i in range(self.n):
                    if self.active_channels[i] == 0:
                        self.active_channels[i] = exponential(self.mu)
                        self.queue.popleft()
                        print(f"Заявка из очереди распределена в канал {i}")
                        break

            # Обновление времени
            t += 1
            self.total_time += 1
            self.states.append(max(0, sum(self.active_channels)))
            print(f"Текущее время: {t}")
            print(f"Активные каналы: {self.active_channels}")
            print(f"Очередь: {self.queue}")

        # Вычисление финальных вероятностей состояний
        probs = np.bincount(self.states, minlength=self.n + 1) / self.total_time

        # Вычисление характеристик эффективности
        mean_customers = self.total_customers / self.total_time
        mean_time = self.total_waiting_time / max(1, self.total_customers)
        utilization = self.total_work_time / (self.n * self.total_time)

        return probs, mean_customers, mean_time, utilization

# Запуск симуляции
queueing_system = QueueingSystem(n, lambd, mu)
probs, mean_customers, mean_time, utilization = queueing_system.run(T)
# Вывод результатов
print("Финальные вероятности состояний:")
for i, p in enumerate(probs):
    print(f"P{i} = {p:.4f}")
print(f"\nСредняя длина очереди: {mean_customers:.2f}")
print(f"Среднее время ожидания: {mean_time:.2f}")
print(f"Коэффициент загрузки: {utilization:.2f}")
# Построение графа состояний
states = np.arange(len(probs))
plt.figure(figsize=(10, 6))
plt.bar(states, probs)
plt.xlabel("Состояние")
plt.ylabel("Вероятность")
plt.title("Граф финальных вероятностей состояний")
plt.show()