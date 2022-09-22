using Lab_4.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_4.Entities
{
    internal class SuperHeroes : FileService<SuperHeroes>
    {
        public string? Name { get; set; }

        public bool? FromEarth  { get; set; }

        public int? Age { get; set; }
        
        public SuperHeroes()
        {
            Name = null;
            Age = null;
            FromEarth = null;
        }
        
        public SuperHeroes(string name, int age, bool fromearth)
        {
            Name = name;
            Age = age;
            FromEarth = fromearth;           
        }

        public SuperHeroes(BinaryReader reader)
        {
            var buf = reader.ReadString();
            string[] data = buf.Split(' ');
            Name = data[0];
            Age = int.Parse(data[1]);
            FromEarth = bool.Parse(data[2]);
        }

        public string get_data()
        {
            return $"{Name} {Age} {FromEarth}";
        }
        public override string ToString()
        {
            return $"{Name} {Age} {FromEarth}";
        }
        public  string String()
        {
            return $"{Name}";
        }
    }
}
