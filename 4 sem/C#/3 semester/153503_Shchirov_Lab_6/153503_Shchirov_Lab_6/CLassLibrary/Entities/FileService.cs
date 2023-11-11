using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using _153503_Shchirov_Lab_6.Interfaces;

namespace CLassLibrary.Entities
{
    internal class FileService<T> : IFileService<T> where T : class
    {
        
    
        /*public IEnumerable<T> ReadFile<T>(string fileName) where T : class
        {
            string json = File.ReadAllText(fileName);
            return JsonSerializer.Deserialize<IEnumerable<T>>(json);
        }*/

        public IEnumerable<T> ReadFile(string fileName)
        {
            string json = File.ReadAllText(fileName);
            return JsonSerializer.Deserialize<IEnumerable<T>>(json);
        }

        /*public void SaveData<T>(IEnumerable<T> data, string fileName) where T : class
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
*/
        public void SaveData(IEnumerable<T> data, string fileName)
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
