using Lab_1.Entities;
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
        HttpClient httpCLient;
        public RateService(HttpClient _httpclient)
        {
            HttpClient httpClient = _httpclient;
        }
        public IEnumerable<Rate> GetRates(DateTime date)
        {
            string uri = "https://www.nbrb.by/api/exrates/rates?ondate=" + date.Year + "-" + date.Month + "-" + date.Day + "&periodicity=0";

            var msg = new HttpResponseMessage();
            Task<HttpResponseMessage> task = Task.Run(async () => await httpCLient.GetAsync(uri));
 
            msg = task.Result;

            msg.EnsureSuccessStatusCode();

            var jsonResponse = msg.Content.ReadAsStringAsync();
            return (IEnumerable<Rate>)jsonResponse;
        }
    }
}
