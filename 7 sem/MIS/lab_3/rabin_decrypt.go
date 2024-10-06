package main

import (
	"crypto/sha256"
	"fmt"
	"io/ioutil"
	"math/big"
	"strings"
)

func compareMessageAndHash(m1 *big.Int, m2 *big.Int, m3 *big.Int, m4 *big.Int,
	hashofMessageInString string) *big.Int {

	m1Hash := getMessageHashInString(m1.String())
	m2Hash := getMessageHashInString(m2.String())
	m3Hash := getMessageHashInString(m3.String())
	m4Hash := getMessageHashInString(m4.String())

	message := big.NewInt(0)

	if m1Hash == hashofMessageInString {
		message = message.Set(m1)
	} else if m2Hash == hashofMessageInString {
		message = message.Set(m2)
	} else if m3Hash == hashofMessageInString {
		message = message.Set(m3)
	} else if m4Hash == hashofMessageInString {
		message = message.Set(m4)
	}

	return message
}

func getMessageHashInString(MessageInString string) string {

	sum := sha256.Sum256([]byte(MessageInString))
	sumInHex := fmt.Sprintf("%x", sum)
	return sumInHex

}
func Decrypt(p *big.Int, q *big.Int, C *big.Int, N *big.Int) (*big.Int, *big.Int,
	*big.Int, *big.Int) {

	mp := getSquareRoot(C, p)
	mq := getSquareRoot(C, q)

	// Finding values of yp and yq as per the equation yp.p + yq.q = 1
	// Using the Extended Euclidean algorithm to do the same

	pCopy := big.NewInt(0)
	qCopy := big.NewInt(0)
	pCopy = pCopy.Set(p)
	qCopy = qCopy.Set(q)

	_, yp, yq := extendedEuclideanAlgorithm(pCopy, qCopy)

	// Handling the 2 statements required to calculate r, -r
	ypPmq := big.NewInt(0)
	//ypPmq = ypPmq.Mul(p,mq)
	ypPmq = ypPmq.Mul(yp, p)

	ypPmq = ypPmq.Mul(ypPmq, mq)

	yqQmp := big.NewInt(0)
	yqQmp = yqQmp.Mul(q, mp)
	yqQmp = yqQmp.Mul(yqQmp, yq)

	ypPmqPlusyqQmp := big.NewInt(0)
	ypPmqPlusyqQmp = ypPmqPlusyqQmp.Add(ypPmq, yqQmp)

	if ypPmqPlusyqQmp.Cmp(big.NewInt(0)) == -1 {

		temp := big.NewInt(0)
		temp = temp.Abs(ypPmqPlusyqQmp)
		tempAbs := big.NewInt(0)

		tempAbs = tempAbs.Set(temp)
		temp = temp.Div(temp, N)
		temp = temp.Add(temp, big.NewInt(1))
		temp = temp.Mul(temp, N)
		ypPmqPlusyqQmp = ypPmqPlusyqQmp.Add(ypPmqPlusyqQmp, temp)

	} else {

		ypPmqPlusyqQmp = ypPmqPlusyqQmp.Mod(ypPmqPlusyqQmp, N)
	}

	NegativeypPmqPlusyqQmp := big.NewInt(0)
	NegativeypPmqPlusyqQmp = NegativeypPmqPlusyqQmp.Sub(N, ypPmqPlusyqQmp)

	// Handling the 2 statements required to calculate s, -s

	ypPmqMinusyqQmp := big.NewInt(0)
	ypPmqMinusyqQmp = ypPmqMinusyqQmp.Sub(ypPmq, yqQmp)

	if ypPmqMinusyqQmp.Cmp(big.NewInt(0)) == -1 {

		temp := big.NewInt(0)
		temp = temp.Abs(ypPmqMinusyqQmp)
		tempAbs := big.NewInt(0)

		tempAbs = tempAbs.Set(temp)

		temp = temp.Div(temp, N)
		temp = temp.Add(temp, big.NewInt(1))
		temp = temp.Mul(temp, N)

		ypPmqMinusyqQmp = ypPmqMinusyqQmp.Add(ypPmqMinusyqQmp, temp)

	} else {

		ypPmqMinusyqQmp = ypPmqMinusyqQmp.Mod(ypPmqMinusyqQmp, N)

	}

	NegativeypPmqMinusyqQmp := big.NewInt(0)
	NegativeypPmqMinusyqQmp = NegativeypPmqMinusyqQmp.Sub(N, ypPmqMinusyqQmp)

	return ypPmqPlusyqQmp, NegativeypPmqPlusyqQmp, ypPmqMinusyqQmp,
		NegativeypPmqMinusyqQmp

}

func getSquareRoot(C *big.Int, val *big.Int) *big.Int {

	temp := big.NewInt(0)
	temp = temp.Add(val, big.NewInt(1))
	temp = temp.Div(temp, big.NewInt(4))

	mpOrmq := squareAndMultiple(C, temp, val)

	return mpOrmq

}

func ConvertCipherTextToBigInt(CipherTextInString string) *big.Int {

	boolError := false
	Ciphertext := big.NewInt(0)

	Ciphertext, boolError = Ciphertext.SetString(CipherTextInString, 10)
	if boolError != true {
		fmt.Println(" Error in Set String")
	}

	return Ciphertext
}

func ExtractDetailsFromPrivateKeyFile(file_name string) (*big.Int, *big.Int,
	*big.Int) {

	FileContent, err := ioutil.ReadFile(file_name)
	N := big.NewInt(0)
	p := big.NewInt(0)
	q := big.NewInt(0)

	if err != nil {
		fmt.Println(" Error readng data from the file")
	} else {

		FileContentString := string(FileContent)

		FileContentString = FileContentString[1:(len(FileContentString) - 1)]
		FileContentSliced := strings.Split(FileContentString, ",")

		NinString := FileContentSliced[0]
		pinString := FileContentSliced[1]
		qinString := FileContentSliced[2]

		boolError := false
		N, boolError = N.SetString(NinString, 10)
		if boolError != true {
			fmt.Println(" Error in Set String")
		}

		p, boolError = p.SetString(pinString, 10)
		if boolError != true {
			fmt.Println(" Error in Set String")
		}

		q, boolError = q.SetString(qinString, 10)
		if boolError != true {
			fmt.Println(" Error in Set String")
		}

	}

	return N, p, q
}

func extendedEuclideanAlgorithm(a *big.Int, b *big.Int) (*big.Int, *big.Int,
	*big.Int) {
	d := big.NewInt(0)
	x := big.NewInt(0)
	y := big.NewInt(0)

	if b.Cmp(big.NewInt(0)) == 0 {

		d = d.Set(a)
		x = big.NewInt(1)
		y = big.NewInt(0)
		fmt.Println("First check return")
		return d, x, y
	}

	//  2 as per the Handbook of Applied cryptography
	x2 := big.NewInt(1)
	x1 := big.NewInt(0)
	y2 := big.NewInt(0)
	y1 := big.NewInt(1)

	// Setting big.Ints for the loop as we can't simple add (or) multiply
	// like Integers
	q := big.NewInt(0)
	r := big.NewInt(0)
	qb := big.NewInt(0)
	qx1 := big.NewInt(0)
	qy1 := big.NewInt(0)

	for (b.Cmp(big.NewInt(0))) == 1 {

		// 3.1 as per the Handbook of Applied cryptography
		q = q.Div(a, b)
		r = r.Sub(a, qb.Mul(q, b))
		x = x.Sub(x2, qx1.Mul(q, x1))
		y = y.Sub(y2, qy1.Mul(q, y1))

		// 3.2 as per the Handbook of Applied cryptography

		a = a.Set(b)
		b = b.Set(r)
		x2 = x2.Set(x1)
		x1 = x1.Set(x)
		y2 = y2.Set(y1)
		y1 = y1.Set(y)
	}

	// 4 as per the Handbook of Applied cryptography

	d = d.Set(a)
	x = x.Set(x2)
	y = y.Set(y2)

	return d, x, y
}
