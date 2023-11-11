using System.Net.Http.Headers;
using System.Threading.Tasks;
using System.Net.Http;
using System;
using ClassLibrary.Entities;
using ClassLibrary.Service;
using System.Runtime.CompilerServices;

class Program
{
    public static async Task Main(string[] args)
    {
        List<Product> list_of_products = new List<Product>();
        Random rand = new Random();

        string? thread_name = Thread.CurrentThread.Name;
        Console.WriteLine($"{thread_name} is started");
        for (int i = 0; i < 10; i++)
        {
            bool isOverdue = rand.Next(0, 2) == 1;
            string id = "";
            for (int j = 0; j < 8; j++)
            {
                id += rand.Next(10).ToString();
            }
            string name = "";
            for (int j = 0; j < 8; j++)
            {
                name += (char)rand.Next(65, 90);
            }
            list_of_products.Add(new Product(name, id, isOverdue));
        }
        object obj = new object();

        Progress<string> progress = new();

        progress.ProgressChanged += Progress_ProgressChanged;
        

        StreamService<Product> streamService = new StreamService<Product>();
        MemoryStream memoryStream = new MemoryStream();

        var m1 = streamService.WriteToStreamAsync(memoryStream, list_of_products);
        Thread.Sleep(200);
        var m2 = streamService.CopyFromStreamAsync(memoryStream, "products.txt");

        Task.WaitAll(m1, m2);

        /*var count = await streamService.GetStatisticsAsync("products.txt", x => x.IsOverdue);*/


        var count = await streamService.GetStatisticsAsync("products.txt", x => x.IsOverdue);
        lock (obj)
        {
            Console.WriteLine("Count of overdue products: " + Convert.ToInt32(count));
        }

    }

    private static void Progress_ProgressChanged(object? sender, string e)
    {
        throw new NotImplementedException();
    }
}