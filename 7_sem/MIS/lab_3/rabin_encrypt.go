package main

import (
	"fmt"
	"io/ioutil"
	"math/big"
)

func Encrypt(Message *big.Int, N *big.Int) *big.Int {

	exponentationComponent := big.NewInt(2)
	Ciphertext := squareAndMultiple(Message, exponentationComponent, N)
	return Ciphertext

}

func ExtractDetailsFromPublicKeyFile(file_name string) *big.Int {

	// In Rabin's crypto-system, N is the public key
	FileContent, err := ioutil.ReadFile(file_name)
	N := big.NewInt(0)

	if err != nil {
		fmt.Println(" Error readng data from the file")
	} else {

		NinString := string(FileContent)
		// Below statements to remove left and right bracket from the string
		NinString = NinString[1:(len(NinString) - 1)]

		boolError := false
		N, boolError = N.SetString(NinString, 10)
		if boolError != true {
			fmt.Println(" Error in Set String")
		}

	}
	return N
}

func ConvertMessageToBigInt(MessageInString string) *big.Int {

	boolError := false
	Message := big.NewInt(0)

	Message, boolError = Message.SetString(MessageInString, 10)
	if boolError != true {
		fmt.Println(" Error in Set String")
	}

	return Message
}
