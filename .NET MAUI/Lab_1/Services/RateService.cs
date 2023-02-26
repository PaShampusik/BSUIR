using Lab_1.Entities;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace Lab_1.Services
{
    public class RateService : IRateService
    {
        HttpClient httpClient { get; init; }
        public RateService(HttpClient _httpclient)
        {
            httpClient = _httpclient;
        }
        public IEnumerable<Rate> GetRates(DateTime date)
        {
            var request = new HttpRequestMessage(HttpMethod.Get, $"?ondate={date.ToString("yyyy-M-d")}&periodicity=0");
            var msg = new HttpResponseMessage();
            Task<HttpResponseMessage> task = Task.Run(() => httpClient.Send(request));

            msg = task.Result;

            msg.EnsureSuccessStatusCode();
            if(msg.Content == null)
            {
                return null;
            }
            var jsonText = Task.Run(async () => await msg.Content.ReadAsStringAsync());
            IEnumerable<Rate> rates = JsonConvert.DeserializeObject<IEnumerable<Rate>>(jsonText.Result);
            return rates;
        }
    }
}
