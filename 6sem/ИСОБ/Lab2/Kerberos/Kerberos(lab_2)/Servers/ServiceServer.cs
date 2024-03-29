﻿using System.Net.Sockets;
using System.Net;
using Kerberos_lab_2_.Models;
using System.Text.Json;
using System.Text;

namespace Kerberos_lab_2_.Servers
{
    internal class ServiceServer
    {
        private string _message = "Hello from service!";
        private string _key = Configuration.ServiceKey;

        public async Task Listen(CancellationToken token)
        {
            UdpClient udpClient = new(Configuration.ServiceServerEP);
            while (true)
            {
                if (token.IsCancellationRequested)
                    return;

                //Ожидаем и получаем сообщение
                var result = await udpClient.ReceiveAsync(token);
                string message = result.Buffer.GetJsonString();
                IPEndPoint endPoint = result.RemoteEndPoint;

                //Пытаемся его разобрать
                ResponseData<AppServerRequest>? appRequest
                    = JsonSerializer.Deserialize<ResponseData<AppServerRequest>>(message);

                //Если не получилось десериализовать
                if (appRequest is null)
                {
                    await Console.Out.WriteLineAsync("Сервер сервиса. Не получилось преобразовать полученный запрос");
                    continue;
                }

                AppServerRequest data = appRequest.Data!;

                //Расшифровываем tgt при помощи ключа kdc
                ServiceTicket tgs = JsonSerializer.Deserialize<ServiceTicket>(data.TGSEncryptByServiceKey.GetJsonString(_key))!;
                string serviceSessionKey = tgs.ServiceSessionKey;

                Authenticator userAuth = JsonSerializer.Deserialize<Authenticator>(data.AuthEncryptBySessionServiceKey.GetJsonString(serviceSessionKey))!;


                if (tgs.TimeStamp.AddSeconds(tgs.Duration) < DateTime.Now   //Если билет протух
                    || tgs.Principal != userAuth.Principal)                 //Если принципалы не совпадают
                {
                    byte[] notFound = JsonSerializer.Serialize(
                            new ResponseData<AppServerResponse>()
                            { IsSuccess = false, ErrorMessage = "Билет не действителен" }).GetBytes();

                    await udpClient.SendAsync(notFound, endPoint);
                    continue;
                } 

                

                await udpClient.SendAsync(new ResponseData<string>() { Data = _message, IsSuccess = true }.GetBytes(), endPoint);
            }
        }
    }
}
