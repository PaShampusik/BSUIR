using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_3.Entities
{
    internal class Client
    {
        List<Product> bought_products = new List<Product>();
        
        
        public string? Name
        {
            get;
            set;
        }

        public List<Product> get_bought_products()
        {
            return bought_products;
        }

        public Client(string name)
        {
            Name = name;
        }
        


    }
}
