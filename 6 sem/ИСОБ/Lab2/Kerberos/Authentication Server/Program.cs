using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class AuthenticationServer
{
    static void Main()
    {
        try
        {
            // Устанавливаем IP-адрес и порт сервера аутентификации (AS)
            IPAddress ipAddress = IPAddress.Parse("127.0.0.1");
            int port = 8888;

            // Создаем TCP-сервер и прослушиваем указанный порт
            TcpListener listener = new TcpListener(ipAddress, port);
            listener.Start();

            Console.WriteLine("Сервер аутентификации запущен. Ожидание подключений...");

            while (true)
            {
                // Принимаем входящее подключение от клиента
                TcpClient client = listener.AcceptTcpClient();

                Console.WriteLine("Подключен клиент");

                // Получаем данные от клиента
                byte[] buffer = new byte[1024];
                NetworkStream stream = client.GetStream();
                int bytesRead = stream.Read(buffer, 0, buffer.Length);
                string request = Encoding.ASCII.GetString(buffer, 0, bytesRead);

                Console.WriteLine("Получен запрос от клиента: " + request);

                // Извлекаем логин и пароль из запроса
                string[] credentials = request.Split(':');
                string username = credentials[0];
                string password = credentials[1];

                // Проверяем логин и пароль
                if (AuthenticateUser(username, password))
                {
                    // Отправляем клиенту ответ об успешной аутентификации
                    byte[] response = Encoding.ASCII.GetBytes("Success");
                    stream.Write(response, 0, response.Length);

                    Console.WriteLine("Аутентификация прошла успешно для пользователя " + username);

                    // Добавьте здесь код для генерации TGT и ключа для взаимодействия с сервером TGS
                }
                else
                {
                    // Отправляем клиенту ответ о неудачной аутентификации
                    byte[] response = Encoding.ASCII.GetBytes("Failure");
                    stream.Write(response, 0, response.Length);

                    Console.WriteLine("Ошибка аутентификации для пользователя " + username);
                }

                // Закрываем соединение с клиентом
                stream.Close();
                client.Close();
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine("Ошибка: " + ex.Message);
        }
    }

    // Фиктивная функция аутентификации пользователя
    static bool AuthenticateUser(string username, string password)
    {
        // Здесь вы можете реализовать вашу логику аутентификации, например, проверку логина и пароля в базе данных или другом источнике данных.
        // В этом примере аутентификация всегда считается успешной, если логин и пароль не пустые.
        return !string.IsNullOrEmpty(username) && !string.IsNullOrEmpty(password);
    }
}