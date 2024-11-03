package main

import (
	"crypto/rand"
	"fmt"
	"io/ioutil"
	"math/big"
	"os"
	"strings"
)

func generatePrime() *big.Int {
	for {
		p, _ := rand.Prime(rand.Reader, 100)
		if new(big.Int).Mod(new(big.Int).Sub(p, big.NewInt(3)), big.NewInt(4)).Cmp(big.NewInt(0)) == 0 {
			return p
		}
	}
}

func encrypt(message, n int64) *big.Int {
	return new(big.Int).Exp(big.NewInt(message), big.NewInt(2), big.NewInt(n))
}

func gcdExtended(a, b *big.Int) (*big.Int, *big.Int) {
	if a.Cmp(big.NewInt(0)) == 0 {
		return big.NewInt(0), big.NewInt(1)
	}

	x1, y1 := gcdExtended(new(big.Int).Mod(b, a), a)
	x := new(big.Int).Sub(y1, new(big.Int).Mul(new(big.Int).Div(b, a), x1))
	y := x1
	return x, y
}

func rabinDecrypt(ciphertext, p, q *big.Int) []*big.Int {
	n := new(big.Int).Mul(p, q)
	four := big.NewInt(4)
	one := big.NewInt(1)
	p1 := new(big.Int).Div(new(big.Int).Add(p, one), four)
	q1 := new(big.Int).Div(new(big.Int).Add(q, one), four)
	mp := new(big.Int).Exp(ciphertext, p1, p)
	mq := new(big.Int).Exp(ciphertext, q1, q)

	x, y := gcdExtended(p, q)

	r := new(big.Int).Mod(new(big.Int).Add(new(big.Int).Mul(new(big.Int).Mul(x, p), mq), new(big.Int).Mul(new(big.Int).Mul(y, q), mp)), n)
	s := new(big.Int).Mod(new(big.Int).Sub(new(big.Int).Mul(new(big.Int).Mul(x, p), mq), new(big.Int).Mul(new(big.Int).Mul(y, q), mp)), n)

	return []*big.Int{r, new(big.Int).Sub(n, r), s, new(big.Int).Sub(n, s)}
}

func main() {
	p := generatePrime()
	q := generatePrime()
	for p.Cmp(q) == 0 {
		q = generatePrime()
	}

	fmt.Println("Выбранные простые числа p и q:", p, q)

	n := new(big.Int).Mul(p, q)
	fmt.Println("Произведение простых чисел (n):", n)

	plaintext, err := ioutil.ReadFile("input.txt")
	if err != nil {
		fmt.Println("Ошибка чтения файла:", err)
		return
	}

	var encryptedData []*big.Int
	for _, c := range plaintext {
		encryptedData = append(encryptedData, encrypt(int64(c), n.Int64()))
	}

	_ = ioutil.WriteFile("encrypted.txt", []byte(strings.Join(func() []string {
		var s []string
		for _, v := range encryptedData {
			s = append(s, v.String())
		}
		return s
	}(), " ")), 0644)
	fmt.Println("Зашифрованные данные сохранены в 'encrypted.txt'")

	encryptedBytes, _ := ioutil.ReadFile("encrypted.txt")
	var decryptedData []*big.Int
	for _, ciphertext := range strings.Split(string(encryptedBytes), " ") {
		c, _ := new(big.Int).SetString(ciphertext, 10)
		possibleValues := rabinDecrypt(c, p, q)
		for _, i := range possibleValues {
			if i.Cmp(big.NewInt(0)) >= 0 && i.Cmp(big.NewInt(128)) <= 0 {
				decryptedData = append(decryptedData, i)
				break
			}
		}
	}

	decryptedBytes := []byte{}
	for _, i := range decryptedData {
		decryptedBytes = append(decryptedBytes, byte(i.Int64()))
	}

	_ = ioutil.WriteFile("decrypted.txt", decryptedBytes, 0644)
	fmt.Println("Расшифрованные данные сохранены в 'decrypted.txt'")

	_ = os.Remove("encrypted.txt")
}
