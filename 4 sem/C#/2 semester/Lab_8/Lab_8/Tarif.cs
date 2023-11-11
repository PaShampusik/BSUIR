using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_8
{
    internal class Tarif
    {
        private string wherewego;
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
        public string Wherewego
        {
            get
            {
                return wherewego;
            }
            set
            {
                wherewego = value;
            }
        }

        public int GetPrice()
        {
            return price;
        }

        public Tarif(int cost, string where)
        {
            price = cost;
            wherewego = where;
        }
    }
}
