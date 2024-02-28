# ---
# jupyter:
#   jupytext:
#     cell_metadata_filter: -all
#     formats: ipynb,py:light
#     text_representation:
#       extension: .py
#       format_name: light
#       format_version: '1.5'
#       jupytext_version: 1.16.1
# ---

import csv
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import geom, binom, poisson, uniform, norm, expon

# Загрузка данных из файла
file1_data = []
with open("set_1.csv", "r") as file:
    reader = csv.reader(file)
    for row in reader:
        file1_data.append(row)

file2_data = []
with open("set_2.csv", "r") as file:
    reader = csv.reader(file)
    for row in reader:
        file2_data.append(row)

file3_data = []
with open("set_3.csv", "r") as file:
    reader = csv.reader(file)
    for row in reader:
        file3_data.append(row)

data = np.array(file1_data).flatten().astype(int)

# гистограмма
plt.xlim(0, 19)
plt.hist(data, bins="auto", color="blue", alpha=0.7, rwidth=0.85)
plt.grid(axis="y", alpha=0.75)
plt.xlabel("Значение")
plt.ylabel("Частота")
plt.title("Гистограмма данных из файла set_1.csv")
plt.show(block=True)

# Параметр p - вероятность успеха
p = 0.5

# Расчет математического ожидания и дисперсии
mean = np.mean(data)
variance = np.var(data)

# Создание массива значений для x
x = np.arange(0, np.max(data) + 1)

# Геометрическое распределение
geom_pmf = geom.pmf(x, 1 / mean)

plt.xlim(0, 19)
plt.plot(x, geom_pmf, "r", label="Геометрическое распределение")
plt.grid(axis="y", alpha=0.75)
plt.xlabel("Значение")
plt.ylabel("Вероятность")
plt.title("Теоретические распределения")
plt.legend()
plt.xticks(np.arange(0, 20, 1))
plt.show(block=True)

# Биномиальное распределение
binom_pmf = binom.pmf(x, len(data), 1 / mean)

plt.xlim(0, 60)
plt.plot(x, binom_pmf, "r", label="Биномиальное распределение")
plt.grid(axis="y", alpha=0.75)
plt.xlabel("Значение")
plt.ylabel("Вероятность")
plt.title("Теоретические распределения")
plt.legend()
plt.xticks(np.arange(0, 60, 1))
plt.show(block=True)

# Пуассоновское распределение
poisson_pmf = poisson.pmf(x, mean)

plt.xlim(-1, 12)
plt.plot(x, poisson_pmf, "r", label="Пуассоново распределение")
plt.grid(axis="y", alpha=0.75)
plt.xlabel("Значение")
plt.ylabel("Вероятность")
plt.title("Теоретические распределения")
plt.legend()
plt.xticks(np.arange(-1, 12, 1))
plt.show(block=True)

# Равномерное распределение
uniform_pdf = uniform.pdf(x, np.min(data), np.max(data))

plt.xlim(-1, 4)
plt.plot(x, uniform_pdf, "r", label="Равномерное распределение")
plt.grid(axis="y", alpha=0.75)
plt.xlabel("Значение")
plt.ylabel("Вероятность")
plt.title("Теоретические распределения")
plt.legend()
plt.xticks(np.arange(-1, 4, 1))
plt.show(block=True)

# Нормальное распределение
norm_pdf = norm.pdf(x, mean, np.sqrt(variance))

plt.xlim(-1, 14)
plt.plot(x, norm_pdf, "r", label="Нормальное распределение")
plt.grid(axis="y", alpha=0.75)
plt.xlabel("Значение")
plt.ylabel("Вероятность")
plt.title("Теоретические распределения")
plt.legend()
plt.xticks(np.arange(-1, 14, 1))
plt.show(block=True)

# Экспоненциальное распределение
expon_pdf = expon.pdf(x, scale=1 / mean)

plt.xlim(-1, 3)
plt.plot(x, expon_pdf, "r", label="Экспоненциальное распределение")
plt.grid(axis="y", alpha=0.75)
plt.xlabel("Значение")
plt.ylabel("Вероятность")
plt.title("Теоретические распределения")
plt.legend()
plt.xticks(np.arange(-1, 3, 1))
plt.show(block=True)
