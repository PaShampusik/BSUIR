using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_8
{
    internal class DiscPrice
    {
        private int price;
        private int discount;

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

        public int Discount
        {
            get
            {
                return discount;
            }
            set
            {
                discount = value;
            }
        }

        public DiscPrice(int cost, int disc)
        {
            price = cost;
            discount = disc;
        }

        public int GetPrice()
        {
            double disc = Convert.ToDouble(discount) / 100.0;
            return price - Convert.ToInt32((Convert.ToDouble(price) * disc));
        }
    }
}
