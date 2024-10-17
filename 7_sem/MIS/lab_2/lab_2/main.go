package main

import (
	"encoding/hex"
	"fmt"
	"io/ioutil"
	"log"
)

const (
	blockSize = 16
	keySize   = 32
)

var H = [256]uint8{
	0xB1, 0x94, 0xBA, 0xC8, 0x0A, 0x08, 0xF5, 0x3B, 0x36, 0x6D, 0x00, 0x8E, 0x58, 0x4A, 0x5D, 0xE4,
	0x85, 0x04, 0xFA, 0x9D, 0x1B, 0xB6, 0xC7, 0xAC, 0x25, 0x2E, 0x72, 0xC2, 0x02, 0xFD, 0xCE, 0x0D,
	0x5B, 0xE3, 0xD6, 0x12, 0x17, 0xB9, 0x61, 0x81, 0xFE, 0x67, 0x86, 0xAD, 0x71, 0x6B, 0x89, 0x0B,
	0x5C, 0xB0, 0xC0, 0xFF, 0x33, 0xC3, 0x56, 0xB8, 0x35, 0xC4, 0x05, 0xAE, 0xD8, 0xE0, 0x7F, 0x99,
	0xE1, 0x2B, 0xDC, 0x1A, 0xE2, 0x82, 0x57, 0xEC, 0x70, 0x3F, 0xCC, 0xF0, 0x95, 0xEE, 0x8D, 0xF1,
	0xC1, 0xAB, 0x76, 0x38, 0x9F, 0xE6, 0x78, 0xCA, 0xF7, 0xC6, 0xF8, 0x60, 0xD5, 0xBB, 0x9C, 0x4F,
	0xF3, 0x3C, 0x65, 0x7B, 0x63, 0x7C, 0x30, 0x6A, 0xDD, 0x4E, 0xA7, 0x79, 0x9E, 0xB2, 0x3D, 0x31,
	0x3E, 0x98, 0xB5, 0x6E, 0x27, 0xD3, 0xBC, 0xCF, 0x59, 0x1E, 0x18, 0x1F, 0x4C, 0x5A, 0xB7, 0x93,
	0xE9, 0xDE, 0xE7, 0x2C, 0x8F, 0x0C, 0x0F, 0xA6, 0x2D, 0xDB, 0x49, 0xF4, 0x6F, 0x73, 0x96, 0x47,
	0x06, 0x07, 0x53, 0x16, 0xED, 0x24, 0x7A, 0x37, 0x39, 0xCB, 0xA3, 0x83, 0x03, 0xA9, 0x8B, 0xF6,
	0x92, 0xBD, 0x9B, 0x1C, 0xE5, 0xD1, 0x41, 0x01, 0x54, 0x45, 0xFB, 0xC9, 0x5E, 0x4D, 0x0E, 0xF2,
	0x68, 0x20, 0x80, 0xAA, 0x22, 0x7D, 0x64, 0x2F, 0x26, 0x87, 0xF9, 0x34, 0x90, 0x40, 0x55, 0x11,
	0xBE, 0x32, 0x97, 0x13, 0x43, 0xFC, 0x9A, 0x48, 0xA0, 0x2A, 0x88, 0x5F, 0x19, 0x4B, 0x09, 0xA1,
	0x7E, 0xCD, 0xA4, 0xD0, 0x15, 0x44, 0xAF, 0x8C, 0xA5, 0x84, 0x50, 0xBF, 0x66, 0xD2, 0xE8, 0x8A,
	0xA2, 0xD7, 0x46, 0x52, 0x42, 0xA8, 0xDF, 0xB3, 0x69, 0x74, 0xC5, 0x51, 0xEB, 0x23, 0x29, 0x21,
	0xD4, 0xEF, 0xD9, 0xB4, 0x3A, 0x62, 0x28, 0x75, 0x91, 0x14, 0x10, 0xEA, 0x77, 0x6C, 0xDA, 0x1D,
}

var KeyIndex = [8][7]uint8{
	{0, 1, 2, 3, 4, 5, 6},
	{7, 0, 1, 2, 3, 4, 5},
	{6, 7, 0, 1, 2, 3, 4},
	{5, 6, 7, 0, 1, 2, 3},
	{4, 5, 6, 7, 0, 1, 2},
	{3, 4, 5, 6, 7, 0, 1},
	{2, 3, 4, 5, 6, 7, 0},
	{1, 2, 3, 4, 5, 6, 7},
}

func load32(in []byte) uint32 {
	return uint32(in[0]) | uint32(in[1])<<8 | uint32(in[2])<<16 | uint32(in[3])<<24
}

func store32(out []byte, v uint32) {
	out[0] = byte(v)
	out[1] = byte(v >> 8)
	out[2] = byte(v >> 16)
	out[3] = byte(v >> 24)
}

func rotl32(x, r uint32) uint32 {
	return (x << r) | (x >> (32 - r))
}

func hu1(x uint32, H [256]uint8) uint32 {
	return uint32(H[(x>>24)&0xff]) << 24
}

func hu2(x uint32, H [256]uint8) uint32 {
	return uint32(H[(x>>16)&0xff]) << 16
}

func hu3(x uint32, H [256]uint8) uint32 {
	return uint32(H[(x>>8)&0xff]) << 8
}

func hu4(x uint32, H [256]uint8) uint32 {
	return uint32(H[x&0xff])
}

func g(x uint32, H [256]uint8, r uint32) uint32 {
	return rotl32(hu4(x, H)|hu3(x, H)|hu2(x, H)|hu1(x, H), r)
}

func beltInit(ks, k []uint8, klen int) {
	switch klen {
	case 16:
		for i := 0; i < 16; i++ {
			ks[i+0] = k[i]
			ks[i+16] = k[i]
		}
	case 24:
		for i := 0; i < 24; i++ {
			ks[i] = k[i]
		}
		store32(ks[24:], load32(k[0:])^load32(k[4:])^load32(k[8:]))
		store32(ks[28:], load32(k[12:])^load32(k[16:])^load32(k[20:]))
	case 32:
		for i := 0; i < 32; i++ {
			ks[i] = k[i]
		}
	}
}

func beltEncrypt(out, in, ks []uint8) {
	a := load32(in[0:4])
	b := load32(in[4:8])
	c := load32(in[8:12])
	d := load32(in[12:16])
	var e uint32
	key := [8]uint32{}

	for i := 0; i < 8; i++ {
		key[i] = load32(ks[4*i : 4*(i+1)])
	}

	for i := 0; i < 8; i++ {
		b ^= g(a+key[KeyIndex[i][0]], H, 5)
		c ^= g(d+key[KeyIndex[i][1]], H, 21)
		a -= g(b+key[KeyIndex[i][2]], H, 13)
		e = g(b+c+key[KeyIndex[i][3]], H, 21) ^ uint32(i+1)
		b += e
		c -= e
		d += g(c+key[KeyIndex[i][4]], H, 13)
		b ^= g(a+key[KeyIndex[i][5]], H, 21)
		c ^= g(d+key[KeyIndex[i][6]], H, 5)
		a, b = b, a
		c, d = d, c
		b, c = c, b
	}
	store32(out[0:4], b)
	store32(out[4:8], d)
	store32(out[8:12], a)
	store32(out[12:16], c)
}

func beltDecrypt(out, in, ks []uint8) {
	a := load32(in[0:4])
	b := load32(in[4:8])
	c := load32(in[8:12])
	d := load32(in[12:16])
	var e uint32
	key := [8]uint32{}

	for i := 0; i < 8; i++ {
		key[i] = load32(ks[4*i : 4*(i+1)])
	}

	for i := 0; i < 8; i++ {
		b ^= g(a+key[KeyIndex[7-i][6]], H, 5)
		c ^= g(d+key[KeyIndex[7-i][5]], H, 21)
		a -= g(b+key[KeyIndex[7-i][4]], H, 13)
		e = g(b+c+key[KeyIndex[7-i][3]], H, 21) ^ uint32(7-i+1)
		b += e
		c -= e
		d += g(c+key[KeyIndex[7-i][2]], H, 13)
		b ^= g(a+key[KeyIndex[7-i][1]], H, 21)
		c ^= g(d+key[KeyIndex[7-i][0]], H, 5)
		a, b = b, a
		c, d = d, c
		a, d = d, a
	}
	store32(out[0:4], c)
	store32(out[4:8], a)
	store32(out[8:12], d)
	store32(out[12:16], b)
}

func processBlocks(data []uint8, ks []uint8, encrypt bool) []uint8 {
	var result []uint8
	block := make([]uint8, blockSize)

	for i := 0; i < len(data); i += blockSize {
		// Handle the last block if it's less than blockSize
		if i+blockSize > len(data) {
			copy(block, data[i:])
			// Pad the block if necessary
			for j := len(data) % blockSize; j < blockSize; j++ {
				block[j] = 0 // Padding with zeros
			}
		} else {
			copy(block, data[i:i+blockSize])
		}

		if encrypt {
			outBlock := make([]uint8, blockSize)
			beltEncrypt(outBlock, block, ks)
			result = append(result, outBlock...)
		} else {
			outBlock := make([]uint8, blockSize)
			beltDecrypt(outBlock, block, ks)
			result = append(result, outBlock...)
		}
	}

	return result
}

func main() {
	// Read input from input.txt
	data, err := ioutil.ReadFile("input.txt")
	if err != nil {
		log.Fatalf("Failed to read input file: %v", err)
	}

	// Convert the string to a byte slice
	inenc := []uint8(data)

	keyenc := []uint8{
		0xE9, 0xDE, 0xE7, 0x2C,
		0x8F, 0x0C, 0x0F, 0xA6,
		0x2D, 0xDB, 0x49, 0xF4,
		0x6F, 0x73, 0x96, 0x47,
		0x06, 0x07, 0x53, 0x16,
		0xED, 0x24, 0x7A, 0x37,
		0x39, 0xCB, 0xA3, 0x83,
		0x03, 0xA9, 0x8B, 0xF6,
	}

	ks := make([]uint8, keySize)
	beltInit(ks, keyenc, keySize)

	// Encrypt the input data
	outenc := processBlocks(inenc, ks, true)

	fmt.Println("Encryption:")
	fmt.Printf("m: %s\n", string(inenc))
	fmt.Printf("k: %s\n", hex.EncodeToString(ks))
	fmt.Printf("c: %s\n", hex.EncodeToString(outenc))

	// Decrypt the encrypted data
	outdec := processBlocks(outenc, ks, false)

	fmt.Println("\nDecryption:")
	fmt.Printf("c: %s\n", hex.EncodeToString(outenc))
	fmt.Printf("k: %s\n", hex.EncodeToString(ks))
	fmt.Printf("m: %s\n", string(outdec))
}
