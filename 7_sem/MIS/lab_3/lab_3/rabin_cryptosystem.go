package main

import (
	"crypto/rand"
	"fmt"
	"math/big"
)

type Cryptography struct{}

var TWO = big.NewInt(2)
var FOUR = big.NewInt(4)

func (c *Cryptography) generateKey(bitLength int) (*big.Int, *big.Int, *big.Int) {
	p := blumPrime(bitLength / 2)
	q := blumPrime(bitLength / 2)
	N := new(big.Int).Mul(p, q)
	return N, p, q
}

func (c *Cryptography) encrypt(m, N *big.Int) *big.Int {
	return new(big.Int).Exp(m, TWO, N)
}

func (c *Cryptography) decrypt(ciphertext, p, q *big.Int) []*big.Int {
	N := new(big.Int).Mul(p, q)
	p1 := new(big.Int).Exp(ciphertext, new(big.Int).Div(new(big.Int).Add(p, big.NewInt(1)), FOUR), p)
	p2 := new(big.Int).Sub(p, p1)
	q1 := new(big.Int).Exp(ciphertext, new(big.Int).Div(new(big.Int).Add(q, big.NewInt(1)), FOUR), q)
	q2 := new(big.Int).Sub(q, q1)

	ext := gcd(p, q)
	yP := ext[1]
	yQ := ext[2]

	d1 := new(big.Int).Mod(new(big.Int).Add(new(big.Int).Mul(yP, new(big.Int).Mul(p, q1)), new(big.Int).Mul(yQ, new(big.Int).Mul(q, p1))), N)
	d2 := new(big.Int).Mod(new(big.Int).Add(new(big.Int).Mul(yP, new(big.Int).Mul(p, q2)), new(big.Int).Mul(yQ, new(big.Int).Mul(q, p1))), N)
	d3 := new(big.Int).Mod(new(big.Int).Add(new(big.Int).Mul(yP, new(big.Int).Mul(p, q1)), new(big.Int).Mul(yQ, new(big.Int).Mul(q, p2))), N)
	d4 := new(big.Int).Mod(new(big.Int).Add(new(big.Int).Mul(yP, new(big.Int).Mul(p, q2)), new(big.Int).Mul(yQ, new(big.Int).Mul(q, p2))), N)

	return []*big.Int{d1, d2, d3, d4}
}

func gcd(a, b *big.Int) []*big.Int {
	s := big.NewInt(0)
	oldS := big.NewInt(1)
	t := big.NewInt(1)
	oldT := big.NewInt(0)
	r := new(big.Int).Set(b)
	oldR := new(big.Int).Set(a)

	for r.Cmp(big.NewInt(0)) != 0 {
		q := new(big.Int).Div(oldR, r)
		tr := new(big.Int).Set(r)
		r.Sub(oldR, new(big.Int).Mul(q, r))
		oldR.Set(tr)

		ts := new(big.Int).Set(s)
		s.Sub(oldS, new(big.Int).Mul(q, s))
		oldS.Set(ts)

		tt := new(big.Int).Set(t)
		t.Sub(oldT, new(big.Int).Mul(q, t))
		oldT.Set(tt)
	}
	return []*big.Int{oldR, oldS, oldT}
}

func blumPrime(bitLength int) *big.Int {
	var p *big.Int
	for {
		var err error
		p, err = rand.Prime(rand.Reader, bitLength)
		if err != nil {
			panic(err)
		}
		if new(big.Int).Mod(p, FOUR).Cmp(big.NewInt(3)) == 0 {
			break
		}
	}
	return p
}

func main() {
	crypto := &Cryptography{}
	n, p, q := crypto.generateKey(512)
	s := "Hello world"

	fmt.Println("Message sent by sender:", s)

	m := new(big.Int).SetBytes([]byte(s))
	c := crypto.encrypt(m, n)

	fmt.Println("Encrypted Message:", c)

	decryptedMessages := crypto.decrypt(c, p, q)
	var finalMessage string
	for _, b := range decryptedMessages {
		dec := string(b.Bytes())
		if dec == s {
			finalMessage = dec
		}
	}

	fmt.Println("Message received by Receiver:", finalMessage)
}
