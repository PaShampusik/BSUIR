#include <iostream>
#include <omp.h>
#include <vector>

void matrixVectorMultiplyBoosted(std::vector<std::vector<int>> matrix, std::vector<int> vector, std::vector<int>& result, int rows, int cols) {
#pragma omp parallel for 
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result[i] += matrix[i][j] * vector[j];
		}
	}
}

void matrixVectorMultiply(std::vector<std::vector<int>> matrix, std::vector<int> vector, std::vector<int>& result, int rows, int cols) {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result[i] += matrix[i][j] * vector[j];
		}
	}
}

int main() {
	const int rows = 6000;
	const int cols = 6000;

	std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = i * cols + j + 1;
		}
	}


	std::vector<int> numbers(rows);

	// Инициализация элементов вектора
	for (int i = 0; i < rows; i++) {
		numbers[i] = i + 1;
	}
	std::vector<int> result(rows);
	std::vector<int> result1(rows);

	double start_time = omp_get_wtime(); // Засекаем время начала выполнения

	matrixVectorMultiply(matrix, numbers, result, rows, cols);

	double end_time = omp_get_wtime(); // Засекаем время окончания выполнения

	double execution_time = end_time - start_time;

	double start_time1 = omp_get_wtime(); // Засекаем время начала выполнения

	matrixVectorMultiplyBoosted(matrix, numbers, result1, rows, cols);

	double end_time1 = omp_get_wtime(); // Засекаем время окончания выполнения

	double execution_time1 = end_time1 - start_time1;
	std::cout << "Execution time: " << execution_time << " seconds" << std::endl;
	std::cout << "Execution time of Boosted function: " << execution_time1 << " seconds" << std::endl;
	std::cout << "Boosted function is faster in " << execution_time / execution_time1 << " times" << std::endl;
	return 0;
}

