using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_5
{
    public class Client
    {
        private string name;
        private string number;

        public Client(string name, string number)
        {
            this.name = name;
            this.number = number;
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public string Number
        {
            get { return number; }
            set { number = value; }
        }
        
        
    }
}
