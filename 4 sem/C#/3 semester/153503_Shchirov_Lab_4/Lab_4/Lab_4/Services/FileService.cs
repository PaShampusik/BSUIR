using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab_4.Interfaces;

namespace Lab_4.Services
{
    internal class FileService<T> : IFileService<T>
    {
        public IEnumerable<T?> ReadFile(string fileName)
        {
            using (BinaryReader reader = new BinaryReader(File.Open(fileName, FileMode.Open)))
            {
                while (reader.PeekChar() > -1)
                {
                    yield return (T?)Activator.CreateInstance(typeof(T), reader);
                }
            }
        }

        public void SaveData(IEnumerable<T> data, string fileName)
        {
            
            using (BinaryWriter writer = new BinaryWriter(File.Open(fileName, FileMode.OpenOrCreate)))
            {

                foreach (var item in data)
                {
                    writer.Write(item.ToString());
                }

            }
        }
    }
}
