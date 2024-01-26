class EncryptionProgram
{
    static string CaesarEncrypt(string text, int shift)
    {
        string encryptedText = "";

        foreach (char c in text)
        {
            if (char.IsLetter(c))
            {
                char encryptedChar = (char)(((c - 'a') + shift) % 26 + 'a');
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
                int shift = key[keyIndex] - 'a';
                char encryptedChar = (char)(((c - 'a' + shift) % 26) + 'a');
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

    static void Main()
    {
        string inputFileName = "input.txt";
        string outputFileNameCaesar = "output_caesar.txt";
        string outputFileNameVigenere = "output_vigenere.txt";

        menu:
        {
            Console.WriteLine("ШИФРОВАНИЕ РАБОТЕТ ТОЛЬКО С АНГЛИЙСКИМ ЯЗЫКОМ!");
            Console.WriteLine("Выберите алгоритм шифрования:");
            Console.WriteLine("1. Шифр Цезаря");
            Console.WriteLine("2. Шифр Виженера");
            Console.WriteLine("3. Выход из программы");
            Console.Write("Введите номер выбранного алгоритма: ");


            int choice = int.Parse(Console.ReadLine());

            Console.WriteLine();

            switch (choice)
            {
                case 1:
                    Console.Write("Введите сдвиг для шифра Цезаря: ");
                    int caesarShift = int.Parse(Console.ReadLine());

                    string inputText = File.ReadAllText(inputFileName);
                    string encryptedText = CaesarEncrypt(inputText.ToLower(), caesarShift);

                    File.WriteAllText(outputFileNameCaesar, encryptedText);

                    Console.WriteLine("Текст зашифрован и сохранен в файле " + outputFileNameCaesar);
                    goto menu;
                case 2:
                    Console.Write("Введите ключ для шифра Виженера: ");
                    string vigenereKey = Console.ReadLine().ToLower();

                    inputText = File.ReadAllText(inputFileName);
                    encryptedText = VigenereEncrypt(inputText.ToLower(), vigenereKey);

                    File.WriteAllText(outputFileNameVigenere, encryptedText);

                    Console.WriteLine("Текст зашифрован и сохранен в файле " + outputFileNameVigenere);
                    goto menu;
                case 3:
                    Console.WriteLine("Выход из программы");
                    return;
                default:
                    Console.WriteLine("Некорректный выбор алгоритма.");
                    break;
            }
        }
    }
}