using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace ClassLibrary.Service
{
    public class StreamService<T> : IProgress<string>
    {
        public object? obj
        {
            get; set;
        }
        public StreamService()
        {
            obj = new object();
        }
        public async Task WriteToStreamAsync(Stream stream, IEnumerable<T> data)
        {
            var name = Environment.CurrentManagedThreadId;
            Report($"Writing is started in stream {name}!");
            await Task.Run(() =>
            {
                lock (obj)
                {
                    
                    stream.Seek(0, SeekOrigin.Begin);
                    StreamWriter writer = new StreamWriter(stream);

                    foreach (var item in data)
                    {
                        writer.WriteLine(JsonSerializer.Serialize(item));
                        Report(item.ToString());
                    }
                    //writer.Flush();
                }
            });
            Report("Writing to stream successfully endded!");

        }

        public async Task CopyFromStreamAsync(Stream stream, string fileName)
        {
            
            var name = Environment.CurrentManagedThreadId;
            Report($"Copiyng is started in thread {name}!");
            await Task.Run(() =>
            {
                lock (obj)
                {
                    
                    
                        stream.Seek(0, SeekOrigin.Begin);
                        using (StreamReader reader = new StreamReader(stream))
                        {
                            using (StreamWriter writer = new StreamWriter(fileName))
                            {

                                while (!reader.EndOfStream)
                                {
                                    writer.WriteLine(reader.ReadLine());
                                }
                            }
                        }
                    
                    
                }

            });
            Report("Copying to file successfully ended!");
        }

        public async Task<int> GetStatisticsAsync(string fileName, Func<T, bool> filter)
        {
            var count = 0;
            using (var reader = new StreamReader(fileName))
            {
                
                    while (!reader.EndOfStream)
                    {
                        var line = reader.ReadLineAsync();
                        string str = await line;
                        Task.WaitAll(line);
                        var item = JsonSerializer.Deserialize<T>(str);
                        if (filter(item))
                        {
                            count++;
                        }
                    }
                
            }
            return count;


        }

        public void Report(string value)
        {
            Console.WriteLine(value);
        }
    }
}
