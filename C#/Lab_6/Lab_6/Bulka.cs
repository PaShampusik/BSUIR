using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_6
{
    internal class Bulka : Bludo
    {
        private double price;
        private bool fresh;
        private double weight;
        private string name;
        public bool Fresh
        {
            get
            {
                return fresh;
            }
            set
            {
                fresh = value;
            }
        }
        public double Weight
        {
            get
            {
                return weight;
            }
            set
            {
                if (value > 0)
                {
                    weight = value;
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
                return name;
            }
            set
            {
                name = value;
            }
        }
        public double Price
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

        public Bulka(String name = "Smetannik", double price = 1, double weight = 120, bool fresh = true)
        {
            Name = name;
            Price = price;
            Weight = weight;
            Fresh = fresh;
        }


        public override string Sustain()
        {
            if (fresh) { 
            
                return "Bulka is new";
            }
            else
            {
                return "Bulka is not fresh";
            }
        }

        public override string GetName()
        {
            return name;
        }
        public override double GetWeight()
        {
            return weight;
        }
        public override double GetPrice()
        {
            return price;
        }
        public override double WeightToPrice()
        {
            return weight / price;
        }

    }
}
