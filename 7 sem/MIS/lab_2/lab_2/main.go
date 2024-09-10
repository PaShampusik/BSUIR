package main

import (
	"bytes"
	"encoding/binary"
	"fmt"
)

const (
	blockSize = 128 // Размер блока в битах
	keySize   = 256 // Размер ключа в битах
)

// Таблица подстановки H
var substitutionTable = [16][16]byte{
	{0xB1, 0x94, 0xBA, 0xC8, 0x0A, 0x08, 0xF5, 0x3B, 0x36, 0x6D, 0x00, 0x8E, 0x58, 0x4A, 0x5D, 0xE4},
	{0x85, 0x04, 0xFA, 0x9D, 0x1B, 0xB6, 0xC7, 0xAC, 0x25, 0x2E, 0x72, 0xC2, 0x02, 0xFD, 0xCE, 0x0D},
	{0x5B, 0xE3, 0xD6, 0x12, 0x17, 0xB9, 0x61, 0x81, 0xFE, 0x67, 0x86, 0xAD, 0x71, 0x6B, 0x89, 0x0B},
	{0x5C, 0xB0, 0xC0, 0xFF, 0x33, 0xC3, 0x56, 0xB8, 0x35, 0xC4, 0x05, 0xAE, 0xD8, 0xE0, 0x7F, 0x99},
	{0xE1, 0x2B, 0xDC, 0x1A, 0xE2, 0x82, 0x57, 0xEC, 0x70, 0x3F, 0xCC, 0xF0, 0x95, 0xEE, 0x8D, 0xF1},
	{0xC1, 0xAB, 0x76, 0x38, 0x9F, 0xE6, 0x78, 0xCA, 0xF7, 0xC6, 0xF8, 0x60, 0xD5, 0xBB, 0x9C, 0x4F},
	{0xF3, 0x3C, 0x65, 0x7B, 0x63, 0x7C, 0x30, 0x6A, 0xDD, 0x4E, 0xA7, 0x79, 0x9E, 0xB2, 0x3D, 0x31},
	{0x3E, 0x98, 0xB5, 0x6E, 0x27, 0xD3, 0xBC, 0xCF, 0x59, 0x1E, 0x18, 0x1F, 0x4C, 0x5A, 0xB7, 0x93},
	{0xE9, 0xDE, 0xE7, 0x2C, 0x8F, 0x0C, 0x0F, 0xA6, 0x2D, 0xDB, 0x49, 0xF4, 0x6F, 0x73, 0x96, 0x47},
	{0x06, 0x07, 0x53, 0x16, 0xED, 0x24, 0x7A, 0x37, 0x39, 0xCB, 0xA3, 0x83, 0x03, 0xA9, 0x8B, 0xF6},
	{0x92, 0xBD, 0x9B, 0x1C, 0xE5, 0xD1, 0x41, 0x01, 0x54, 0x45, 0xFB, 0xC9, 0x5E, 0x4D, 0x0E, 0xF2},
	{0x68, 0x20, 0x80, 0xAA, 0x22, 0x7D, 0x64, 0x2F, 0x26, 0x87, 0xF9, 0x34, 0x90, 0x40, 0x55, 0x11},
	{0xBE, 0x32, 0x97, 0x13, 0x43, 0xFC, 0x9A, 0x48, 0xA0, 0x2A, 0x88, 0x5F, 0x19, 0x4B, 0x09, 0xA1},
	{0x7E, 0xCD, 0xA4, 0xD0, 0x15, 0x44, 0xAF, 0x8C, 0xA5, 0x84, 0x50, 0xBF, 0x66, 0xD2, 0xE8, 0x8A},
	{0xA2, 0xD7, 0x46, 0x52, 0x42, 0xA8, 0xDF, 0xB3, 0x69, 0x74, 0xC5, 0x51, 0xEB, 0x23, 0x29, 0x21},
	{0xD4, 0xEF, 0xD9, 0xB4, 0x3A, 0x62, 0x28, 0x75, 0x91, 0x14, 0x10, 0xEA, 0x77, 0x6C, 0xDA, 0x1D},
}

// Функция подстановки H
func H(u []byte) []byte {
	if len(u) != 4 {
		panic("H function requires 4 bytes")
	}
	i := u[0] >> 4
	j := u[0] & 0x0F
	return []byte{
		substitutionTable[i][j],
		substitutionTable[u[1]>>4][u[1]&0x0F],
		substitutionTable[u[2]>>4][u[2]&0x0F],
		substitutionTable[u[3]>>4][u[3]&0x0F],
	}
}

// Функция вращения и подстановки G
func G5(u []byte) []byte {
	return rotateHigh(H(u), 5)
}

func G13(u []byte) []byte {
	return rotateHigh(H(u), 13)
}

func G21(u []byte) []byte {
	return rotateHigh(H(u), 21)
}

// Вращение влево
func rotateHigh(u []byte, r int) []byte {
	if len(u) != 4 {
		panic("rotateHigh requires 4 bytes")
	}
	// Вращаем 32 бита
	r = r % 32
	if r == 0 {
		return u
	}
	var result [4]byte
	binary.BigEndian.PutUint32(result[:], (binary.BigEndian.Uint32(u)<<r)|(binary.BigEndian.Uint32(u)>>(32-r)))
	return result[:]
}

// Функция F
func F(key []byte, input []byte) []byte {
	if len(key) != 32 || len(input) != 16 {
		panic("Invalid key or input length")
	}

	// Разделяем входные данные на 4 слова по 32 бита
	x1 := input[0:4]
	x2 := input[4:8]
	x3 := input[8:12]
	x4 := input[12:16]

	// Генерируем ключи K1, K2, ..., K56
	keys := make([][]byte, 56)
	for i := 0; i < 56; i++ {
		keys[i] = key[i%8*4 : (i%8+1)*4]
	}

	a, b, c, d := x1, x2, x3, x4

	for i := 1; i <= 8; i++ {
		b = xor(b, G5(append(a, keys[7*i-6]...)))
		c = xor(c, G21(append(d, keys[7*i-5]...)))
		a = xor(a, G13(append(b, keys[7*i-4]...)))
		e := xor(G21(append(b, c, keys[7*i-3]...)), intToBytes(i, 4))
		b = xor(b, e)
		c = xor(c, e)
		d = xor(d, G13(append(c, keys[7*i-2]...)))
		b = xor(b, G21(append(a, keys[7*i-1]...)))
		c = xor(c, G5(append(d, keys[7*i]...)))

		// Обмен значениями
		a, b, c, d = b, d, a, c
	}

	// Собираем результат
	result := append(append(b, d...), append(a, c...)...)
	return result
}

// Функция XOR
func xor(a, b []byte) []byte {
	result := make([]byte, len(a))
	for i := range a {
		result[i] = a[i] ^ b[i]
	}
	return result
}

// Преобразование целого числа в байты
func intToBytes(n int, size int) []byte {
	buf := new(bytes.Buffer)
	binary.Write(buf, binary.BigEndian, int32(n))
	return buf.Bytes()[:size]
}

// Шифрование
func Encrypt(key []byte, message []byte) []byte {
	n := len(message) / (blockSize / 8)
	if len(message)%(blockSize/8) != 0 {
		n++
	}

	var result bytes.Buffer

	for i := 0; i < n; i++ {
		start := i * (blockSize / 8)
		end := start + (blockSize / 8)
		if end > len(message) {
			end = len(message)
		}

		block := message[start:end]
		if len(block) < (blockSize / 8) {
			// Добавляем нули до 128 бит
			padding := make([]byte, (blockSize/8)-len(block))
			block = append(block, padding...)
		}

		encryptedBlock := F(key, block)
		result.Write(encryptedBlock)
	}

	return result.Bytes()
}

// Дешифрование
func Decrypt(key []byte, message []byte) []byte {
	n := len(message) / (blockSize / 8)
	var result bytes.Buffer

	for i := 0; i < n; i++ {
		start := i * (blockSize / 8)
		end := start + (blockSize / 8)
		if end > len(message) {
			end = len(message)
		}

		block := message[start:end]
		decryptedBlock := F(key, block) // Для простоты используем F для дешифрования
		result.Write(decryptedBlock)
	}

	return result.Bytes()
}

func main() {
	key := make([]byte, keySize/8)
	message := []byte("Пример сообщения для шифрования.")

	// Шифрование
	encrypted := Encrypt(key, message)
	fmt.Printf("Зашифрованное сообщение: %x\n", encrypted)

	// Дешифрование
	decrypted := Decrypt(key, encrypted)
	fmt.Printf("Расшифрованное сообщение: %s\n", string(decrypted))
}
