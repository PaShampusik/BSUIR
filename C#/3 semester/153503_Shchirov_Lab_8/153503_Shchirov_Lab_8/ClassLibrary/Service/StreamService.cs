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
        public async Task WriteToStreamAsync(Stream stream, IEnumerable<T> data)
        {
            object locker = new();
            stream.Seek(0, SeekOrigin.Begin);
            Report($"Writing is started!");
            await Task.Run(() =>
            {
                lock (locker)
                {
                    stream.Seek(0, SeekOrigin.Begin);
                    StreamWriter writer = new StreamWriter(stream);

                    foreach (var item in data)
                    {
                        writer.WriteLine(JsonSerializer.Serialize(item));
                        Report(item.ToString());
                    }
                    writer.Flush();
                }
            });
            Report("Writing to stream successfully endded!");

        }

        public async Task CopyFromStreamAsync(Stream stream, string fileName)
        {
            object locker = new();

            Report($"Copiyng is started!");
            await Task.Run(() =>
            {
                lock (locker)
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
            using (var reader = new StreamReader(fileName))
            {
                var count = 0;
                while (!reader.EndOfStream)
                {
                    var line = await reader.ReadLineAsync();
                    var item = JsonSerializer.Deserialize<T>(line);
                    if (filter(item))
                    {
                        count++;
                    }
                }
                return count;
            }
        }

        public void Report(string value)
        {
            Console.WriteLine(value);
        }
    }
}
