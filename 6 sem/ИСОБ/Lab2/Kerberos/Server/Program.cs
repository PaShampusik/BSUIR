using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class ServiceServer
{
    static void Main()
    {
        try
        {
            // Устанавливаем IP-адрес и порт сервера службы (Service Server)
            IPAddress ipAddress = IPAddress.Parse("127.0.0.1");
            int port = 8890;

            // Создаем TCP-сервер и прослушиваем указанный порт
            TcpListener listener = new TcpListener(ipAddress, port);
            listener.Start();

            Console.WriteLine("Сервер службы (Service Server) запущен. Ожидание подключений...");

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

                // Извлекаем зашифрованный TGS-серверный билет и TGS-сессионный ключ из запроса
                string[] requestParts = request.Split(':');
                string encryptedTgsServerTicket = requestParts[0];
                string encryptedTgsSessionKey = requestParts[1];

                // Расшифровываем TGS-серверный билет с использованием TGS-сессионного ключа
                string tgsServerTicket = DecryptWithKey(encryptedTgsServerTicket, encryptedTgsSessionKey);

                // Извлекаем логин и TGS-сессионный ключ из TGS-серверного билета
                string[] ticketParts = tgsServerTicket.Split(':');
                string username = ticketParts[0];
                string tgsSessionKey = ticketParts[1];

                // Генерируем серверный билет для доступа к службе
                string serviceTicket = GenerateServiceTicket(username, tgsSessionKey);

                // Формируем ответ для клиента, содержащий серверный билет
                byte[] responseBytes = Encoding.ASCII.GetBytes(serviceTicket);
                stream.Write(responseBytes, 0, responseBytes.Length);

                Console.WriteLine("Отправлен ответ клиенту");

                // Добавьте здесь код для обработки успешного получения серверного билета сервером службы

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

    // Фиктивная функция генерации серверного билета для доступа к службе
    static string GenerateServiceTicket(string username, string tgsSessionKey)
    {
        // Здесь вы можете реализовать вашу логику генерации серверного билета для доступа к службе.
        // В этом примере просто формируется строка "<username>:<tgsSessionKey>:<expirationTime>",
        // где <expirationTime> - время истечения срока действия билета.
        // Возвращается фиктивный серверный билет.
        DateTime expirationTime = DateTime.Now.AddMinutes(60);
        return $"{username}:{tgsSessionKey}:{expirationTime.ToString()}";
    }

    // Фиктивная функция расшифровки данных с использованием ключа
    static string DecryptWithKey(string data, string key)
    {
        // Здесь вы можете реализовать вашу логику расшифровки данных с использованием ключа.
        // В этом примере просто возвращается фиктивное расшифрованное представление данных.
        return data.Replace("encrypted_", "");
    }
}