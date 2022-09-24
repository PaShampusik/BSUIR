using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153503_Shchirov_Lab_6.Entities
{
    internal class Employee
    {
        public int Age
        {
            get;
            set;
        }

        public bool Male
        {
            get;
            set;
        }

        public string? Name
        {
            get;
            set;
        }

        public Employee(string name, bool male, int age)
        {
            Name = name;
            Male = male;
            Age = age;
        }
    }
}

