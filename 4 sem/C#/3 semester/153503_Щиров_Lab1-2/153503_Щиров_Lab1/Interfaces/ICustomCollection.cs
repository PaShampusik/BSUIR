using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153503_Щиров_Lab1.Interfaces
{
    internal interface ICustomCollection<T> 
    {
        public T this[int index]
        {
            get;
            set;
        }

        void Reset();

        void Next();

        T Current();

        public int Count
        {
            get
            {
                return Count;
            }
            set
            {
                Count = value;
            }
        }
        void Add(T item);

        void Remove(T item);
        T RemoveCurrent();

    }

}