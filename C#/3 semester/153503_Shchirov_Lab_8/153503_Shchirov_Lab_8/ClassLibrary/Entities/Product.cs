using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary.Entities
{
    public class Product
    {
        public string Id { get; set; }
        public string Name { get; set; }
        public bool IsOverdue { get; set; }
        
        public Product(string name, string id, bool isoverdue)
        {
            Id = id;
            Name = name;
            IsOverdue = isoverdue;             
        }

        public override string ToString()
        {
            return $"{Id} {Name} {IsOverdue}";
        }
        
        
    }
}
