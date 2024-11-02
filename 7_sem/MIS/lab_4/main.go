package main

import (
	"fmt"
	"math/rand"
	"time"
)

// Функция для генерации порождающей матрицы G
func generateGeneratorMatrix(k, n int) [][]int {
	G := make([][]int, k)
	for i := range G {
		G[i] = make([]int, n)
		for j := range G[i] {
			G[i][j] = rand.Intn(2) // Заполнение случайными 0 и 1
		}
	}
	return G
}

// Функция для проверки невырожденности матрицы
func isInvertible(matrix [][]int) bool {
	// Здесь можно реализовать проверку на невырожденность
	// Для простоты, будем считать, что матрица всегда невырождена
	return true
}

// Функция для генерации невырожденной матрицы S
func generateInvertibleMatrix(k int) [][]int {
	var S [][]int
	for {
		S = make([][]int, k)
		for i := range S {
			S[i] = make([]int, k)
			for j := range S[i] {
				S[i][j] = rand.Intn(2) // Заполнение случайными 0 и 1
			}
		}
		if isInvertible(S) {
			break
		}
	}
	return S
}

// Функция для генерации подстановочной матрицы P
func generatePermutationMatrix(n int) [][]int {
	P := make([][]int, n)
	for i := range P {
		P[i] = make([]int, n)
		for j := range P[i] {
			if i == j {
				P[i][j] = 1
			} else {
				P[i][j] = 0
			}
		}
	}
	// Перемешивание строк
	for i := range P {
		j := rand.Intn(n)
		P[i], P[j] = P[j], P[i]
	}
	return P
}

// Функция для умножения матриц
func multiplyMatrices(A, B [][]int) [][]int {
	rowsA := len(A)
	colsA := len(A[0])
	colsB := len(B[0])
	result := make([][]int, rowsA)
	for i := range result {
		result[i] = make([]int, colsB)
		for j := 0; j < colsB; j++ {
			for k := 0; k < colsA; k++ {
				result[i][j] = (result[i][j] + A[i][k]*B[k][j]) % 2 // Умножение по модулю 2
			}
		}
	}
	return result
}

// Функция для представления сообщения в виде двоичного вектора
func messageToBinaryVector(message string, k int) []int {
	binaryVector := make([]int, k)
	for i := 0; i < k; i++ {
		if i < len(message) {
			binaryVector[i] = int(message[i] - '0') // Преобразуем символ в бинарный вектор
		} else {
			binaryVector[i] = 0 // Заполняем нулями, если сообщение короче
		}
	}
	return binaryVector
}

// Функция для умножения матрицы на вектор
func multiplyMatrixByVector(matrix [][]int, vector []int) []int {
	rows := len(matrix)
	cols := len(matrix[0])
	result := make([]int, cols)
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			result[j] = (result[j] + matrix[i][j]*vector[i]) % 2 // Умножение по модулю 2
		}
	}
	return result
}

// Функция для умножения вектора на матрицу
func multiplyVectorByMatrix(vector []int, matrix [][]int) []int {
	// Проверяем, что размер вектора соответствует количеству строк в матрице
	if len(vector) != len(matrix) {
		vector = vector[:len(matrix)]
	}

	// Результирующий вектор
	result := make([]int, len(matrix[0]))

	// Умножаем вектор на матрицу
	for i := 0; i < len(matrix); i++ {
		for j := 0; j < len(matrix[i]); j++ {
			if vector[i] == 1 {
				result[j] ^= matrix[i][j]
			}
		}
	}

	return result
}

// Функция для генерации случайного бинарного вектора ошибок
func generateErrorVector(n, t int) []int {
	Z := make([]int, n)
	indices := rand.Perm(n)[:t] // Получаем случайные индексы для t единиц
	for _, index := range indices {
		Z[index] = 1
	}
	return Z
}

func Transpose(matrix [][]int) [][]int {
	if len(matrix) == 0 {
		return nil
	}

	// Создаем новую матрицу с размерами, поменянными местами
	transposed := make([][]int, len(matrix[0]))
	for i := range transposed {
		transposed[i] = make([]int, len(matrix))
	}

	// Заполняем транспонированную матрицу
	for i := range matrix {
		for j := range matrix[i] {
			transposed[j][i] = matrix[i][j]
		}
	}

	return transposed
}

// Находит обратную матрицу для данной двоичной невырожденной матрицы
func findInverseMatrixBinary(matrix [][]int) ([][]int, error) {
	n := len(matrix)

	// Проверяем, что матрица является квадратной
	for _, row := range matrix {
		if len(row) != n {
			return nil, fmt.Errorf("Матрица должна быть квадратной")
		}
	}

	// Создаём единичную матрицу
	identity := make([][]int, n)
	for i := range identity {
		identity[i] = make([]int, n)
		identity[i][i] = 1
	}

	// Расширенная матрица
	augmented := make([][]int, n)
	for i := range augmented {
		augmented[i] = make([]int, 2*n)
		copy(augmented[i], matrix[i])
		copy(augmented[i][n:], identity[i])
	}

	// Приводим расширенную матрицу к ступенчатому виду
	for i := 0; i < n; i++ {
		// Находим первый ненулевой элемент в i-ой строке
		pivotRow := i
		for j := i; j < n; j++ {
			if augmented[j][i] == 1 {
				pivotRow = j
				break
			}
		}

		// Меняем i-ую строку на pivotRow
		augmented[i], augmented[pivotRow] = augmented[pivotRow], augmented[i]

		// Делаем первый ненулевой элемент в i-ой строке равным 1
		for j := i + 1; j < 2*n; j++ {
			augmented[i][j] ^= 1
		}

		// Обнуляем остальные элементы в i-ом столбце
		for j := 0; j < n; j++ {
			if j != i && augmented[j][i] == 1 {
				for k := 0; k < 2*n; k++ {
					augmented[j][k] ^= augmented[i][k]
				}
			}
		}
	}

	// Правая часть расширенной матрицы содержит обратную матрицу
	inverse := make([][]int, n)
	for i := 0; i < n; i++ {
		inverse[i] = make([]int, n)
		copy(inverse[i], augmented[i][n:])
	}

	return inverse, nil
}

func main() {
	rand.Seed(time.Now().UnixNano())

	// Параметры системы
	k := 4  // Пример значения
	n := 12 // Пример значения
	t := 2  // Пример значения
	print(n)

	// Шаг 1: Генерация порождающей матрицы G
	//G := generateGeneratorMatrix(k, n)
	//fmt.Println("Порождающая матрица G:")
	//for _, row := range G {
	//	fmt.Println(row)
	//}
	G := [][]int{
		{0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0},
		{0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0},
		{1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0},
	}

	// Шаг 2: Генерация невырожденной матрицы S
	//S := generateInvertibleMatrix(k)
	//fmt.Println("Невырожденная матрица S:")
	//for _, row := range S {
	//	fmt.Println(row)
	//}
	S := [][]int{
		{1, 0, 0, 1},
		{0, 1, 0, 1},
		{0, 1, 0, 0},
		{0, 0, 1, 1},
	}

	// Шаг 3: Генерация подстановочной матрицы P
	//P := generatePermutationMatrix(n)
	//fmt.Println("Подстановочная матрица P:")
	//for _, row := range P {
	//	fmt.Println(row)
	//}
	P := [][]int{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
	}

	// Шаг 4: Вычисление G1 = S * G * P
	GG_new := multiplyMatrices(S, G)
	GG := multiplyMatrices(GG_new, P)
	fmt.Println("Открытый ключ G1:")
	for _, row := range GG {
		fmt.Println(row)
	}

	// Открытый ключ (G1, t) и секретный ключ (S, G, P)
	fmt.Println("Открытый ключ: (GG, t) =", GG, t)
	fmt.Println("Секретный ключ: (S, G, P) =", S, G, P)

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	message := "1010" // Двоичное сообщение длиной k/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Шаг 1: Представить M в виде двоичного вектора длины k
	M := messageToBinaryVector(message, k)
	fmt.Println("Сообщение M в двоичном векторе:", M)

	// Шаг 2: Выбрать случайный бинарный вектор ошибок Z длиной n
	Z := generateErrorVector(n, t)
	fmt.Println("Случайный бинарный вектор ошибок Z:", Z)
	// Шаг 4: Вычислить бинарный вектор C = M · G_A + Z
	C := multiplyVectorByMatrix(M, GG)

	for i := 0; i < len(C); i++ {
		C[i] = (C[i] + Z[i]) % 2 // Сложение по модулю 2
	}

	fmt.Println("Зашифрованный вектор C:", C)

	P_1 := Transpose(P)

	S_1 := Transpose(S)

	fmt.Println("обратная к S_1:")
	for _, row := range S_1 {
		fmt.Println(row)
	}

	C_1 := multiplyVectorByMatrix(C, P_1)
	fmt.Println("C_1 vector:")
	fmt.Println(C_1)
	Y := multiplyVectorByMatrix(Z, P_1)
	fmt.Println("error vector after P_1:")
	fmt.Println(Y)
	for i := 0; i < len(C_1); i++ {
		C_1[i] = (Y[i] + C_1[i]) % 2
	}
	fmt.Println("C_1 vector after sum with Y:")
	fmt.Println(C_1)

	fmt.Println("G_pseudo:")
	G_pseudo := findPseudoinverse(G)

	C_1 = multiplyVectorByMatrix(C_1, G_pseudo)
	fmt.Println("C_1 vector:")
	fmt.Println(C_1)
	//S_1 = [][]int{{1, -1, 1, 0}, {0, 0, 1, 0}, {0, -1, 1, 1}, {0, 1, -1, 0}}  its inv matrix for S
	M_recieved := multiplyMatrixByVector(S_1, C_1)

	//M_recieved := multiplyVectorByMatrix(C_1, S_1)
	fmt.Println("MSG:")
	fmt.Println(M_recieved)

	E := multiplyMatrices(S, S_1)
	fmt.Println(E)
	E = multiplyMatrices(G, G_pseudo)
	fmt.Println(E)

}

func findPseudoinverse(G [][]int) [][]int {
	G_T := Transpose(G)

	// Вычисляем G^T * G
	G_T_G := multiplyMatrices(G_T, G)

	// Вычисляем обратную матрицу (G^T * G)^-1
	G_T_G_Inv := Transpose(G_T_G)

	// Вычисляем псевдообратную матрицу G^+
	G_Plus := multiplyMatrices(multiplyMatrices(G_T_G_Inv, G_T), Transpose(G))

	return G_Plus
}
