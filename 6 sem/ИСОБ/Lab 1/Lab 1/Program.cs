using System.Text.Json.Nodes;
using System.Text.RegularExpressions;

class EncryptionProgram
{
    static string CaesarEncrypt(string text, int shift)
    {
        string encryptedText = "";

        foreach (char c in text)
        {
            if (char.IsLetter(c))
            {
                char encryptedChar;
                int lettershift = c - 'a';
                if (lettershift + shift > 25)
                {
                    encryptedChar = (char)('a' + (lettershift + shift) % 26);
                }
                else
                {
                    encryptedChar = (char)(c + shift);
                }
                encryptedText += encryptedChar;
            }
            else
            {
                encryptedText += c;
            }
        }

        return encryptedText;
    }

    static string VigenereEncrypt(string text, string key)
    {
        string encryptedText = "";
        int keyIndex = 0;

        foreach (char c in text)
        {
            if (char.IsLetter(c))
            {
                char encryptedChar;
                int lettershift = c - 'a';
                int shift = key[keyIndex] - 'a';
                if (lettershift + shift > 26)
                {
                    encryptedChar = (char)('a' + (lettershift + shift) % 26);
                }
                else
                {
                    encryptedChar = (char)(c + shift);
                }
                encryptedText += encryptedChar;

                keyIndex = (keyIndex + 1) % key.Length;
            }
            else
            {
                encryptedText += c;
            }
        }

        return encryptedText;
    }

    static string CaesarDecrypt(string text, int shift)
    {
        string decryptedText = "";

        foreach (char c in text)
        {
            if (char.IsLetter(c))
            {
                char decryptedChar = (char)(c - shift);
                if (decryptedChar < 'a')
                {
                    decryptedChar = (char)(decryptedChar + 26);
                }
                decryptedText += decryptedChar;
            }
            else
            {
                decryptedText += c;
            }
        }

        return decryptedText;
    }

    static string VigenereDecrypt(string text, string key)
    {
        string decryptedText = "";
        int keyIndex = 0;

        foreach (char c in text)
        {
            if (char.IsLetter(c))
            {
                int shift = key[keyIndex] - 'a';
                char decryptedChar = (char)(c - shift % 26);
                if (decryptedChar < 'a'){
                    decryptedChar = (char)(decryptedChar + 26);
                }
                decryptedText += decryptedChar;

                keyIndex = (keyIndex + 1) % key.Length;
            }
            else
            {
                decryptedText += c;
            }
        }

        return decryptedText;
    }

    static bool ValidText(string text)
    {
        Regex rx = new Regex(@"^[A-Za-z\s]+$");
        return rx.IsMatch(text);
    }

    static void Main()
    {
        string inputFileName = "input.txt";
        string outputFileNameCaesar = "output_caesar.txt";
        string outputFileNameVigenere = "output_vigenere.txt";

    menu:
        {
            Console.WriteLine("Выберите алгоритм шифрования:");
            Console.WriteLine("1. Шифр Цезаря");
            Console.WriteLine("2. Шифр Виженера");
            Console.WriteLine("3. Расшифровка шифра Цезаря");
            Console.WriteLine("4. Расшифровка шифра Вижинера");
            Console.WriteLine("5. Выход из программы");
            Console.Write("Введите номер выбранного алгоритма: ");


            string choice = Console.ReadLine();

            Console.WriteLine();

            switch (choice)
            {
                case "1":
                    Console.Write("Введите сдвиг для шифра Цезаря: ");
                    int caesarShift = int.Parse(Console.ReadLine());

                    string inputText = File.ReadAllText(inputFileName);
                    string encryptedText = CaesarEncrypt(inputText.ToLower(), caesarShift);

                    File.WriteAllText(outputFileNameCaesar, encryptedText);

                    Console.WriteLine("Текст зашифрован и сохранен в файле " + outputFileNameCaesar);
                    Console.WriteLine("Зашифрованный текст: " + encryptedText);
                    goto menu;
                case "2":
                    inputText = File.ReadAllText(inputFileName);
                    if (ValidText(inputText))
                    {
                        Console.Write("Введите ключ для шифра Виженера: ");
                        string vigenereKey = Console.ReadLine().ToLower();
                        if (ValidText(vigenereKey))
                        {


                            encryptedText = VigenereEncrypt(inputText.ToLower(), vigenereKey);

                            File.WriteAllText(outputFileNameVigenere, encryptedText);

                            Console.WriteLine("Текст зашифрован и сохранен в файле " + outputFileNameVigenere);
                            Console.WriteLine("Зашифрованный текст: " + encryptedText);
                        }
                        else
                        {
                            Console.WriteLine("Ключ для шифра вижинера должен быть на английском языке");
                        }
                    }
                    else
                    {
                        Console.WriteLine("Неправильные входные данные, текст должен быть на английском языке\n");
                    }
                    goto menu;
                case "3":
                    Console.Write("Введите сдвиг для шифра Цезаря: ");
                    int caesarUnshift = int.Parse(Console.ReadLine());
                    inputText = File.ReadAllText(outputFileNameCaesar);
                    Console.WriteLine("Расшифрованный текст методом Цезаря " + CaesarDecrypt(inputText, caesarUnshift));
                    goto menu;
                case "4":
                    Console.Write("Введите ключ для шифра Виженера: ");
                    string vigenereKeyD = Console.ReadLine().ToLower();
                    if (ValidText(vigenereKeyD))
                    {
                        inputText = File.ReadAllText(outputFileNameVigenere);
                        Console.WriteLine("Расшифрованный текст методом Вижинера " + VigenereDecrypt(inputText, vigenereKeyD));
                    }
                    goto menu; ;
                case "5":
                    Console.WriteLine("Выход из программы");
                    return;
                default:
                    Console.WriteLine("Некорректный выбор алгоритма.");
                    goto menu;
            }
        }
    }
}