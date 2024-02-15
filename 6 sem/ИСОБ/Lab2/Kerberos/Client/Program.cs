using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class Client
{
    static void Main()
    {
        try
        {
            // Устанавливаем IP-адрес и порт сервера аутентификации (AS)
            IPAddress ipAddress = IPAddress.Parse("127.0.0.1");
            int port = 8888;

            // Создаем TCP-клиента и подключаемся к серверу AS
            TcpClient client = new TcpClient();
            client.Connect(ipAddress, port);

            Console.WriteLine("Подключено к серверу аутентификации");

            // Запрашиваем у пользователя логин и пароль
            Console.Write("Введите логин: ");
            string username = Console.ReadLine();
            Console.Write("Введите пароль: ");
            string password = Console.ReadLine();

            // Формируем запрос на сервер AS
            string request = username + ":" + password;

            // Отправляем запрос на сервер AS
            byte[] data = Encoding.ASCII.GetBytes(request);
            NetworkStream stream = client.GetStream();
            stream.Write(data, 0, data.Length);

            Console.WriteLine("Запрос отправлен на сервер аутентификации");

            // Получаем ответ от сервера AS
            byte[] buffer = new byte[1024];
            int bytesRead = stream.Read(buffer, 0, buffer.Length);
            string response = Encoding.ASCII.GetString(buffer, 0, bytesRead);

            if (response == "Success")
            {
                Console.WriteLine("Аутентификация прошла успешно!");
                // Добавьте здесь код для обработки успешной аутентификации
            }
            else
            {
                Console.WriteLine("Ошибка аутентификации. Неверный логин или пароль.");
            }

            // Закрываем соединение с сервером AS
            stream.Close();
            client.Close();
        }
        catch (Exception ex)
        {
            Console.WriteLine("Ошибка: " + ex.Message);
        }

        Console.WriteLine("Нажмите любую клавишу для выхода...");
        Console.ReadKey();
    }
}