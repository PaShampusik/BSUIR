using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_4.Entities
{
    internal class MyCustomComparer<T> : IComparer<T>
    {
        /*private Comparison<T> comparison;

        public MyCustomComparer(Comparison<T> comparison)
        {
            if (comparison == null)
                throw new ArgumentNullException("comparison");
            this.comparison = comparison;
        }

        public int Compare(T x, T y)
        {
            return comparison(x, y);
        }*/
        public int Compare(T? x, T? y)
        {
            if (x == null && y == null)
                return 0;
            if (x == null)
                return -1;
            if (y == null)
                return 1;
            return x.ToString().CompareTo(y.ToString());
        }
        
    }
}
