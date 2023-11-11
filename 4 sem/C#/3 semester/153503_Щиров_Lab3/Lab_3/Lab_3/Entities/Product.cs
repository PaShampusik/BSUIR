using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_3.Entities
{
    internal class Product
    {
        public string? Name 
        { 
            get; 
            set; 
        }
        public int? Price 
        { 
            get; 
            private set; 
        }

        public Product(string name, int price)
        {
            Name = name;
            Price = price;
        }

    }
}
