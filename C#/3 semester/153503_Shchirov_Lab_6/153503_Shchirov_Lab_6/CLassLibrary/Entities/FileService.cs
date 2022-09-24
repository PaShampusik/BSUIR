using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace CLassLibrary.Entities
{
    internal class FileService
    {
        public IEnumerable<T> ReadFile<T>(string fileName) where T : class
        {
            string json = File.ReadAllText(fileName);
            return JsonSerializer.Deserialize<IEnumerable<T>>(json);
        }

        public void SaveData<T>(IEnumerable<T> data, string fileName) where T : class
        {
            string json = JsonSerializer.Serialize(data);
            Console.WriteLine(json);
            if (File.Exists(fileName))
            {
                File.Delete(fileName);
                File.Create(fileName);

            }
            else
            {
                File.Create(fileName);
            }
            File.WriteAllText(fileName, json);
        }
    }
}
