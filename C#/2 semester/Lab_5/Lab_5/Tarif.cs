using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_5
{
    public class Tarif
    {
        private int price;
        private string wheretogo;

        public Tarif(string wheretogo, int price)
        {
            this.price = price;
            this.wheretogo = wheretogo;
        }
        
        public int Price
        {
            get { return price; }
            set { price = value; }
        }

        public string WhereToGo
        {
            get { return wheretogo; }
            set { wheretogo = value; }
        }
    }
}
