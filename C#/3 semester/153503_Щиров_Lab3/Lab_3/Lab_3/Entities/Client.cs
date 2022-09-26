using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_3.Entities
{
    internal class Client
    {
        public List<Product> bought_products = new List<Product>();
        
        
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

        public int Get_total_cost()
        {
            int sum = 0;
            foreach (var product in bought_products)
            {
                sum += Convert.ToInt32(product.Price);
            }
            return sum;
        }
        


    }
}
