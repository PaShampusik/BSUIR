using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_8
{
    internal class NoDiscPrice
    {
        private int price;

        public int Price
        {
            get
            {
                return price;
            }
            set
            {
                price = value;
            }
        }

        
        public NoDiscPrice(int cost)
        {
            price = cost;
        }

        public int GetPrice()
        {

            return price;
        }
    }
}
