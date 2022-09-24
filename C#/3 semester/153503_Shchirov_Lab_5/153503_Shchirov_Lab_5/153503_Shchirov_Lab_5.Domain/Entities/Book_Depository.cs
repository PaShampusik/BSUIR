using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153503_Shchirov_Lab_5.Domain.Entities
{
    [Serializable]
    public class Book_Depository
    {
        public string Name
        {
            get;
            set;
        }

        public int Count
        {
            get;
            set;
        }

        public override string ToString()
        {
            return $"{Name} {Count}";
        }

        public IEnumerable<Book_Depository> GetDepository()
        {
            yield return this;
        }
    }
}
