using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_6
{
    internal sealed class Sup : Bludo
    {
       
        public bool Hot {
            get { return Hot; }
            set { Hot = value; }
        }
        public double Weight
        {
            get
            {
                return Weight;
            }
            set
            {
                if (value > 0)
                {
                    Weight = value;
                }
                else
                {
                    throw new Exception("Вес не может быть отрицательным");
                }
            }
        }
        public String Name
        {
            get
            {
                return Name;
            }
            set
            {
                Name = value;
            }
        }
        public double Price
        {
            get
            {
                return Price;
            }
            set
            {
                Price = value;
            }
        }

        public Sup(String name = "Borsch", double price = 2, double weight = 300, bool hot = true)
        {
            Name = name;
            Price = price;
            Weight = weight;
            Hot = hot;
        }
        
        public override string Sustain()
        {
            if (Hot)
            {
                return "Sup is hot";
            }
            else
            {
                return "Sup is not hot";
            }
        }

        public override string GetName()
        {
            return Name;
        }
        public override double GetWeight()
        {
            return Weight;
        }
        public override double GetPrice()
        {
            return Price;
        }
        public override double WeightToPrice()
        {
            return Weight / Price;
        }
    }
}



