using Kerberos_lab_2_.Models;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;

namespace Kerberos_lab_2_.Servers
{
    internal class ClientServer
    {
        private const string _key = Configuration.ClientKey;
        private string _login = "Pavel Shchirov";
        public async Task Listen(CancellationTokenSource cancelTokenSource)
        {
            UdpClient udpClient = new(Configuration.ClientPort);

            //  1)))  Отправляем запрос для аутентификации (посылает серверу аутентификации AS свой идентификатор) 
            
            AuthServerRequest authData = new(_login, 600);
            ResponseData<AuthServerRequest> authRequest = new() { Data = authData, IsSuccess = true };

            byte[] data = Encoding.UTF8.GetBytes(JsonSerializer.Serialize(authRequest));

            await udpClient.SendAsync(data, Configuration.AuthEP);
            await Console.Out.WriteLineAsync("*********************************************************************************\n" +
                "Клиент отправил запрос на аутентификацию с принипалом Pavel Shchirov и временем жизни 10 минут");
            var response = await udpClient.ReceiveAsync();
            
            ResponseData<AuthServerResponse>? authResponse 
                = JsonSerializer.Deserialize<ResponseData<AuthServerResponse>>(Encoding.UTF8.GetString(response.Buffer));

            if(authResponse is null)
            {
                cancelTokenSource.Cancel();
                await Console.Out.WriteLineAsync("Клиент. Ошибка при получении ответа");
                return;
            }

            if(!authResponse.IsSuccess)
            {
                cancelTokenSource.Cancel();
                await Console.Out.WriteLineAsync("Клиент. Неуспешный ответ при аутентификации: " + authResponse.ErrorMessage);
                return;
            }




            /* 2)))  Удачный ответ на аутентификацию   
               (сервер аутентификации AS, проверив, что клиент C имеется в его базе, возвращает ему билет для доступа к 
                серверу выдачи разрешений и ключ для взаимодействия с сервером выдачи разрешений. Вся посылка зашифрована на ключе клиента C.)*/
           
            byte[] tgtByKDCkey = authResponse.Data!.TGSEncryptByKDCKey;
            TicketGrantingTicket tgt = JsonSerializer.Deserialize<TicketGrantingTicket>(authResponse.Data.TGSEncryptByClientKey.GetJsonString(_key))!;
            string sessionKey = tgt.SessionKey;

            await Console.Out.WriteLineAsync("\n*********************************************************************************\n" +
                "Клиент получил ответ от сервера аутентификации." +
                "\nTGT билет, зашифрованный ключем KDC: " + tgtByKDCkey.GetJsonString() +
                "\nСессионный ключ: " + sessionKey);





            //  3))) Отправляем запрос на получение разрешения доступа к сервису //
            /* Он пересылает полученный от AS билет, зашифрованный на ключе KAS_TGS, и аутентификационный блок, содержащий идентификатор c и метку 
             * времени, показывающую, когда была сформирована посылка.*/

            Authenticator authenticator = new(_login);
            //Шифруем аутентификатор сессионным ключем
            byte[] encryptAuth = JsonSerializer.Serialize(authenticator).GetDesEncryptBytes(sessionKey);

            await Console.Out.WriteLineAsync("\n*********************************************************************************\n" +
                "Клиент отправляет запрос на разрешение доступа к сервису (TGS)." +
                "\nЗашифрованный аутентификатор: " + encryptAuth.GetJsonString() +
                "\nПринципал сервиса: service 1");
            TGServerRequest tgsRequest = new("service 1", tgtByKDCkey, encryptAuth);
            await udpClient.SendAsync(new ResponseData<TGServerRequest>() { Data = tgsRequest, IsSuccess = true }.GetBytes(), Configuration.TGServerEP);
            
            response = await udpClient.ReceiveAsync();
            ResponseData<TGServerResponse>? tgsResponse
                = JsonSerializer.Deserialize<ResponseData<TGServerResponse>>(response.Buffer.GetJsonString());

            if (tgsResponse is null)
            {
                cancelTokenSource.Cancel();
                await Console.Out.WriteLineAsync("Клиент. Ошибка при получении ответа");
                return;
            }

            if (!tgsResponse.IsSuccess)
            {
                cancelTokenSource.Cancel();
                await Console.Out.WriteLineAsync("Клиент. Неуспешный ответ при аутентификации: " + tgsResponse.ErrorMessage);
                return;
            }




            //     4)))     Удачный ответ от TGS        //
            /* сервер выдачи разрешений TGS посылает клиенту C ключ шифрования и билет, необходимые для доступа к серверу SS. Структура билета такая же, 
             * как на шаге 2): идентификатор того, кому выдали билет; идентификатор того, для кого выдали билет; отметка времени; период действия; ключ шифрования.*/
            
            ServiceTicket st = JsonSerializer.Deserialize<ServiceTicket>(tgsResponse.Data!.STEncryptBySessionKey.GetJsonString(sessionKey))!;
            string sessinServiceKey = st.ServiceSessionKey;
            byte[] encryptST = tgsResponse.Data!.STEncryptByServiceKey;

            await Console.Out.WriteLineAsync("\n*********************************************************************************\n" +
                "Клиент получил ответ от TGS." +
                "\nST билет, зашифрованный ключем сервиса: " + encryptST.GetJsonString() +
                "\nСессионный ключ сервиса: " + sessinServiceKey);



            // 5))))  Отправляем запрос сервису на получение данных  //
            /* Клиент C посылает билет, полученный от сервера выдачи разрешений, и свой аутентификационный блок серверу SS, с которым хочет установить сеанс защищенного
             * взаимодействия. Предполагается, что SS уже зарегистрировался в системе и распределил с сервером TGS ключ шифрования KTGS_SS. */
           
            //Шифруем сессионным ключем сервиса
            encryptAuth = JsonSerializer.Serialize(new Authenticator(_login)).GetDesEncryptBytes(sessinServiceKey);
            AppServerRequest serviceRequest = new(encryptAuth, encryptST);

            await Console.Out.WriteLineAsync("\n*********************************************************************************\n" +
                "Клиент отправляет запрос на разрешение доступа к сервису (SS)." +
                "\nЗашифрованный аутентификатор: " + encryptAuth.GetJsonString() +
                "\nЗашифрованный ST: " + encryptST.GetJsonString());

            await udpClient.SendAsync(new ResponseData<AppServerRequest>() { Data = serviceRequest, IsSuccess = true}.GetBytes(), Configuration.ServiceServerEP);
            response = await udpClient.ReceiveAsync();

            ResponseData<AppServerResponse>? appResponse = JsonSerializer.Deserialize<ResponseData<AppServerResponse>>(response.Buffer);

            if (appResponse is null)
            {
                cancelTokenSource.Cancel();
                await Console.Out.WriteLineAsync("Клиент. Ошибка при получении ответа от сервиса");
                return;
            }

            if (!appResponse.IsSuccess)
            {
                cancelTokenSource.Cancel();
                await Console.Out.WriteLineAsync("Клиент. Неуспешный ответ от сервиса: " + appResponse.ErrorMessage);
                return;
            }




            //   6)))     Удачный ответ от сервиса       //
            /* SS берет отметку времени из аутентификационного блока C, изменяет ее заранее определенным образом (увеличивает на 1), шифрует на ключе KC_SS и возвращает C.*/
           
            string message = JsonSerializer.Deserialize<string>(appResponse.Data!.ServiceResEncryptByServiceSessionKey.GetJsonString(sessinServiceKey))!;
            await Console.Out.WriteLineAsync("\n*********************************************************************************\n" +
                "Клиент получил ответ от сервиса." +
                "\nПолученное сообщение: " + message);
            cancelTokenSource.Cancel();
        }
    }
}
