using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_6
{
    abstract class Bludo
    {
        public string? name
        {
            get;
        }
        public virtual string? GetName()
        {
            return name;
        }

        

        

        public abstract double GetPrice();

        public abstract double GetWeight();

        public abstract string Sustain();
        public virtual double WeightToPrice()
        {
            return 0;
        } 
        
    }
}
