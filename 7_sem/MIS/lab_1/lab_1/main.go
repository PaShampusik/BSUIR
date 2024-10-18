package main

import (
	"encoding/binary"
	"fmt"
	"io"
	"os"
)

var SBox = [8][16]uint8{
	{4, 10, 9, 2, 13, 8, 0, 14, 6, 11, 1, 12, 7, 15, 5, 3},
	{14, 11, 4, 12, 6, 13, 15, 10, 2, 3, 8, 1, 0, 7, 5, 9},
	{5, 8, 1, 13, 10, 3, 4, 2, 14, 15, 12, 7, 6, 0, 9, 11},
	{7, 13, 10, 1, 0, 8, 9, 15, 14, 4, 6, 12, 11, 2, 5, 3},
	{6, 12, 7, 1, 5, 15, 13, 8, 4, 10, 9, 14, 0, 3, 11, 2},
	{4, 11, 10, 0, 7, 2, 1, 13, 3, 6, 8, 5, 9, 12, 15, 14},
	{13, 11, 4, 1, 3, 15, 5, 9, 0, 10, 14, 7, 6, 8, 2, 12},
	{1, 15, 13, 0, 5, 7, 10, 4, 9, 2, 3, 14, 6, 11, 8, 12},
}

func cyclicShiftLeft(value uint32, shift int) uint32 {
	return (value << shift) | (value >> (32 - shift))
}

func F(block uint32, key uint32) uint32 {
	temp := block + key
	for i := 0; i < 8; i++ {
		s_input := (temp >> (4 * i)) & 0xF
		s_output := SBox[i][s_input]
		temp = (temp &^ (0xF << (4 * i))) | (uint32(s_output) << (4 * i)) // Convert s_output to uint32
	}
	return cyclicShiftLeft(temp, 11)
}

func encryptBlock(block *[2]uint32, key []uint32) {
	N1, N2 := block[0], block[1]
	for i := 0; i < 32; i++ {
		round_key := key[i%8]
		temp := F(N1, round_key)
		temp ^= N2
		N2 = N1
		N1 = temp
	}
	block[0], block[1] = N2, N1
}

func decryptBlock(block *[2]uint32, key []uint32) {
	N1, N2 := block[0], block[1]
	for i := 31; i >= 0; i-- {
		round_key := key[i%8]
		temp := F(N1, round_key)
		temp ^= N2
		N2 = N1
		N1 = temp
	}
	block[0], block[1] = N2, N1
}

func readFile(filename string) ([]byte, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	return io.ReadAll(file)
}

func writeFile(filename string, data []byte) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	_, err = file.Write(data)
	return err
}

func processFile(inputFilename, outputFilename string, key []uint32, encrypt bool) error {
	data, err := readFile(inputFilename)
	if err != nil {
		return err
	}
	if encrypt {
		fmt.Println("Input data: ", data)
	}

	paddingSize := (8 - (len(data) % 8)) % 8
	data = append(data, make([]byte, paddingSize)...)

	for i := 0; i < len(data); i += 8 {
		block := [2]uint32{}
		block[0] = binary.LittleEndian.Uint32(data[i : i+4])
		block[1] = binary.LittleEndian.Uint32(data[i+4 : i+8])

		if encrypt {
			encryptBlock(&block, key)
		} else {
			decryptBlock(&block, key)
		}

		// Create a byte slice to hold the output
		output := make([]byte, 8)
		binary.LittleEndian.PutUint32(output[0:4], block[0])
		binary.LittleEndian.PutUint32(output[4:8], block[1])

		// Copy the output back to the original data slice
		copy(data[i:i+8], output)
	}

	if encrypt {
		fmt.Println("Encrypted data: ", data)
	} else {
		fmt.Println("Decrypted data: ", data)
	}

	return writeFile(outputFilename, data)
}

func main() {
	key := []uint32{
		0xA56BABCD, 0xDEF01234, 0x789ABCDE, 0xFEDCBA98,
		0x01234567, 0x89ABCDEF, 0x12345678, 0x9ABCDEF0,
	}

	inputFilename := "input.txt"
	encryptedFilename := "encrypted.bin"
	decryptedFilename := "decrypted.txt"

	fmt.Println("Start of encrypting:", encryptedFilename)

	err := processFile(inputFilename, encryptedFilename, key, true)
	if err != nil {
		fmt.Println("Error encrypting file:", err)
	} else {
		fmt.Println("Encrypted file:", encryptedFilename)
	}

	err = processFile(encryptedFilename, decryptedFilename, key, false)
	if err != nil {
		fmt.Println("Error decrypting file:", err)
	} else {
		fmt.Println("Decrypted file:", decryptedFilename)
	}

}
