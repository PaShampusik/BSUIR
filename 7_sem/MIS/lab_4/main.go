package main

import (
	"math"
	"math/rand"
	"os"
)

const N = 8

var matrixG = [][]int{
	{1, 0, 0, 0, 1, 1, 0},
	{0, 1, 0, 0, 1, 0, 1},
	{0, 0, 1, 0, 0, 1, 1},
	{0, 0, 0, 1, 1, 1, 1},
}

var matrixS = [][]int{
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
}

var matrixP = [][]int{
	{1, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 1},
}

var matrixGHead [][]int
var matrixH = [][]int{
	{1, 1, 0},
	{1, 0, 1},
	{0, 1, 1},
	{1, 1, 1},
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1},
}

var matrixInverseP [][]int
var matrixInverseS [][]int
var vectorZ []int

func prepareAllInfo() {
	matrixGHead = multiplyMatrices(matrixS, matrixG)
	matrixGHead = multiplyMatrices(matrixGHead, matrixP)

	for i := range matrixGHead {
		for j := range matrixGHead[i] {
			if matrixGHead[i][j]%2 == 0 {
				matrixGHead[i][j] = 0
			}
		}
	}

	matrixInverseP = matrixInverse(matrixP)
	matrixInverseS = matrixInverse(matrixS)
}

func encryptByte(byteForEncryption byte) []byte {
	bitArrayFull := toBitArray([]byte{byteForEncryption})
	byteArr := make([]byte, (N-1)*2)
	index := 0
	for k := 0; k < N; k += N / 2 {
		bitArrayHalf := bitArrayFull[k : k+N/2]
		vectorZ = getErrorVector(N-1, N/2)

		arr := make([]int, len(bitArrayHalf))
		for i, bit := range bitArrayHalf {
			arr[i] = toBool(bit)
		}

		result := multiplyMatrixOnVector(matrixGHead, arr)

		for i := range result {
			result[i] = (result[i] + vectorZ[i]) % 2
		}

		for i := range result {
			byteArr[index+i] = byte(result[i])
		}

		index += N - 1
	}

	return byteArr
}

func decryptBytes(inputBytes []byte) byte {
	bytes := make([]byte, 2)
	boolsResult := make([]bool, N)
	index := 0
	for k := 0; k < (N-1)*2; k += N - 1 {
		arr := make([]int, len(inputBytes)/2)
		for i := k; i < k+len(inputBytes)/2; i++ {
			arr[i-k] = int(inputBytes[i])
		}

		vectorCHead := multiplyMatrixOnVector(matrixInverseP, arr)

		for i := range vectorCHead {
			vectorCHead[i] %= 2
		}

		syndrom := multiplyMatrixOnVector(matrixH, vectorCHead)
		for i := range syndrom {
			syndrom[i] %= 2
		}

		resultIndex := -1
		for i := range matrixH {
			sumIndex := 0
			for j := range matrixH[0] {
				if syndrom[j] == matrixH[i][j] {
					sumIndex++
				}
			}
			if sumIndex == len(matrixH[0]) {
				resultIndex = i
				break
			}
		}

		if resultIndex != -1 {
			if vectorCHead[resultIndex] == 0 {
				vectorCHead[resultIndex] = 1
			} else {
				vectorCHead[resultIndex] = 0
			}
		}

		vectorCHead = multiplyMatrixOnVector(matrixInverseS, vectorCHead)

		for i := index; i < index+len(boolsResult)/2; i++ {
			boolsResult[i] = vectorCHead[i-index] == 1
		}

		index += N / 2
	}

	bytes[0] = fromBitArray(boolsResult)
	return bytes[0]
}

func encryptMessageFromFile(inputFileName, outputFileName string) {
	prepareAllInfo()

	inputFile, err := os.Open(inputFileName)
	if err != nil {
		panic(err)
	}
	defer inputFile.Close()

	outputFile, err := os.Create(outputFileName)
	if err != nil {
		panic(err)
	}
	defer outputFile.Close()

	var buf [1]byte
	for {
		_, err := inputFile.Read(buf[:])
		if err != nil {
			break
		}
		encryptedBytes := encryptByte(buf[0])
		_, err = outputFile.Write(encryptedBytes)
		if err != nil {
			panic(err)
		}
	}
}

func decryptMessageFromFile(inputFileName, outputFileName string) {
	inputFile, err := os.Open(inputFileName)
	if err != nil {
		panic(err)
	}
	defer inputFile.Close()

	outputFile, err := os.Create(outputFileName)
	if err != nil {
		panic(err)
	}
	defer outputFile.Close()

	var buf = make([]byte, (N-1)*2)
	for {
		_, err := inputFile.Read(buf)
		if err != nil {
			break
		}
		decryptedByte := decryptBytes(buf)
		_, err = outputFile.Write([]byte{decryptedByte})
		if err != nil {
			panic(err)
		}
	}
}

func main() {
	encryptMessageFromFile("input.txt", "output.txt")
	decryptMessageFromFile("output.txt", "decrypted.txt")
}

func getErrorVector(length, maxIndex int) []int {
	arr := make([]int, length)
	index := rand.Intn(maxIndex)
	arr[index] = 1
	return arr
}

func matrixCreate(rows, cols int) [][]int {
	result := make([][]int, rows)
	for i := range result {
		result[i] = make([]int, cols)
	}
	return result
}

func multiplyMatrices(matrixA, matrixB [][]int) [][]int {
	aRows, aCols := len(matrixA), len(matrixA[0])
	bRows, bCols := len(matrixB), len(matrixB[0])

	if aCols != bRows {
		panic("Non-conformable matrices in multiplyMatrices")
	}

	result := matrixCreate(aRows, bCols)
	for i := range result {
		for j := range result[i] {
			for k := 0; k < aCols; k++ {
				result[i][j] += matrixA[i][k] * matrixB[k][j]
			}
		}
	}

	return result
}

func matrixDuplicate(matrix [][]int) [][]int {
	result := matrixCreate(len(matrix), len(matrix[0]))
	for i := range matrix {
		for j := range matrix[i] {
			result[i][j] = matrix[i][j]
		}
	}
	return result
}

func matrixDecompose(matrix [][]int) ([][]int, []int, int) {
	n := len(matrix)
	result := matrixDuplicate(matrix)
	perm := make([]int, n)
	for i := range perm {
		perm[i] = i
	}
	toggle := 1

	for j := 0; j < n-1; j++ {
		colMax := math.Abs(float64(result[j][j]))
		pRow := j
		for i := j + 1; i < n; i++ {
			if math.Abs(float64(result[i][j])) > colMax {
				colMax = math.Abs(float64(result[i][j]))
				pRow = i
			}
		}

		if pRow != j {
			result[pRow], result[j] = result[j], result[pRow]
			perm[pRow], perm[j] = perm[j], perm[pRow]
			toggle = -toggle
		}

		if math.Abs(float64(result[j][j])) < 1e-20 {
			return nil, nil, 0
		}
		for i := j + 1; i < n; i++ {
			result[i][j] /= result[j][j]
			for k := j + 1; k < n; k++ {
				result[i][k] -= result[i][j] * result[j][k]
			}
		}
	}

	return result, perm, toggle
}

func matrixInverse(matrix [][]int) [][]int {
	n := len(matrix)
	result := matrixDuplicate(matrix)
	lum, perm, _ := matrixDecompose(matrix)
	if lum == nil {
		panic("Unable to compute inverse")
	}
	b := make([]int, n)
	for i := range perm {
		for j := 0; j < n; j++ {
			if i == perm[j] {
				b[j] = 1
			} else {
				b[j] = 0
			}
		}
		x := helperSolve(lum, b)
		for j := range x {
			result[j][i] = x[j]
		}
	}
	return result
}

func multiplyMatrixOnVector(matrix [][]int, vector []int) []int {
	result := make([]int, len(matrix[0]))
	for i := range result {
		for j := range matrix {
			result[i] += vector[j] * matrix[j][i]
		}
	}
	return result
}

func toBitArray(bytes []byte) []bool {
	result := make([]bool, len(bytes)*8)
	for i, b := range bytes {
		for j := 0; j < 8; j++ {
			result[i*8+j] = b&(1<<uint(j)) != 0
		}
	}
	return result
}

func fromBitArray(bits []bool) byte {
	var result byte
	for i, b := range bits {
		if b {
			result |= 1 << uint(i)
		}
	}
	return result
}

func toBool(b bool) int {
	if b {
		return 1
	}
	return 0
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func helperSolve(luMatrix [][]int, b []int) []int {
	n := len(luMatrix)
	x := make([]int, n)
	copy(x, b)
	for i := 1; i < n; i++ {
		sum := x[i]
		for j := 0; j < i; j++ {
			sum -= luMatrix[i][j] * x[j]
		}
		x[i] = sum
	}

	x[n-1] /= luMatrix[n-1][n-1]
	for i := n - 2; i >= 0; i-- {
		sum := x[i]
		for j := i + 1; j < n; j++ {
			sum -= luMatrix[i][j] * x[j]
		}
		x[i] = sum / luMatrix[i][i]
	}

	return x
}
