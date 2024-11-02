package main

import (
	"crypto/rand"
	"fmt"
	"io/ioutil"
	"math/big"
)

type Rabin struct {
	p, q, n *big.Int
}

func NewRabin() (*Rabin, error) {
	// Генерация двух больших простых чисел p и q
	p, err := rand.Prime(rand.Reader, 512)
	if err != nil {
		return nil, err
	}
	q, err := rand.Prime(rand.Reader, 512)
	if err != nil {
		return nil, err
	}

	n := new(big.Int).Mul(p, q)

	return &Rabin{p: p, q: q, n: n}, nil
}

func (r *Rabin) Encrypt(message []byte) (*big.Int, error) {
	m := new(big.Int).SetBytes(message)
	c := new(big.Int).Exp(m, big.NewInt(2), r.n) // c = m^2 mod n
	return c, nil
}

func (r *Rabin) Decrypt(c *big.Int) ([]byte, error) {
	// Находим квадратные корни по модулю n
	p1 := new(big.Int).ModSqrt(c, r.p)
	p2 := new(big.Int).Sub(r.p, p1)

	q1 := new(big.Int).ModSqrt(c, r.q)
	q2 := new(big.Int).Sub(r.q, q1)

	// Получаем 4 возможных корня
	roots := []*big.Int{new(big.Int).Set(p1), new(big.Int).Set(p2), new(big.Int).Set(q1), new(big.Int).Set(q2)}

	// Преобразуем корни в байты
	var messages [][]byte
	for _, root := range roots {
		m := new(big.Int).Mod(root, r.n)
		messages = append(messages, m.Bytes())
	}

	// Возвращаем первый корень (можно улучшить выбор)
	return messages[0], nil
}

func (r *Rabin) PublicKey() *big.Int {
	return r.n
}

func (r *Rabin) PrivateKey() (*big.Int, *big.Int) {
	return r.p, r.q
}

func main() {
	rabin, err := NewRabin()
	if err != nil {
		fmt.Println("Error generating Rabin keys:", err)
		return
	}

	// Вывод открытого и закрытого ключей
	fmt.Println("Public Key (n):", rabin.PublicKey())
	p, q := rabin.PrivateKey()
	fmt.Println("Private Key (p):", p)
	fmt.Println("Private Key (q):", q)

	// Чтение текста из файла
	inputFile := "input.txt"
	data, err := ioutil.ReadFile(inputFile)
	if err != nil {
		fmt.Println("Error reading file:", err)
		return
	}

	// Шифрование
	ciphertext, err := rabin.Encrypt(data)
	if err != nil {
		fmt.Println("Error encrypting:", err)
		return
	}

	// Сохранение зашифрованного текста в файл
	err = ioutil.WriteFile("ciphertext.txt", ciphertext.Bytes(), 0644)
	if err != nil {
		fmt.Println("Error writing ciphertext to file:", err)
		return
	}

	// Дешифрование
	decrypted, err := rabin.Decrypt(ciphertext)
	if err != nil {
		fmt.Println("Error decrypting:", err)
		return
	}

	// Сохранение расшифрованного текста в файл
	err = ioutil.WriteFile("decrypted.txt", decrypted, 0644)
	if err != nil {
		fmt.Println("Error writing decrypted text to file:", err)
		return
	}

	fmt.Println("Encryption and decryption completed successfully.")
}
