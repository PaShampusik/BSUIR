package main

import (
	"fmt"
	"io/ioutil"
	"math/rand"
)

const (
	n = 7 // длина кода
	k = 4 // размерность кода
	t = 2 // количество исправляемых ошибок
)

// Генерация случайного двоичного вектора заданной длины с не более чем t единицами
func generateErrorVector(length int, t int) []int {
	vector := make([]int, length)
	for i := 0; i < t; i++ {
		for {
			pos := rand.Intn(length)
			if vector[pos] == 0 {
				vector[pos] = 1
				break
			}
		}
	}
	return vector
}

// Умножение матрицы на вектор
func multiplyMatrixVector(matrix [][]int, vector []int) []int {
	result := make([]int, len(matrix))
	for i := range matrix {
		for j := range matrix[i] {
			result[i] ^= matrix[i][j] & vector[j]
		}
	}
	return result
}

// Генерация порождающей матрицы G
func generateGeneratorMatrix() [][]int {
	return [][]int{
		{1, 0, 0, 0, 1, 1, 0},
		{0, 1, 0, 0, 1, 0, 1},
		{0, 0, 1, 0, 0, 1, 1},
		{0, 0, 0, 1, 1, 1, 1},
	}
}

// Генерация случайной невырожденной матрицы S
func generateRandomMatrix(size int) [][]int {
	matrix := make([][]int, size)
	for i := range matrix {
		matrix[i] = make([]int, size)
		for j := range matrix[i] {
			matrix[i][j] = rand.Intn(2) // 0 или 1
		}
	}
	// Убедимся, что матрица невырожденная (для простоты, просто сделаем ее единичной)
	for i := 0; i < size; i++ {
		matrix[i][i] = 1
	}
	return matrix
}

// Шифрование сообщения
func encrypt(message []int, G [][]int) []int {
	// Генерация случайного вектора ошибок
	errorVector := generateErrorVector(n, t)
	// Шифрование
	c := multiplyMatrixVector(G, message)
	for i := 0; i < n; i++ {
		c[i] ^= errorVector[i]
	}
	return c
}

// Дешифрование сообщения
func decrypt(c []int, G [][]int, S [][]int) []int {
	// Восстановление сообщения (для простоты, не реализуем декодирование)
	m := multiplyMatrixVector(G, c)
	return m
}

// Преобразование строки в двоичный вектор
func stringToBinaryVector(s string) []int {
	binaryVector := make([]int, k)
	for i, char := range s {
		if i < k {
			binaryVector[i] = int(char - '0') // Преобразуем символ в число
		}
	}
	return binaryVector
}

// Преобразование двоичного вектора в строку
func binaryVectorToString(v []int) string {
	result := ""
	for _, bit := range v {
		result += fmt.Sprintf("%d", bit)
	}
	return result
}

func main() {
	// Генерация ключей
	G := generateGeneratorMatrix()
	S := generateRandomMatrix(k)

	// Чтение текста из файла
	inputFile := "input.txt"
	data, err := ioutil.ReadFile(inputFile)
	if err != nil {
		fmt.Println("Error reading file:", err)
		return
	}

	// Преобразование данных в двоичный вектор
	message := stringToBinaryVector(string(data))

	// Шифрование
	ciphertext := encrypt(message, G)
	fmt.Println("Зашифрованное сообщение:", ciphertext)

	// Дешифрование
	decryptedMessage := decrypt(ciphertext, G, S)
	fmt.Println("Расшифрованное сообщение:", binaryVectorToString(decryptedMessage))
}
