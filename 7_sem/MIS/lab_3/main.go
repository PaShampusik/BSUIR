package main

import (
	crypt "crypto/rand"
	"fmt"
	"io/ioutil"
	"math/big"
)

func main() {
	publickeyFileName := "public.txt"
	privateKeyFileName := "private.txt"

	p := generateRabinPrimeNumber()
	q := generateRabinPrimeNumber()

	pCopy := big.NewInt(0)
	qCopy := big.NewInt(0)
	pCopy = pCopy.Set(p)
	qCopy = qCopy.Set(q)

	N := getPublicKey(pCopy, qCopy)

	WritePublicKeyInformationToFile(N, publickeyFileName)
	WritePrivateKeyInformationToFile(N, p, q, privateKeyFileName)

	MessageInString := "hello world"

	fmt.Println(MessageInString)

	Message := ConvertMessageToBigInt(MessageInString)

	P := ExtractDetailsFromPublicKeyFile(publickeyFileName)

	Ciphertext := Encrypt(Message, P)
	CipherTextInString := Ciphertext.String()

	hashofMessageInString := getMessageHashInString(MessageInString)

	output := CipherTextInString + hashofMessageInString
	// I've concatenated the SHA256 hash of the message with the ciphertext
	fmt.Println(" The ciphertext is ", output)

	// Rabin decrypt will produce 4 output messages

	N, p, q = ExtractDetailsFromPrivateKeyFile(privateKeyFileName)
	hashofMessageInString = CipherTextInString[(len(CipherTextInString) - 64):len(CipherTextInString)]
	CipherTextInString = CipherTextInString[0:(len(CipherTextInString) - 64)]
	Ciphertext = ConvertCipherTextToBigInt(CipherTextInString)

	m1, m2, m3, m4 := Decrypt(p, q, Ciphertext, N)

	message := compareMessageAndHash(m1, m2, m3, m4, hashofMessageInString)
	fmt.Println(" The Message is ", message)
}

func generateRabinPrimeNumber() *big.Int {

	temp := big.NewInt(0)
	p := big.NewInt(0)

	for true {
		p = getprimeNumber()
		temp = temp.Mod(p, big.NewInt(4))
		if temp.Cmp(big.NewInt(3)) == 0 {
			break
		}
	}

	return p
}

func WritePublicKeyInformationToFile(N *big.Int, publickeyFileName string) {

	NStringToWrite := N.String()
	leftBracket := "("
	rightBracket := ")"

	valueToWrite := leftBracket + NStringToWrite + rightBracket

	err := ioutil.WriteFile(publickeyFileName, []byte(valueToWrite), 0644)
	if err != nil {
		fmt.Println("Some Problem in writing to a file")
	}

}

func WritePrivateKeyInformationToFile(N *big.Int, p *big.Int, q *big.Int,
	privateKeyFileName string) {

	NStringToWrite := N.String()
	commaCharacter := ","
	leftBracket := "("
	rightBracket := ")"
	pStringToWrite := p.String()
	qStringToWrite := q.String()

	valueToWrite := leftBracket + NStringToWrite + commaCharacter + pStringToWrite +
		commaCharacter + qStringToWrite + rightBracket

	err := ioutil.WriteFile(privateKeyFileName, []byte(valueToWrite), 0644)
	if err != nil {
		fmt.Println("Some Problem in writing to a file")
	}

}

func getPublicKey(p *big.Int, q *big.Int) *big.Int {

	N := big.NewInt(0)
	N = N.Mul(p, q)
	return N
}

func getprimeNumber() *big.Int {
	randomNumber := generateNumber()

	accuracyFactor := big.NewInt(5)
	resultWhetherPrime := false

	for !resultWhetherPrime {
		randomNumber = generateNumber()
		resultWhetherPrime = isaPrimeNumber(randomNumber, accuracyFactor)
		if resultWhetherPrime {
			break
		}
	}
	return randomNumber

}

func generateNumber() *big.Int {

	n := 64
	b := make([]byte, n)
	_, y := crypt.Read(b)
	if y != nil {
		fmt.Println("Some error")
	}

	z := big.NewInt(0)
	randomNumber := z.SetBytes(b)

	return randomNumber
}

func squareAndMultiple(a *big.Int, b *big.Int, c *big.Int) *big.Int {

	binExp := fmt.Sprintf("%b", b)
	binExpLength := len(binExp)

	initialValue := big.NewInt(0)
	initialValue = initialValue.Mod(a, c)

	result := big.NewInt(0)
	result = result.Set(initialValue)

	for i := 1; i < binExpLength; i++ {

		interMediateResult := big.NewInt(0)
		interMediateResult = interMediateResult.Mul(result, result)
		result = result.Mod(interMediateResult, c)

		if byte(binExp[i]) == byte(49) {
			interResult := big.NewInt(0)
			interResult = interResult.Mul(result, initialValue)
			result = result.Mod(interResult, c)
		}
	}
	return result

}

func isaPrimeNumber(number *big.Int, accuracyFactor *big.Int) bool {

	if ((big.NewInt(0)).Mod(number, big.NewInt(2))).Cmp(big.NewInt(0)) == 0 {
		return false
	} else {

		varNumber := (big.NewInt(0)).Sub(number, big.NewInt(1))

		r := big.NewInt(2)
		// exponentitalR is 2powr(r)
		exponentitalR := big.NewInt(2)

		for true {

			x := big.NewInt(0)
			modValForX := big.NewInt(0)
			x, modValForX = x.DivMod(varNumber, exponentitalR, modValForX)

			if (modValForX.Cmp(big.NewInt(0))) == 0 {
				// Fixing value 10000000000 for calculation purpose
				// To resue the squareAndMultiple algorithm but not affect the modulo part
				r = r.Add(r, big.NewInt(1))
				exponentitalR = squareAndMultiplyWithoutMod(big.NewInt(2),
					r)

			} else {
				break
			}

		}

		r = r.Sub(r, big.NewInt(1))

		exponentitalR = squareAndMultiplyWithoutMod(big.NewInt(2),
			r)

		d := big.NewInt(0)
		d = d.Div(varNumber, exponentitalR)

		for i := big.NewInt(0); (i.Cmp(accuracyFactor)) == -1; i.Add(i, big.NewInt(1)) {

			millerRabinPrimalityTestResult := millerRabinPrimalityTest(number, d,
				r)

			if millerRabinPrimalityTestResult == false {
				return false
			}
		}
		return true
	}
}

func squareAndMultiplyWithoutMod(number *big.Int, exponent *big.Int) *big.Int {

	value := big.NewInt(1)

	binExp := fmt.Sprintf("%b", exponent)
	binExpLength := len(binExp)

	if exponent == big.NewInt(1) {
		return number
	}

	for i := 1; i < binExpLength; i++ {

		if byte(binExp[i]) == byte(49) {

			// temp := big.NewInt(0)
			value.Mul(value, value)
			value.Mul(value, number)

		} else {

			// temp := big.NewInt(0)
			value.Mul(value, value)

		}
	}

	return value

}

func millerRabinPrimalityTest(number *big.Int, d *big.Int,
	r *big.Int) bool {

	numberTemp := big.NewInt(0)
	numberTemp = (numberTemp.Sub(number, big.NewInt(4)))
	//aTemp := rand.Int63n(numberTemp.Int64()) + 2
	aTemp := int64(1000000000001)
	a := big.NewInt(aTemp)

	x := squareAndMultiple(a, d, number)

	numberMinusOne := (big.NewInt(0)).Sub(number, big.NewInt(1))
	if ((x.Cmp(big.NewInt(1))) == 0) || ((x.Cmp(numberMinusOne)) == 0) {
		return true
	}

	loopCount := (big.NewInt(0)).Sub(r, big.NewInt(1))

	for i := big.NewInt(0); (i.Cmp(loopCount)) == -1; i.Add(i,
		big.NewInt(1)) {

		xIntermediate := (big.NewInt(0)).Mul(x, x)

		x = x.Mod(xIntermediate, number)
		if x.Cmp(big.NewInt(1)) == 0 {
			return false
		}
		if (x.Cmp(numberMinusOne)) == 0 {
			return true
		}
	}
	return false

}
